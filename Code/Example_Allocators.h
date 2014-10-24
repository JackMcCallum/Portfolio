/*
@author
Jack McCallum

@licence
This code is free to use, no credit required if used but is appreciated, thanks.



this allocator will return a block a memory of size 'SIZE' in bytes
when this allocator runs out of free memory it will allocate more
it will allocate 'RESERVE' many and return 1 and save the rest for later
RESERVE = 64 by default

this allocators primary use is for the command queue
to speed up the storage of thousands of commands 
*/

template<uint32 SIZE, uint32 RESERVE = 64>
class TFixedSizeAllocator
{
public:
	~TFixedSizeAllocator()
	{
		for (auto iter : mBlockList)
			::free(iter);

		assert(mFreeList.size() == mNumAllocated && "Possible memory leaks");
	}

	// Grab a block of SIZE bytes returns nullptr if it fails
	void* allocate()
	{
		static_assert(RESERVE > 0, "Reserve cannot be 0");

		mLock.lock();

		if (!mFreeList.empty())
		{
			// Grab a free pointer from the back of the list
			void* ptr = mFreeList.back();
			assert(ptr); // Err...?

			mFreeList.pop_back();

			mLock.unlock();
			return ptr;
		}
		else
		{
			// Allocate a new block
			void* block = malloc(SIZE * RESERVE);
			if (!block) throw std::exception("Out of memory");

			// Register the memory block for cleanup later
			mBlockList.push_back(block);

			// Push all the spares into the free list
			// Note: loop starts at 1, not 0 since we are returning the 0th element
			mFreeList.reserve(mFreeList.size() + RESERVE - 1);
			for (uint32 i = 1; i < RESERVE; i++)
				mFreeList.push_back((uint8*)block + SIZE * i);

			// Keep track of the number allocated so we can detect memory leaks
			mNumAllocated += RESERVE;

			mLock.unlock();
			return block;
		}
	}

	// Free a pointer that was allocated by this allocator
	// Note: the allocator can not tell if the pointer belongs to it.
	void free(void* ptr)
	{
		assert(ptr);
		mLock.lock();
		// Push the
		mFreeList.push_back(ptr);
		mLock.unlock();
	}

private:
	// List of free slots
	std::vector<void*> mFreeList;
	std::vector<void*> mBlockList;
	uint32 mNumAllocated;
	std::mutex mLock;
};

/*
Simple wrapper class for the supplied type instead of size
TFixedSizeAllocator<sizeof(Type), RESERVE>
*/
template<class Type, uint32 RESERVE = 64>
class TFixedTypeAllocator
{
public:
	Type* allocate()
	{
		static_assert(RESERVE > 0, "Reserve cannot be 0");
		return (Type*)mAlloc.allocate();
	}

	void free(Type* ptr)
	{
		mAlloc.free(ptr);
	}

private:
	TFixedSizeAllocator<sizeof(Type), RESERVE> mAlloc;
};


/*
Simple object allocator class
This is intended to be inherited by an object that needs to be new'd
by default the allocator is TFixedSizeAllocator<sizeof(Type), RESERVE>
but other allocators can be provided. they must supply:
void* allocate(); and void free(void* ptr);

Example:
	class MyClass : public TObjectAllocator<MyClass>
	{
	}

By utilizing this class you can potentially increase the
speed of new/delete for that object by over 10000% or more
compared to the standard new/delete methods
*/

template<class T, class Alloc = TFixedTypeAllocator<T>>
class TObjectAllocator
{
public:
	void* operator new(size_t size)
	{
		assert(size == sizeof(T));
		return getAllocator().allocate();
	}

	void operator delete(void* ptr)
	{
		getAllocator().free((T*)ptr);
	}

	static Alloc& getAllocator()
	{
		static Alloc alloc;
		return alloc;
	}
};