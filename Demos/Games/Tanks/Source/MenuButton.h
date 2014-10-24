/************************************************************************/
/* @class MenuButton
 * @author Jack McCallum
 * 
 * @description
 * Simple derivative of HUDElement, that allows a 
 * cute little animation for when you select 
 * items in a menu
 * 
 * More info in HUDElement.h
 * 
/************************************************************************/


#pragma once
#ifndef _MENU_BUTTON
#define _MENU_BUTTON

// Dependencies
#include "HUDElement.h"
#include "MathsMacros.h"

class MenuButton : public HUDElement
{
public:
	// Default constructor
	MenuButton(String caption, String name, Overlay* parent);
	// Destructor
	virtual ~MenuButton();

	// Update animations
	virtual void update(float timeSinceLastFrame);

	String getCaption();
	
protected:
	// Text element
	TextAreaOverlayElement* textarea;
	// Animating value used for linear interpolation
	float clampedAnimateValue;
	// Caption displayed on the element
	String buttonCaption;
};

#endif