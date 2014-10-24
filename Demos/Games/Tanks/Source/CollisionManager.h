/************************************************************************/
/* @class CollisionManager
 * @author Jack McCallum
 * 
 * @description
 * Collision manager is responsible for checking for collisions, handling them
 * then sending the event to object.
 * 
/************************************************************************/

#pragma once
#include "JMFrameEventHandler.h"

class Player;
class Collidable;
class JMRay;

// Define flags ill be using for my rays
#define FLAG_WALL 1
#define FLAG_PLAYER 2
#define FLAG_ENEMY 4

// Ray query results typedef
typedef std::list<std::pair<float, Collidable*>> rayResults;

class CollisionManager : public JMFrameEventListener
{
public:
	CollisionManager(JMFrameEventHandler* frameHndl = NULL);
	~CollisionManager();

	// Add/remove objects, this is mostly done automatically in the Collidable constructor/deconstruction
	void addCollidable(Collidable* c);
	void removeCollidable(Collidable* c);
	void destroyAllCollidables();

	// Updates all bodies, collisions and deletions
	void update(float timeSinceLastFrame);
	
	// Finds the pointer to the player in the list
	Player* findPlayer();
	
	// Queries the scene for all objects that intersect with the given ray
	void rayQuery(JMRay* ray, rayResults& results, int flags = 0);
	
	// Gets the address to the list, however this is a dangerous thing to do so don't edit the list externally
	std::list<Collidable*>& getCollidableList();

	// For automatically calling update
	virtual void eventPreRender(const JMFrameEvent &evt);


private:
	// Frame handler
	JMFrameEventHandler* frameHandler;

	// List
	std::list<Collidable*> collidableList;
};

