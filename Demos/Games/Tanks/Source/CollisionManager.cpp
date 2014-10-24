#include "StdAfx.h"
#include "CollisionManager.h"
#include "JMRay.h"
#include "Collidable.h"
#include "Player.h"
#include "JMShape.h"

// ------------------------------------------------------------------------------------------------------------
CollisionManager::CollisionManager(JMFrameEventHandler* frameHndl)
{
	frameHandler = frameHndl;

	// If given a frame handler, add it
	if (frameHandler)
		frameHandler->addListener((JMFrameEventListener*)this);

	collidableList.clear();
}
// ------------------------------------------------------------------------------------------------------------
CollisionManager::~CollisionManager()
{
	// If given a frame handler, remove it
	if (frameHandler)
		frameHandler->removeListener((JMFrameEventListener*)this);
}
// ------------------------------------------------------------------------------------------------------------
void CollisionManager::addCollidable(Collidable* c)
{
	// Add a Collidable to be processed
	collidableList.push_back(c);
}
// ------------------------------------------------------------------------------------------------------------
void CollisionManager::removeCollidable(Collidable* c)
{
	// Remove a Collidable from being processed
	collidableList.remove(c);
}
// ------------------------------------------------------------------------------------------------------------
void CollisionManager::update(float timeSinceLastFrame)
{
	// Update all Collidable objects
	std::list<Collidable*>::iterator collidableIter;
	collidableIter = collidableList.begin();
	while (collidableIter != collidableList.end())
		(*collidableIter++)->update(timeSinceLastFrame);
	
	// Begin the collision process
	collidableIter = collidableList.begin();
	while (collidableIter != collidableList.end())
	{
		Collidable* obj1 = (*collidableIter++);

		// Ignore objects that are static, ignore it
		if (obj1->getMass() == 0)
			continue;

		// If the Collidable shape is not yet initialized, ignore it
		JMShape* shape1 = obj1->getCollision();
		if (shape1 == NULL)
			continue;

		// First do all the static objects
		std::list<Collidable*>::iterator iter;
		iter = collidableList.begin();
		while (iter != collidableList.end())
		{
			Collidable* obj2 = (*iter++);

			// If the object is not static, skip it
			// Or if the objects are the same, skip it
			if (obj1 == obj2 || obj2->getMass() != 0)
				continue;

			// If the shape is NULL, skip it
			JMShape* shape2 = obj2->getCollision();
			if (shape2 == NULL)
				continue;

			// Okay so all the tests have passed, check for an intersection
			float xx, yy;
			if (shape1->intersects(shape2, xx, yy))
			{
				// There was an intersection, now move the non static object out of the way
				obj1->translate(-xx,-yy);
				// Send collision events to those objects
				obj2->collision(obj1, 0,0);
				obj1->collision(obj2, -xx,-yy);
			}
		}

		// Secondly do all the non static, but only check them once each for every object,
		// To do this we start from where this object is in the list +1
		iter = collidableIter;
		while (iter != collidableList.end())
		{
			Collidable* obj2 = (*iter++);

			// If the object is static, skip it
			// Or if the objects are the same, skip it
			if (obj1 == obj2 || obj2->getMass() == 0)
				continue;

			// If the shape is NULL, skip it
			JMShape* shape2 = obj2->getCollision();
			if (shape2 == NULL)
				continue;

			// Okay so all the tests have passed, check for an intersection
			float xx, yy;
			if (shape1->intersects(shape2, xx, yy))
			{
				// An intersection has occurred
				// Calculate how much each object should be moved away from each other
				// based on their masses
				float ma1 = obj2->getMass()/(obj1->getMass()+obj2->getMass());
				float ma2 = 1-ma1;

				// Now move each object apart
				obj1->translate(-xx*ma1,-yy*ma1);
				obj2->translate(xx*ma2,yy*ma2);

				// Send collision events
				obj1->collision(obj2, -xx*ma1,-yy*ma1);
				obj2->collision(obj1, xx*ma2,yy*ma2);
			}
		}
	}

	// Each collidable has a deleteThis();
	// If that was called, this is where we delete it
	collidableIter = collidableList.begin();
	while (collidableIter != collidableList.end())
	{
		Collidable* obj = (*collidableIter++);
		if (obj->nDelete)
			delete obj;
	}
}
// ------------------------------------------------------------------------------------------------------------
void CollisionManager::rayQuery(JMRay* ray, rayResults& results, int flags)
{
	int f;
	float pos;
	Collidable* obj;
	
	// A ray query queries all object in the scene to see if they intersect with a ray
	// If they meet the flag requirements, and they intersect, they are added to an external list
	std::list<Collidable*>::iterator iter = collidableList.begin();
	while (iter != collidableList.end())
	{
		obj = (*iter++);
		// Get the flags
		f = obj->getRayQueryFlags();
		// if the flags pass the test, then check for intersection
		if ((f & flags) == f)
		if (obj->getCollision()->intersects(ray, pos))
			results.push_back(std::pair<float, Collidable*>(pos, obj));
	}
}
// ------------------------------------------------------------------------------------------------------------
void CollisionManager::eventPreRender(const JMFrameEvent &evt)
{
	// Automatic updating when listening to a frame event handler
	update(evt.timeSinceLastFrame);
}
// ------------------------------------------------------------------------------------------------------------
Player* CollisionManager::findPlayer()
{
	// Iterates through all Collidable and if it finds a player, 
	// returns the pointer, else it returns NULL
	std::list<Collidable*>::iterator iter = collidableList.begin();
	while (iter != collidableList.end())
	{
		Collidable* obj = (*iter++);
		// Is this object the player?
		if (typeid(Player) == typeid(*obj))
			return static_cast<Player*>(obj);
	}
	return NULL;
}
// ------------------------------------------------------------------------------------------------------------
std::list<Collidable*>& CollisionManager::getCollidableList()
{
	return collidableList;
}

void CollisionManager::destroyAllCollidables()
{
	// Destroys all objects
	std::list<Collidable*>::iterator iter = collidableList.begin();
	while (iter != collidableList.end())
	{
		Collidable* obj = (*iter++);
		delete obj;
	}
	collidableList.clear();
}

// ------------------------------------------------------------------------------------------------------------