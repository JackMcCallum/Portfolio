#include "StdAfx.h"
#include "Wall.h"
#include "CollisionManager.h"

// ------------------------------------------------------------------------------------------------------------
Wall::Wall(GameData gd, WallDirection direction, int length) : Collidable(gd)
{
	// Is it a tower or segment?
	if (length > 0)
	{
		// Define the collision rectangle
		if (direction == WD_HORIZONTAL)
			setCollisionRect(2,0,14, 16.0f*length);
		else
			setCollisionRect(0,2,16.0f*length, 14);

		// Create the entities and attach
		segmentList.resize(length);
		for (int i=0; i<length; i++)
		{
			segmentList[i].first = gameData.ogreMain->getSceneManager()->createEntity("WallSection.mesh");
			segmentList[i].second = mainNode->createChildSceneNode();
			segmentList[i].second->attachObject(segmentList[i].first);

			if (direction == WD_HORIZONTAL)
			{
				// Horizontal entity
				segmentList[i].second->setPosition(8+i*16.0f,0,8);
			}
			else
			{
				// Vertical entity
				segmentList[i].second->setPosition(8,0,8+i*16.0f);
				segmentList[i].second->yaw(Degree(90));
			}
		}
	}
	else
	{
		// Create the tower entity
		Entity* ent = gameData.ogreMain->getSceneManager()->createEntity("WallTower.mesh");
		SceneNode* node = mainNode->createChildSceneNode(Vector3(8,0,8));
		node->attachObject(ent);
		setCollisionRect(0,0,16, 16);
	}

	// Set the ray query flags to WALL
	setRayQueryFlags(FLAG_WALL);
}
// ------------------------------------------------------------------------------------------------------------
Wall::~Wall()
{
	// Clean up
	int length = segmentList.size();
	for (int i=0; i<length; i++)
	{
		gameData.ogreMain->getSceneManager()->destroyEntity(segmentList[i].first);
		segmentList[i].second->removeAndDestroyAllChildren();
	}
	mainNode->removeAndDestroyAllChildren();
	// Main node is destroyed by parent destructor
}
// ------------------------------------------------------------------------------------------------------------