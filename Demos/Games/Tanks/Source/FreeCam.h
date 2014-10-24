/************************************************************************/
/* @class FreeCam
 * @author Jack McCallum
 * 
 * @description
 * This is a dialog intended for use as a menu.
 * In this case, I'm using it for my pause menu and main menu,
 * There are 3 possible states this class can be in:
 * Animating in, animating out and idle,
 * This derivative of DialogScreen takes use of goUp, goDown and goForward.
 * All menus MUST have a unique name or ogre will fall over.
 * 
 * Using a menu is as simple as:
 * MenuDialog* menu = new MenuDialog("Unique Name", Pointer to ogre main class)
 * menu->addButton("Button0");
 * menu->addButton("Button1");
 * etc...
 * menu->open();
 * 
 * More detailed info in the description of DialogScreen.h
 * 
/************************************************************************/

#pragma once

// Dependencies
#include "EventLoop.h"

class FreeCam : public EventLoop
{
public:
	// Default constructor
	FreeCam(OgreMain* oMain);
	
	// Called before every frame
	virtual void eventPreRender(const JMFrameEvent &evt);
	// Called on keyboard key pressed
	virtual void eventKeyboardKeyPressed(const JMKeyEvent &evt);
	// Called on keyboard key released
	virtual void eventKeyboardKeyReleased(const JMKeyEvent &evt);
	// Called when mouse moved
	virtual void eventMouseMoved(const JMMouseEvent &evt);
	// Called when mouse button pressed
	virtual void eventMousePressed(const JMMouseEvent &evt);
	// Called when mouse button released
	virtual void eventMouseReleased(const JMMouseEvent &evt);

protected:
	// Pointer to the camera
	Camera* camera;
	// If your holding down the right mouse button
	bool cameraDrag;
	// Down states for keyboard input
	bool wDown, aDown, sDown, dDown;
};
