/************************************************************************/
/* @class TanksMain
 * @author Jack McCallum
 * 
 * @description
 * An interface element that displays my credits. used in Credits.h
 * 
/************************************************************************/

#pragma once

// Dependencies
#include "HUDElement.h"
#include "MathsMacros.h"

class CreditsDisplay : public HUDElement
{
public:
	CreditsDisplay(String name, Overlay* parent);
	virtual ~CreditsDisplay();

	virtual void update(float timeSinceLastFrame);
	
private:
	// Text element
	TextAreaOverlayElement* textareaTitles;
	TextAreaOverlayElement* textareaDesc;
	// Caption displayed on the element
	String titlesCaption;
	String descCaption;

};

