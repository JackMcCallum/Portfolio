#include "StdAfx.h"
#include "CreditsDisplay.h"


// ------------------------------------------------------------------------------------------------------------
CreditsDisplay::CreditsDisplay(String name, Overlay* parent) : HUDElement(name, parent)
{
	// Setup the main container
	container->setMaterialName("Material_MenuItemBackground");
	container->setMetricsMode(GMM_RELATIVE_ASPECT_ADJUSTED);
	container->setWidth(12000);
	container->setPosition(-6000,800);
	container->setHeight(6000);
	container->setHorizontalAlignment(GHA_CENTER);

	// Set the text captions
	// Orange text
	titlesCaption = 
		"PROGRAMMING & ART\n\n\n"
		"SOFTWARE USED\n\n\n\n\n"
		"FONT";

	// White text
	descCaption = 
		"\n"
		"Jack McCallum\n\n\n"
		"Photoshop CS6\n"
		"Blender 2.6\n"
		"Ogre3D 1.8\n\n\n"
		"Eurostile Extended";

	// Create the text area for the orange text
	OverlayManager* overlayMgr = OverlayManager::getSingletonPtr();
	textareaTitles = (TextAreaOverlayElement*)overlayMgr->createOverlayElement("TextArea", name+"Titles");
	textareaTitles->setMetricsMode(GMM_RELATIVE_ASPECT_ADJUSTED);
	textareaTitles->setFontName("MenuFont");
	textareaTitles->setCharHeight(400);
	textareaTitles->setPosition(180, 180);
	textareaTitles->setColour(ColourValue(0.913f, 0.588f, 0.294f));
	container->addChild(textareaTitles);

	// Create the text area for the white text
	textareaDesc = (TextAreaOverlayElement*)overlayMgr->createOverlayElement("TextArea", name+"Descriptions");
	textareaDesc->setMetricsMode(GMM_RELATIVE_ASPECT_ADJUSTED);
	textareaDesc->setFontName("MenuFont");
	textareaDesc->setCharHeight(400);
	textareaDesc->setPosition(180, 180);
	textareaDesc->setColour(ColourValue::White);
	container->addChild(textareaDesc);
}
// ------------------------------------------------------------------------------------------------------------
CreditsDisplay::~CreditsDisplay()
{
	// Clean up
	OverlayManager* overlayMgr = OverlayManager::getSingletonPtr();
	overlayMgr->destroyOverlayElement(textareaTitles);
	overlayMgr->destroyOverlayElement(textareaDesc);
}
// ------------------------------------------------------------------------------------------------------------
void CreditsDisplay::update(float timeSinceLastFrame)
{
	// Update, even thou
	textareaTitles->setCaption(titlesCaption);
	textareaDesc->setCaption(descCaption);
}
// ------------------------------------------------------------------------------------------------------------