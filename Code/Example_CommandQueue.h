
namespace NGine
{
	// Simple abstract command class
	class Command
	{
	public:
		virtual ~Command() {}

		virtual void executeAndDestroy() = 0;
	};

	// A command queue from which you can push commands and have them execute on
	// a second thread primarily built for render commands on a 2nd thread
	// To make a command for the queue have a class that inherits from TCommand
	// with the template parameter as the class name you just made
	// And override the abstract execute() method and put your code in there
	// eg: class MyCommand : public TCommand<MyCommand>
	class CommandQueue
	{
	public:
		CommandQueue() : mRequestReturn(false) {}

		// Enter an infinite loop processing each task as it can
		// This method wont return until requestReturn() is called
		void processUntilRequestReturn();

		// Request the return of the infinite loop
		void requestReturn();

		// Push a task into the queue
		template<class T>
		void enqueueCommand(const T& task);

	protected:
		template<class T>
		friend class TCommand;

		// Hard coded size of each task
		enum TaskSize
		{
			SMALL_TASK = 64,
			MEDIUM_TASK = 256,
			LARGE_TASK = 1024,
		};

		// Task allocators
		static TFixedSizeAllocator<SMALL_TASK>& getSmallTaskAllocator();
		static TFixedSizeAllocator<MEDIUM_TASK>& getMediumTaskAllocator();
		static TFixedSizeAllocator<LARGE_TASK>& getLargeTaskAllocator();

	private:
		std::queue<Command*> mQueue;
		std::mutex mMutex;
		std::condition_variable mConditional;
		
		bool mRequestReturn;
	};

	template<class T>
	void CommandQueue::enqueueCommand(const T& task)
	{
		std::unique_lock<std::mutex> mlock(mMutex);

		if (sizeof(T) <= SMALL_TASK)
		{
			void* ptr = CommandQueue::getSmallTaskAllocator().allocate();
			mQueue.push(new (ptr)T(task));
		}
		else if (sizeof(T) <= MEDIUM_TASK)
		{
			void* ptr = CommandQueue::getMediumTaskAllocator().allocate();
			mQueue.push(new (ptr)T(task));
		}
		else if (sizeof(T) <= LARGE_TASK)
		{
			void* ptr = CommandQueue::getLargeTaskAllocator().allocate();
			mQueue.push(new (ptr)T(task));
		}
		else
		{
			mQueue.push(new T(task));
		}

		mlock.unlock();
		mConditional.notify_one();
	}

	template<class T>
	class TCommand : public Command
	{
	public:
		virtual ~TCommand() {}

		// Virtual function for the user to put the code
		// they want to execute in
		virtual void execute() = 0;

		// Execute the command and clean it up after completion
		virtual void executeAndDestroy()
		{
			execute();

			// Destroy the task
			if (sizeof(T) <= CommandQueue::SMALL_TASK)
			{
				this->~TCommand();
				CommandQueue::getSmallTaskAllocator().free(this);
			}
			else if (sizeof(T) <= CommandQueue::MEDIUM_TASK)
			{
				this->~TCommand();
				CommandQueue::getMediumTaskAllocator().free(this);
			}
			else if (sizeof(T) <= CommandQueue::LARGE_TASK)
			{
				this->~TCommand();
				CommandQueue::getLargeTaskAllocator().free(this);
			}
			else
			{
				delete this;
			}
		}
	};

	// Command queue fence can be used to track the command queue,
	// It can be used to flush the queue or wait for a command to complete
	class CommandQueueFence
	{
	public:
		class NotifyEvent : public NGine::TCommand<NotifyEvent>
		{
		public:
			NotifyEvent(CommandQueueFence* parent) : mParent(parent) {}

			virtual void execute() { mParent->notify(); }

		private:
			CommandQueueFence* mParent;
		};

	public:
		CommandQueueFence() : mSignalled(false), mHasBegun(false), mNotifyEvent(this) {}

		// Begin the fence, inserts a command into the given queue
		// When that command is processed it will call notify();
		void begin(NGine::CommandQueue* queue);

		// notify the fence it has completed
		void notify();

		// Wait for the fence to complete, if it has already completed
		// it will do nothing
		void wait();

	private:
		std::mutex mMutex;
		std::condition_variable mConditional;
		bool mSignalled;
		bool mHasBegun;

		NotifyEvent mNotifyEvent;
	};
}

// ============================================
// .cpp file

namespace NGine
{
	void CommandQueue::processUntilRequestReturn()
	{
		mRequestReturn = false;
		
		while (!mRequestReturn)
		{
			// if there are no tasks, wait for a task, or until request return 
			std::unique_lock<std::mutex> mlock(mMutex);
			while (mQueue.empty() && !mRequestReturn)
				mConditional.wait(mlock);

			if (mRequestReturn)
				return;

			// Pop and execute a task
			Command* item = nullptr;
			if (task = mQueue.front())
			{
				mQueue.pop();
				item->executeAndDestroy();
			}
		}
	}

	void CommandQueue::requestReturn()
	{
		mRequestReturn = true;
		mConditional.notify_all();
	}

	TFixedSizeAllocator<CommandQueue::SMALL_TASK>& CommandQueue::getSmallTaskAllocator()
	{
		static TFixedSizeAllocator<SMALL_TASK> allocator;
		return allocator;
	}

	TFixedSizeAllocator<CommandQueue::MEDIUM_TASK>& CommandQueue::getMediumTaskAllocator()
	{
		static TFixedSizeAllocator<MEDIUM_TASK> allocator;
		return allocator;
	}

	TFixedSizeAllocator<CommandQueue::LARGE_TASK>& CommandQueue::getLargeTaskAllocator()
	{
		static TFixedSizeAllocator<LARGE_TASK> allocator;
		return allocator;
	}

	void CommandQueueFence::begin(NGine::CommandQueue* queue)
	{
		mHasBegun = true;
		mSignalled = false;
		queue->enqueueCommand(mNotifyEvent);
	}

	void CommandQueueFence::notify()
	{
		std::unique_lock<std::mutex> lock(mMutex);
		mSignalled = true;
		mHasBegun = false;
		lock.unlock();
		mConditional.notify_all();
	}

	void CommandQueueFence::wait()
	{
			std::unique_lock<std::mutex> lock(mMutex);
			if (!mSignalled && mHasBegun)
				mConditional.wait(lock, [&](){ return mSignalled; });
	}

}
