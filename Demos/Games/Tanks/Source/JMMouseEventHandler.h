/****************************************************
Author: 
	Jack McCallum

Class: 
	JMF::MouseEventHandler : public JMF::MouseEventListener, public JMF::EventHandler

Description: 
	Handler class for sending input events to the matching listener
	for this to work properly the process____Events(); method must be 
	called whenever necessary (every frame, or more).
	
	by doing process____Events(true);
	you are processing input without sending events allowing the handler to catch up
	on the input state if it has been pause for example, for example:
	if you have a button pressed and you resume this handler then the 
	buttonPressed event would be sent even if you're already holding the button down
	
	Window handle must be provided so input is not detected when window is not active

	see JMFMouseEventListener.h for more info

****************************************************/

#pragma once
#ifndef JMF_MOUSE_EVENT_HANDLER
#define JMF_MOUSE_EVENT_HANDLER

// Dependencies
#include "JMMouseEventListener.h"
#include "JMEventHandler.h"

class JMMouseEventHandler : public JMEventHandler
{
public:
	// Default constructor. 
	// HWND wnd - window handle to the window wanting to receive input
	JMMouseEventHandler(HWND wnd);

	// Function to process input for this class
	// bool dontSendEvents - process input but don't send events
	void processMouseEvents(bool dontSendEvents = false);

	// Called when mouse moves
	virtual void eventMouseMoved(const JMMouseEvent &evt);
	// Calls when mouse button pressed
	virtual void eventMousePressed(const JMMouseEvent &evt);
	// Calls when mouse button released
	virtual void eventMouseReleased(const JMMouseEvent &evt);
		
protected:
	// Window handle
	HWND windowHandle;

	// Variable for storing the event data
	JMMouseEvent mouseData;

	// Array button down state
	bool mouseButtonDown[MB_END];
	// Array button pressed state
	bool mouseButtonPressed[MB_END];
	// Array button released state
	bool mouseButtonReleased[MB_END];
};

#endif
