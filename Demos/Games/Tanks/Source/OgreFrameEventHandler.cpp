#include "StdAfx.h"
#include "OgreFrameEventHandler.h"

	// ------------------------------------------------------------------------------------------------------------
	OgreFrameEventHandler::OgreFrameEventHandler(Ogre::Root* root, Ogre::RenderWindow* rw, Ogre::Camera* camera, int dfps, bool cap) 
		: JMFrameEventHandler(dfps, cap)
	{
		ogreRoot = root;
		renderWindow = rw;
		sceneCamera = camera;
	}
	// ------------------------------------------------------------------------------------------------------------
	void OgreFrameEventHandler::renderFrame()
	{
		ogreRoot->renderOneFrame();
	}
	// ------------------------------------------------------------------------------------------------------------
	int OgreFrameEventHandler::getWindowWidth()
	{
		return renderWindow->getWidth();
	}
	// ------------------------------------------------------------------------------------------------------------
	int OgreFrameEventHandler::getWindowHeight()
	{
		return renderWindow->getHeight();
	}
	// ------------------------------------------------------------------------------------------------------------
	bool OgreFrameEventHandler::getWindowClosed()
	{
		return renderWindow->isClosed();
	}
	// ------------------------------------------------------------------------------------------------------------
	void OgreFrameEventHandler::eventWindowResized(const JMFrameEvent &evt)
	{
		JMFrameEventHandler::eventWindowResized(evt);
		if (sceneCamera)
			sceneCamera->setAspectRatio(evt.windowWidth/(float)evt.windowHeight);
	}
