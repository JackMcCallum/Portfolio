/************************************************************************/
/* @class Explosion
 * @author Jack McCallum
 * 
 * @description
 * 
 * 
/************************************************************************/

#pragma once
#include "OgreMain.h"
#include "Effect.h"

class Explosion : public Effect
{
public:
	Explosion(EffectsManager* mgr, OgreMain* oMain, float x, float y, float s, ColourValue c);
	~Explosion();

	// Update animations
	virtual void update();

protected:
	// Data
	float posx, posy, scale;
	ColourValue color;

	// Ogre
	OgreMain* ogreMain;
	BillboardSet* bbs;
	Billboard* bb[4];
};

