/************************************************************************/
/* @class TanksMain
 * @author Jack McCallum
 * 
 * @description
 * Event look to display the credits. 
 * 
/************************************************************************/

#pragma once

#include "NavigatableInterface.h"
#include "MenuButton.h"
#include "Credits.h"
#include "CreditsDisplay.h"

class Credits : public NavigatableInterface
{
public:
	Credits(String uname, OgreMain* oMain);
	virtual ~Credits();

	// Open/close the menu, close should be controlled internally most likely
	virtual void open();
	virtual void close();

	// Update animations etc...
	virtual void update(float timeSinceLastFrame);
	
	// Navigate the standard menu
	virtual void navigateUp();
	virtual void navigateDown();
	virtual void navigateForward();
	virtual void navigateBackward();
	virtual void navigateMouse(float mx, float my);

private:
	Overlay* overlay;
	MenuButton* backButton;
	CreditsDisplay* creditsPane;

};

