 /****************************************************
Author: 
	Jack McCallum

Class: 
	FrameEvtHandler

Inherits: 
	public FrameEvtListener

Description: 
	This class is a render event handler,
	it emits events:
		- pre render
		- post render
		- render loop begin
		- render loop end
		- window resized

	It is an abstract class that needs to be 
	implemented to suit the render engine
	being used.

****************************************************/

#pragma once

// Dependencies
#include "JMEventHandler.h"
#include "JMFrameEventListener.h"
#include "JMTimer.h"

class JMFrameEventHandler : public JMEventHandler
{
public:
	// Constructor optional quick setup with the functions
	JMFrameEventHandler(int dfps = 60, bool cap = true);
		
	// Event loop control
	void beginFrameLoop();
	void endFrameLoop();

	// For changing the fps
	void setDesiredFps(int dfps);
	void setCapFps(bool cap);
		
	// Abstract functions to be reimplemented 
	// for the render engine being used.
	// Tells the engine to render
	virtual void renderFrame() = 0;
	// Gets width of render window
	virtual int getWindowWidth() = 0;
	// Gets height of render window
	virtual int getWindowHeight() = 0;
	// Gets if the render window is closed
	virtual bool getWindowClosed() = 0;

	// Inherited members from FrameEvtListener
	// These ones in particular send this even to all others listening
	// See FrameEvtListener.h for more description
	virtual void eventPreRender(const JMFrameEvent &evt);
	virtual void eventPostRender(const JMFrameEvent &evt);
	virtual void eventEnteringLoop(const JMFrameEvent &evt);
	virtual void eventLeavingLoop(const JMFrameEvent &evt);
	virtual void eventWindowResized(const JMFrameEvent &evt);

protected:
		
	// If capFps = true, the handler will attempt 
	// to keep the frame rate stable at desiredFps 
	// For truly accurate ~60 fps VSync works best :3
	int desiredFps;

	// To cap or not
	bool capFps;

	// Cleaner way of breaking out
	bool continueLooping;
		
	// Window resolutions so we can compare sizes 
	// and call resizeEvent if necessary
	int resolutionWidth, resolutionHeight;

	// Timers for controlling frame rate
	// They are static so they all frame looks 
	// share the timer and don't get too jumpy when leaving/entering 
	// as they pickup from where the previous one left off
	
public:
	static JMTimer sleepTimer;
	static JMTimer frameTimer;
};