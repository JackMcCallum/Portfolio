#include "StdAfx.h"
#include "MenuButton.h"

// ------------------------------------------------------------------------------------------------------------
MenuButton::MenuButton(String caption, String name, Overlay* parent) : HUDElement(name, parent)
{
	buttonCaption = caption;

	// main container
	container->setMaterialName("Material_MenuItemBackground");
	container->setMetricsMode(GMM_RELATIVE_ASPECT_ADJUSTED);
	container->setWidth(8000);
	container->setHeight(800);
	
	// Caption area
	OverlayManager* overlayMgr = OverlayManager::getSingletonPtr();
	textarea = (TextAreaOverlayElement*)overlayMgr->createOverlayElement("TextArea", name+"MenuElementTextArea");
	textarea->setMetricsMode(GMM_RELATIVE_ASPECT_ADJUSTED);
	textarea->setFontName("MenuFont");
	textarea->setCharHeight(600);
	textarea->setPosition(180, 180);
	textarea->setColour(ColourValue::White);
	container->addChild(textarea);
}
// ------------------------------------------------------------------------------------------------------------
MenuButton::~MenuButton(void)
{
	OverlayManager* overlayMgr = OverlayManager::getSingletonPtr();
	overlayMgr->destroyOverlayElement(textarea);
}
// ------------------------------------------------------------------------------------------------------------
void MenuButton::update(float timeSinceLastFrame)
{
	// Update animations etc
	textarea->setCaption(buttonCaption);

	if (selected)
		clampedAnimateValue += 0.01f*timeSinceLastFrame;
	else
		clampedAnimateValue -= 0.01f*timeSinceLastFrame;

	if (clampedAnimateValue < 0)
		clampedAnimateValue = 0;

	if (clampedAnimateValue > 1)
		clampedAnimateValue = 1;

	float smoothedAnimateValue = Smootherstep(clampedAnimateValue);
	container->setWidth(8000 + smoothedAnimateValue*1000);
	textarea->setPosition(180 + Smootherstep(clampedAnimateValue)*100, 180);
	textarea->setColour(ColourValue(0.913f, 0.588f, 0.294f)*smoothedAnimateValue + ColourValue::White*(1-smoothedAnimateValue));
}
// ------------------------------------------------------------------------------------------------------------
String MenuButton::getCaption()
{
	return buttonCaption;
}
// ------------------------------------------------------------------------------------------------------------
