/************************************************************************/
/* @class Collidable
 * @author Jack McCallum
 * 
 * @description
 * This is a base class for anything that needs a solid body in the scene
 * A collision manager must be supplied
 * 
/************************************************************************/

#pragma once

class JMShape;
#include "Game.h"

class Collidable
{
public:
	Collidable(GameData gd);
	virtual ~Collidable();

	virtual void update(float timeSinceLastFrame);
	// This function is called from the collision manager,
	// The object it collided with and the direction and magnitude it moved to get away
	virtual void collision(Collidable* obj, float pushx, float pushy);

	// Gets the collision shape
	JMShape* getCollision();

	// Setup Circle collision
	void setCollisionCircle(float radius);
	void setCollisionCircle(float xx, float yy, float radius);

	// Setup rectangle collision
	void setCollisionRect(float width, float height);
	void setCollisionRect(float top, float left, float bottom, float right);

	// Positioning of this
	void position(float xx, float yy);
	void translate(float xx, float yy);
	void getPosition(float& xx, float& yy);

	// Mass for collision control
	float getMass();
	void setMass(float val);

	// Ray query flags, this allows me to be specific on what i want to return in a ray query
	void setRayQueryFlags(int flags);
	int getRayQueryFlags();

	// Safe way to delete, if you wanna delete due to a collision, 
	// it can fuck with the iterators, this method allows the collision manager 
	// to delete this after all the updates and collisions have been processed
	void deleteThis();
	
	bool nDelete;
	
protected:
	// Ogre Stuff
	// Scene node of which things can attach them selfs
	SceneNode* mainNode;
	
	// Contains pointers to managers etc...
	GameData gameData;

	// Collision Stuff
	// Flags used for ray queries
	// Works very similar, if not the same as ogres method
	int rayQueryFlags;	
	JMShape* collisionShape;
	// This variable controls how collisions are handle (0 = static)
	float mass;
	// World positions as float
	float posx, posy;


};

