
#include "StdAfx.h"
#include "Enemy.h"
#include "MathsMacros.h"

#include "CollisionManager.h"
#include "Game.h"
#include "JMRay.h"

#include "Player.h"
#include "Spawner.h"
#include "Wall.h"
#include "Explosion.h"

// ------------------------------------------------------------------------------------------------------------
Enemy::Enemy(GameData gd) : Collidable(gd)
{
	// Setup visuals
	meshEntity = gameData.ogreMain->getSceneManager()->createEntity("Enemy.mesh");
	offsetNode = mainNode->createChildSceneNode(Vector3(0,3,0));
	offsetNode->attachObject(meshEntity);

	// Object properties
	setMass(500);
	setHitPonts(100);
	setCollisionCircle(4);
	setRayQueryFlags(FLAG_ENEMY);

	// Movement properties
	velx = 0;
	vely = 0;
	playerSightTimeout = 200;
	rayTimeout = Math::RangeRandom(0, 60);
}
// ------------------------------------------------------------------------------------------------------------
Enemy::~Enemy()
{
	// Cleanup
	gameData.ogreMain->getSceneManager()->destroyEntity(meshEntity);
	mainNode->removeAllChildren();
}
// ------------------------------------------------------------------------------------------------------------
void Enemy::update(float timeSinceLastFrame)
{
	// If player exists in the collision manager
	Player* player = gameData.collisionManager->findPlayer();
	if (player)
	{
		// Get the players position
		float px, py;
		player->getPosition(px, py);

		// Only every 60 frames, so we don't lag balls by casting a ray so often
		if (rayTimeout > 60)
		{
			// Cast a ray from this to the player
			JMRay ray(posx, posy, px, py);
			rayResults results;
			gameData.collisionManager->rayQuery(&ray, results, FLAG_PLAYER|FLAG_WALL);
			
			// Find the closest result, rather than sorting
			std::pair<float, Collidable*> closest(999999.0f, nullptr);
			closest.second = NULL;
			rayResults::iterator iter = results.begin();
			while (iter != results.end())
			{
				while ((*iter).first < closest.first)
					closest = (*iter);
				iter++;
			}
			
			// If the closest is the player, set the timer
			if (closest.second != NULL && typeid(*closest.second) == typeid(Player))
				playerSightTimeout = 0;

			// Now reset the timer so we don't ray cast again for a while 
			rayTimeout = 0;
		}
		
		// This needs to continue seeking the player for at least 2 seconds after seeing it
		if (playerSightTimeout < 120)
		{
			// add force in the direction towards the player
			float dirx, diry, l;
			dirx = px-posx;
			diry = py-posy;
			l = Sqrt(dirx*dirx + diry*diry);
			dirx = (dirx/l);
			diry = (diry/l);
			velx += dirx*0.015f;
			vely += diry*0.015f;
		}

		// increment timers
		rayTimeout++;
		playerSightTimeout++;
	}

	// Apply velocity
	velx *= 0.99f;
	vely *= 0.99f;

	// Move it
	translate(velx, vely);
	
	// Rotate the visuals based on movement
	offsetNode->roll(Degree(-velx*10), Node::TS_WORLD);
	offsetNode->pitch(Degree(vely*10), Node::TS_WORLD);
}
// ------------------------------------------------------------------------------------------------------------
void Enemy::collision(Collidable* obj, float pushx, float pushy)
{
	// Rotate the visuals based on movement
	offsetNode->roll(Degree(-pushx*10), Node::TS_WORLD);
	offsetNode->pitch(Degree(pushy*10), Node::TS_WORLD);

	Player* player = dynamic_cast<Player*>(obj);
	if (player)
	{
		// Upon collision with player
		// Damage player
		player->damage(10);
		// Pop and explosion
		destroyed();
	}
}
// ------------------------------------------------------------------------------------------------------------
void Enemy::destroyed()
{
	gameData.game->addScore(1);
	new Explosion(gameData.effectsManager, gameData.ogreMain, posx, posy, 0.7f, ColourValue(1,0.2f,0.1f));
	deleteThis();
}
// ------------------------------------------------------------------------------------------------------------