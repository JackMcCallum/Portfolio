#include "StdAfx.h"
#include "Explosion.h"

Explosion::Explosion(EffectsManager* mgr, OgreMain* oMain, float x, float y, float s, ColourValue c) : Effect(mgr)
{
	ogreMain = oMain;
	posx = x;
	posy = y;
	scale = s;
	color = c;

	// Setup the billboard
	bbs = ogreMain->getSceneManager()->createBillboardSet();
	bbs->setMaterialName("Mat_Shock");
	ogreMain->getSceneManager()->getRootSceneNode()->attachObject(bbs);
	bbs->setTextureStacksAndSlices(2,2);
	bbs->setBillboardRotationType(BBR_VERTEX);

	bb[0] = bbs->createBillboard(posx, 4, posy, ColourValue::White);
	bb[0]->setTexcoordIndex(0);
	bb[0]->setRotation(Degree(Math::RangeRandom(0,360)));

	bb[1] = bbs->createBillboard(posx, 4, posy, ColourValue::White);
	bb[1]->setTexcoordIndex(1);
	bb[1]->setRotation(Degree(Math::RangeRandom(0,360)));

	bb[2] = bbs->createBillboard(posx, 4, posy, ColourValue::White);
	bb[2]->setTexcoordIndex(2);
	bb[2]->setRotation(Degree(Math::RangeRandom(0,360)));

	bb[3] = bbs->createBillboard(posx, 4, posy, ColourValue::White);
	bb[3]->setTexcoordIndex(3);
	bb[3]->setRotation(Degree(Math::RangeRandom(0,360)));

}

Explosion::~Explosion()
{
	ogreMain->getSceneManager()->destroyBillboardSet(bbs);
}

void Explosion::update()
{
	animate += 0.03f;

	if (animate > 1)
	{
		delete this;
		return;
	}

	// Position billboards
	bb[0]->setDimensions((8+(pow(1-animate,3))*16)*scale, (8+(pow(1-animate,3))*16)*scale);
	bb[1]->setDimensions((16+animate*animate*16)*scale,(16+animate*animate*16)*scale);
	bb[2]->setDimensions((16+animate*animate*16)*scale,(16+animate*animate*16)*scale);
	bb[3]->setDimensions((16+(1-pow(1-animate,2))*32)*scale, (16+(1-pow(1-animate,2))*32)*scale);
	bb[0]->setColour(color*(1-animate));
	bb[1]->setColour(color*(1-animate));
	bb[2]->setColour(color*(1-animate));
	bb[3]->setColour(color*(1-animate));

}
