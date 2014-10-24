/************************************************************************/
/* @class TanksMain
 * @author Jack McCallum
 * 
 * @description
 * Expanded event loop for navigable interfaces 
 * like menus and what not.
 * Simplified input sums it up.
 * 
/************************************************************************/

#pragma once

#include "OgreMain.h"
#include "EventLoop.h"

class NavigatableInterface : public EventLoop
{
public:
	NavigatableInterface(OgreMain* oMain);

	// Open/close the menu, close should be controlled internally most likely
	virtual void open() = 0;
	virtual void close() = 0;

	// Virtual navigation methods
	virtual void navigateUp();
	virtual void navigateDown();
	virtual void navigateLeft();
	virtual void navigateRight();
	virtual void navigateForward();
	virtual void navigateBackward();
	virtual void navigateMouse(float mx, float my);

	// For updating animations and what not
	virtual void update(float timeSinceLastFrame) = 0;
	
	// Necessary input events
	virtual void eventMouseMoved(const JMMouseEvent &evt);
	virtual void eventMousePressed(const JMMouseEvent &evt);
	virtual void eventKeyboardKeyPressed(const JMKeyEvent &evt);

	// Frame events
	virtual void eventPreRender(const JMFrameEvent &evt);
};

