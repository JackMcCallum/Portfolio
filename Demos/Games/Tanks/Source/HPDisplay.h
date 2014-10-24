/************************************************************************/
/* @class TanksMain
 * @author Jack McCallum
 * 
 * @description
 * Interface element that displays a number in the bottom left hand of the screen
 * For the health
 * 
/************************************************************************/

#pragma once
#include "HUDElement.h"

class HPDisplay : public HUDElement
{
public:
	HPDisplay(String name, Overlay* parent, float& hp);
	virtual ~HPDisplay();

	virtual void update(float timeSinceLastFrame);

private:

	// Text element
	TextAreaOverlayElement* textarea;
	// Text element
	TextAreaOverlayElement* titlearea;

	float displayHP;
	float actualHP;
	float& linkedHP;

};










