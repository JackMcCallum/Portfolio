/************************************************************************/
/* @class Wall
 * @author Jack McCallum
 * 
 * @description
 * Real simple class that lets me place walls around my scene
 * a wall of 0 length is a tower, more than 0 is a section either 
 * horizontal or vertical
 * 
/************************************************************************/

#pragma once

#include "Collidable.h"

class Wall : public Collidable
{
public:
	enum WallDirection
	{
		WD_VERTICAL,
		WD_HORIZONTAL
	};

	Wall(GameData gd, WallDirection direction, int length);
	virtual ~Wall();

private:
	// Each visual segment of the wall
	std::vector<std::pair<Entity*, SceneNode*>> segmentList;
};

