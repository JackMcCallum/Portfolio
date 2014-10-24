#include "StdAfx.h"
#include "Spawner.h"
#include "CollisionManager.h"
#include "Explosion.h"

// ------------------------------------------------------------------------------------------------------------
Spawner::Spawner(GameData gd) : Collidable(gd)
{
	// Create the visuals
	meshEntity = gameData.ogreMain->getSceneManager()->createEntity("Spawner.mesh");
	mainNode->attachObject(meshEntity);

	// Generate a new material so we can display its health with colour
	// If i don't make a new material, the health state would be global 
	// for all meshes sharing this material
	SubEntity* subent = meshEntity->getSubEntity(1);
	glowmat = subent->getMaterial();

	// Make a new unique name for it
	String newName = glowmat->getName();
	while (MaterialManager::getSingletonPtr()->resourceExists(newName))
		newName = glowmat->getName() + StringConverter::toString(rand());

	// and finally set our material
	MaterialPtr newMat = glowmat->clone(newName);
	subent->setMaterial(newMat);
	glowmat = newMat;

	// Setup game properties for this object
	setCollisionCircle(8);
	setRayQueryFlags(FLAG_ENEMY);
	setHitPonts(1000);

	// Random start point so the spawner is not spawning in sync with others
	spawnInterval = (rand()%200)-200;
	isDead = false;
}
// ------------------------------------------------------------------------------------------------------------
Spawner::~Spawner()
{
	// Cleanup
	gameData.ogreMain->getSceneManager()->destroyEntity(meshEntity);
}
// ------------------------------------------------------------------------------------------------------------
void Spawner::update(float timeSinceLastFrame)
{
	if (!isDead)
	{
		// If the spawn interval is ready to spawn,
		// Spawn one and reset
		if (spawnInterval > 700-getHitPoints()/2)
		{
			spawnNew();
			spawnInterval = 0;
		}
		else
			// Else increment the spawn counter
			spawnInterval++;

		// Update the material
		float l = getHitPoints()/1000.0f;
		glowmat->getTechnique(0)->getPass(0)->setEmissive(ColourValue::Green*l + ColourValue::Red*(1-l));
		glowmat->_notifyNeedsRecompile();
	}
}
// ------------------------------------------------------------------------------------------------------------
void Spawner::destroyed()
{
	gameData.game->addScore(10);
	new Explosion(gameData.effectsManager, gameData.ogreMain, posx, posy, 3, ColourValue(0.4f,1,0.7f));
	isDead = true;
	glowmat->getTechnique(0)->getPass(0)->setEmissive(ColourValue::Black);
	glowmat->_notifyNeedsRecompile();
}
// ------------------------------------------------------------------------------------------------------------
void Spawner::spawnNew()
{
	// Spawn an enemy in a random direction next to this spawner
	Enemy* enemy = new Enemy(gameData);
	enemy->position(posx+Math::RangeRandom(-1,1),posy+Math::RangeRandom(-1,1));
}
// ------------------------------------------------------------------------------------------------------------