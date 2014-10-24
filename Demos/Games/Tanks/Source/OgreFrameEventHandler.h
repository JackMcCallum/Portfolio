/************************************************************************/
/* @class OgreFrameEventHandler
 * @author Jack McCallum
 * 
 * @description
 * This is the derivative of FrameEventHandler with an
 * Ogre3D implementation. This class implements the abstract 
 * methods to be able to process the event loop properly 
 * using Ogre3D.
 * 
/************************************************************************/

#pragma once

#include "JMFrameEventHandler.h"

class OgreFrameEventHandler : public JMFrameEventHandler
{
public:
	// Pointer to Ogres singleton root, pointer to the render window, desired FPS, to cap fps
	OgreFrameEventHandler(Ogre::Root* root, Ogre::RenderWindow* rw, Ogre::Camera* camera, int dfps = 60, bool cap = true);

	// Abstract functions to be reimplemented 
	// for the render engine being used.
	// Tells the engine to render
	virtual void renderFrame();
	// Gets width of render window
	virtual int getWindowWidth();
	// Gets height of render window
	virtual int getWindowHeight();
	// Gets if the render window is closed
	virtual bool getWindowClosed();

	// So that we can correct the aspect of our camera(s)
	virtual void eventWindowResized(const JMFrameEvent &evt);

private:
	// Pointers to control Ogre
	Ogre::Root* ogreRoot;
	Ogre::RenderWindow* renderWindow;
	Ogre::Camera* sceneCamera;
};
