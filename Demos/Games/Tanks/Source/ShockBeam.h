/************************************************************************/
/* @class ShockBeam
 * @author Jack McCallum
 * 
 * @description
 * 
 * 
/************************************************************************/

#pragma once
#include "OgreMain.h"
#include "Effect.h"

class ShockBeam : public Effect
{
public:
	ShockBeam(EffectsManager* mgr, OgreMain* oMain, float sx, float sy, float ex, float ey, float sca, ColourValue col = ColourValue::White);
	~ShockBeam();

	// Update animations
	virtual void update();

protected:
	// Data
	float startx, starty;
	float endx, endy;
	float scale;
	ColourValue color;
	
	// Ogre
	OgreMain* ogreMain;
	BillboardChain* bbc;
	BillboardSet* bbs;
	Billboard* bb[4];

	
};

