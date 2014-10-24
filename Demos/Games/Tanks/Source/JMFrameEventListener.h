/****************************************************
Author: 
	Jack McCallum

Class: 
	JMF::FrameEvtListener : public EventListener

Description: 
	This class listens in on FrameEvtHandler 
	and sends out events and FrameEvent parameters

****************************************************/

#pragma once
#ifndef JMF_FRAME_EVENT_LISTENER
#define JMF_FRAME_EVENT_LISTENER

// Dependencies
#include "JMEventListener.h"

// Event arguments
struct JMFrameEvent
{
	// Default constructor
	JMFrameEvent()
	{
		timeSinceLastFrame = 0;
		windowWidth = 0;
		windowHeight = 0;
	}
	// Simple constructor for quick access to this struct
	JMFrameEvent(float timFra, int wWid, int wHei)
	{
		timeSinceLastFrame = timFra;
		windowWidth = wWid;
		windowHeight = wHei;
	}

	// Time in milliseconds since last event
	float timeSinceLastFrame;
	// Window width in pixels
	int windowWidth;
	// Window Height in pixels
	int windowHeight;
};

// Sub class to listen in on the the FrameEventHandler
class JMFrameEventListener : public JMEventListener
{
public:
	// Called upon entering the event loop
	virtual void eventEnteringLoop(const JMFrameEvent &evt);
	// Called upon leaving the event loop
	virtual void eventLeavingLoop(const JMFrameEvent &evt);
	// Called before every frame is rendered
	virtual void eventPreRender(const JMFrameEvent &evt);
	// Called after every frame is rendered
	virtual void eventPostRender(const JMFrameEvent &evt);
	// Event called whenever the window has been resized
	virtual void eventWindowResized(const JMFrameEvent &evt);
};

#endif