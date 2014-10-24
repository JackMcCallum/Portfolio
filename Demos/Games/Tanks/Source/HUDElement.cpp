#include "StdAfx.h"
#include "HUDElement.h"


// ------------------------------------------------------------------------------------------------------------
HUDElement::HUDElement(String name, Overlay* parent)
{
	elementName = name;
	parentOverlay = parent;

	selected = false;
	enable = true;
	hidden = false;

	// Create the parent container
	OverlayManager* overlayMgr = OverlayManager::getSingletonPtr();
	container = (OverlayContainer*)overlayMgr->createOverlayElement("Panel", name+"BaseContainer");
	parentOverlay->add2D(container);
}
// ------------------------------------------------------------------------------------------------------------
HUDElement::~HUDElement()
{
	OverlayManager* overlayMgr = OverlayManager::getSingletonPtr();
	overlayMgr->destroyOverlayElement(container);
}
// ------------------------------------------------------------------------------------------------------------
void HUDElement::setPosition(float x, float y)
{
	container->setPosition(x, y);
}
// ------------------------------------------------------------------------------------------------------------
void HUDElement::setSelected(bool val)
{
	selected = val;
}
// ------------------------------------------------------------------------------------------------------------
void HUDElement::setEnabled(bool val)
{
	enable = val;
}
// ------------------------------------------------------------------------------------------------------------
void HUDElement::setHidden(bool val)
{
	hidden = val;
}
// ------------------------------------------------------------------------------------------------------------
bool HUDElement::inside(float x, float y)
{
	// Check if X and Y is withing the area of the main container
	if (container)
	{
		float t, l, w, h;
		t = container->_getDerivedTop();
		l = container->_getDerivedLeft();
		w = container->_getRelativeWidth();
		h = container->_getRelativeHeight() ;

		if (y > t && y < t+h && x > l && x < l+w)
			return true;
	}

	return false;
}
// ------------------------------------------------------------------------------------------------------------
bool HUDElement::isSelected()
{
	return selected;
}
// ------------------------------------------------------------------------------------------------------------
bool HUDElement::isEnabled()
{
	return enable;
}
// ------------------------------------------------------------------------------------------------------------
bool HUDElement::isHidden()
{
	return hidden;
}
// ------------------------------------------------------------------------------------------------------------
Ogre::String HUDElement::getName()
{
	return elementName;
}
// ------------------------------------------------------------------------------------------------------------
void HUDElement::setOutput(String o)
{
	outputString = o;
}
// ------------------------------------------------------------------------------------------------------------
Ogre::String HUDElement::getOutput()
{
	return outputString;
}
// ------------------------------------------------------------------------------------------------------------
