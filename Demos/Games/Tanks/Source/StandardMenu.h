/************************************************************************/
/* @class TanksMain
 * @author Jack McCallum
 * 
 * @description
 * Standard menu with a simple up/down interface
 * pause menu/main menu
 * 
/************************************************************************/

#pragma once

#include "NavigatableInterface.h"
#include "MenuButton.h"

class StandardMenu : public NavigatableInterface
{
public:
	// A Unique name and OgreMain pointer are mandatory
	StandardMenu(String uname, OgreMain* oMain);
	virtual ~StandardMenu();
	
	// Update animations etc...
	virtual void update(float timeSinceLastFrame);

	// Open/close the menu, close should be controlled internally most likely
	virtual void open();
	virtual void close();
	
	// Adds a button to the menu with a given name, upon pressing 
	// the button it returns the returnStr out of the event loop
	void addButton(String caption, String returnStr);
	void removeButton(String caption);

	// Navigate the standard menu
	virtual void navigateUp();
	virtual void navigateDown();
	virtual void navigateForward();
	virtual void navigateBackward();
	virtual void navigateMouse(float mx, float my);
	
private:
	String uniqueName;
	int uniqueNameGen;
	Overlay* menuOverlay;

	// List of the buttons in the menu
	std::list<MenuButton*> buttonList;
	std::list<MenuButton*>::iterator buttonIter;
};

