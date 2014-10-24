#include "StdAfx.h"
#include "HPDisplay.h"

// ------------------------------------------------------------------------------------------------------------
HPDisplay::HPDisplay(String name, Overlay* parent, float& hp) : HUDElement(name, parent), linkedHP(hp)
{
	container->setMaterialName("Material_MenuItemBackground");
	container->setMetricsMode(GMM_RELATIVE_ASPECT_ADJUSTED);
	container->setWidth(2200);
	container->setHeight(1200);
	container->setPosition(0,8800);
	//container->setHorizontalAlignment(GHA_RIGHT);
	
	// The number tha
	OverlayManager* overlayMgr = OverlayManager::getSingletonPtr();
	textarea = (TextAreaOverlayElement*)overlayMgr->createOverlayElement("TextArea", name+"TextDisplay");
	textarea->setMetricsMode(GMM_RELATIVE_ASPECT_ADJUSTED);
	textarea->setFontName("MenuFont");
	textarea->setCharHeight(600);
	textarea->setPosition(180, 580);
	textarea->setColour(ColourValue::White);
	container->addChild(textarea);

	// Title area
	titlearea = (TextAreaOverlayElement*)overlayMgr->createOverlayElement("TextArea", name+"TitleDisplay");
	titlearea->setMetricsMode(GMM_RELATIVE_ASPECT_ADJUSTED);
	titlearea->setFontName("HUDFont");
	titlearea->setCharHeight(300);
	titlearea->setPosition(180, 180);
	titlearea->setColour(ColourValue(0.913f, 0.588f, 0.294f));
	container->addChild(titlearea);

	displayHP = 0;

	if (linkedHP != actualHP)
		actualHP = linkedHP;
}
// ------------------------------------------------------------------------------------------------------------
HPDisplay::~HPDisplay()
{
	OverlayManager* overlayMgr = OverlayManager::getSingletonPtr();
	overlayMgr->destroyOverlayElement(textarea);
	overlayMgr->destroyOverlayElement(titlearea);

}
// ------------------------------------------------------------------------------------------------------------
void HPDisplay::update(float timeSinceLastFrame)
{
	if (linkedHP != actualHP)
		actualHP = linkedHP;

	if (displayHP > actualHP)
	{
		displayHP -= 2.5;
		if (displayHP < actualHP)
			displayHP = actualHP;
	}
	else if (displayHP < actualHP)
	{
		displayHP += 2.5;
		if (displayHP > actualHP)
			displayHP = actualHP;
	}

	titlearea->setCaption("Armor:");
	textarea->setCaption(StringConverter::toString((int)displayHP));
}
// ------------------------------------------------------------------------------------------------------------