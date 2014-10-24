/************************************************************************/
/* @class Enemy
 * @author Jack McCallum
 * 
 * @description
 * The enemy, little spiky balls that roll towards the player if they can see it
 * These are automatically spawned by Spawner, upon collision with player
 * they blow up and deal damage to the player
 * 
/************************************************************************/

#pragma once

#include "Destructable.h"
#include "Collidable.h"

class Spawner;

class Enemy : public Collidable, public Destructable
{
public:
	Enemy(GameData gd);
	virtual ~Enemy();

	// Control
	virtual void update(float timeSinceLastFrame);
	virtual void collision(Collidable* obj, float pushx, float pushy);
	virtual void destroyed();

private:
	// Ogre
	SceneNode* offsetNode;
	Entity* meshEntity;

	// AI & Motion Control
	float playerSightTimeout;
	float rayTimeout;
	float velx, vely;
};

