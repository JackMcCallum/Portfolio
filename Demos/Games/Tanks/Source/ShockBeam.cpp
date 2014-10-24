#include "StdAfx.h"
#include "ShockBeam.h"


ShockBeam::ShockBeam(EffectsManager* mgr, OgreMain* oMain, float sx, float sy, float ex, float ey, float sca, ColourValue col) : Effect(mgr)
{
	ogreMain = oMain;
	startx = sx;
	starty = sy;
	endx = ex;
	endy = ey;
	color = col;
	scale = sca;

	// Billboard set
	bbs = ogreMain->getSceneManager()->createBillboardSet();
	bbs->setMaterialName("Mat_Shock");
	bbs->setTextureStacksAndSlices(2,2);
	bbs->setBillboardRotationType(BBR_VERTEX);
	bbs->setPoolSize(4);
	ogreMain->getSceneManager()->getRootSceneNode()->attachObject(bbs);

	// Billboards
	for (int i=0; i<4; i++)
	{
		bb[i] = bbs->createBillboard(endx, 4, endy, color);
		bb[i]->setTexcoordIndex(i);
		bb[i]->setRotation(Degree(Math::RangeRandom(0,360)));
	}

	// Billboard chain
	bbc = ogreMain->getSceneManager()->createBillboardChain();
	bbc->setMaterialName("Mat_Lightning");
	ogreMain->getSceneManager()->getRootSceneNode()->attachObject(bbc);
	
	// Length of the chain we need to make
	float dx, dy;
	dx = (startx-endx);
	dy = (starty-endy);
	float l = sqrt(dx*dx+dy*dy);

	// Add elements to the chain
	bbc->addChainElement(0, BillboardChain::Element(Vector3(startx, 4, starty), 4*scale, 0, color, Quaternion::IDENTITY));
	bbc->addChainElement(0, BillboardChain::Element(Vector3(endx, 4, endy), 4*scale, 1, color, Quaternion::IDENTITY));
}

ShockBeam::~ShockBeam()
{
	// Cleanup
	bbs->clear();
	ogreMain->getSceneManager()->destroyBillboardSet(bbs);
	ogreMain->getSceneManager()->destroyBillboardChain(bbc);

}

void ShockBeam::update()
{
	animate += 0.03f*(2-scale);

	if (animate > 1)
	{
		delete this;
		return;
	}

	// Update billboards
	float anim0 = (1+animate*animate)*scale;
	float anim1 = (1+(pow(1-animate,3))*2)*scale;
	float anim2 = (1+(1-pow(1-animate,2))*2)*scale;
	ColourValue fade = color*(1-animate);

	bb[0]->setDimensions(anim1*8, anim1*8);
	bb[1]->setDimensions(anim0*16,anim0*14);
	bb[2]->setDimensions(anim0*14,anim0*16);
	bb[3]->setDimensions(anim2*16, anim2*16);

	for (int i=0; i<4; i++)
		bb[i]->setColour(fade);
	
	// Update chain elements
	BillboardChain::Element e;
	e = bbc->getChainElement(0, 0);
	e.colour = fade;
	bbc->updateChainElement(0, 0, e);

	e = bbc->getChainElement(0, 1);
	e.colour = fade;
	bbc->updateChainElement(0, 1, e);
}
