#include "StdAfx.h"
#include "JMFrameEventHandler.h"

JMTimer JMFrameEventHandler::sleepTimer;
JMTimer JMFrameEventHandler::frameTimer;


// ------------------------------------------------------------------------------------------------------------
JMFrameEventHandler::JMFrameEventHandler(int dfps, bool cap)
{
	setDesiredFps(dfps);
	setCapFps(cap);
}
// ------------------------------------------------------------------------------------------------------------
void JMFrameEventHandler::beginFrameLoop()
{
	// This is how we end the loop
	continueLooping = true;
		
	// Call all entering events before entering the loop
	std::cout << "Entering frame event loop" << std::endl;
	eventEnteringLoop(JMFrameEvent(0,resolutionWidth,resolutionHeight));

	float timeSinceLastFrame = 0;
	float sleepTime = 0;

	// Reset the timers
	sleepTimer.reset();
	frameTimer.reset();

	// Enter to loop :D
	while (continueLooping)
	{
		// Keep window alive with ogres window message pump
		//WindowEventUtilities::messagePump();

		// Windows Message Loop (NULL means check all HWNDs belonging to this context)\
		// from: https://bitbucket.org/sinbad/ogre/src/37761c6b69e7/OgreMain/src/OgreWindowEventUtilities.cpp
		MSG  msg;
		while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		// Resize Event
		if (getWindowWidth() != resolutionWidth || getWindowHeight() != resolutionHeight)
		{
			resolutionWidth = getWindowWidth();
			resolutionHeight = getWindowHeight();
			//std::cout << "Window Resized" << std::endl;
			eventWindowResized(JMFrameEvent(timeSinceLastFrame,resolutionWidth,resolutionHeight));
		}

		sleepTimer.reset();

		// Call all pre render events
		eventPreRender(JMFrameEvent(timeSinceLastFrame,resolutionWidth,resolutionHeight));
		
		if (!continueLooping)
			break;

		// Render the frame
		renderFrame();

		// Call all post render events
		eventPostRender(JMFrameEvent(timeSinceLastFrame,resolutionWidth,resolutionHeight));
		
		// For truly accurate ~60 fps VSync works best :3
		// Sleep the necessary amount of time 
		sleepTime = ((1000.0f/(desiredFps)) - sleepTimer.getms());
		if (sleepTime > 0.0f) Sleep((DWORD)sleepTime);
		
		timeSinceLastFrame = frameTimer.getms();
		frameTimer.reset();

		// Check if the window has been closed before continuing
		if (getWindowClosed())
			continueLooping = false;
	}

	// Call all leaving events after leaving the loop
	std::cout << "Leaving frame event loop" << std::endl;
	eventLeavingLoop(JMFrameEvent(timeSinceLastFrame,resolutionWidth,resolutionHeight));

}
// ------------------------------------------------------------------------------------------------------------
void JMFrameEventHandler::endFrameLoop()
{
	continueLooping = false;
}
// ------------------------------------------------------------------------------------------------------------
void JMFrameEventHandler::setDesiredFps(int dfps)
{
	if (dfps > 0)
		desiredFps = dfps;
	else
		desiredFps = 60;
}
// ------------------------------------------------------------------------------------------------------------
void JMFrameEventHandler::setCapFps(bool cap)
{
	capFps = cap;
}


// I'd love to know if theres a shortcut to doing the following
// Instead of writing the while loop 5 times.
// Couldn't seem to find anything on google.
// ------------------------------------------------------------------------------------------------------------
void JMFrameEventHandler::eventPreRender(const JMFrameEvent &evt)
{
	// Iterate all objects listening in on these events and send it to them
	listenerIter = listenerList.begin();
	while (listenerIter != listenerList.end())
	{
		static_cast<JMFrameEventListener*>(*listenerIter)->eventPreRender(evt);
		listenerIter++;
	}
}
// ------------------------------------------------------------------------------------------------------------
void JMFrameEventHandler::eventPostRender(const JMFrameEvent &evt)
{
	// Iterate all objects listening in on these events and send it to them
	listenerIter = listenerList.begin();
	while (listenerIter != listenerList.end())
	{
		static_cast<JMFrameEventListener*>(*listenerIter)->eventPostRender(evt);
		listenerIter++;
	}
}
// ------------------------------------------------------------------------------------------------------------
void JMFrameEventHandler::eventEnteringLoop(const JMFrameEvent &evt)
{
	// Iterate all objects listening in on these events and send it to them
	listenerIter = listenerList.begin();
	while (listenerIter != listenerList.end())
	{
		static_cast<JMFrameEventListener*>(*listenerIter)->eventEnteringLoop(evt);
		listenerIter++;
	}
}
// ------------------------------------------------------------------------------------------------------------
void JMFrameEventHandler::eventLeavingLoop(const JMFrameEvent &evt)
{
	// Iterate all objects listening in on these events and send it to them
	listenerIter = listenerList.begin();
	while (listenerIter != listenerList.end())
	{
		static_cast<JMFrameEventListener*>(*listenerIter)->eventLeavingLoop(evt);
		listenerIter++;
	}
}
// ------------------------------------------------------------------------------------------------------------
void JMFrameEventHandler::eventWindowResized(const JMFrameEvent &evt)
{
	// Iterate all objects listening in on these events and send it to them
	listenerIter = listenerList.begin();
	while (listenerIter != listenerList.end())
	{
		static_cast<JMFrameEventListener*>(*listenerIter)->eventWindowResized(evt);
		listenerIter++;
	}

}
