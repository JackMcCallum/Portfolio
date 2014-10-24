/************************************************************************/
/* @class Spawner
 * @author Jack McCallum
 * 
 * @description
 * This is a simple class that creates the visuals for a spawner
 * and spawns enemies nearby based a timer
 * The less hit points it has the slower the rate it spawns
 * 
/************************************************************************/

#pragma once

#include "Destructable.h"
#include "Collidable.h"
#include "Enemy.h"

class Spawner : public Collidable, public Destructable
{
public:
	Spawner(GameData gd);
	virtual ~Spawner();
	
	// Control
	virtual void update(float timeSinceLastFrame);
	virtual void destroyed();

	// Spawns a new enemy next to this
	void spawnNew();

	bool isDead;

private:
	int spawnInterval;
	
	// Ogre
	Entity* meshEntity;
	MaterialPtr glowmat;

};

