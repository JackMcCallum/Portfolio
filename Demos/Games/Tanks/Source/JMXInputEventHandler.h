/****************************************************
By Jack McCallum

Handler class for sending input events to the matching listener
for this to work properly the process____Events(); method must be 
called whenever necessary (every frame, or more).

by doing process____Events(true);
you are processing input without sending events allowing the handler to catch up
on the input state if it has been pause for example, for example:
if you have a button pressed and you resume this handler then the 
buttonPressed event would be sent even if you're already holding the button down

Window handle must be provided so input is not detected when window is not active

see JMFXInputEventListener.h for more info

****************************************************/

#pragma once
#ifndef JMF_XINPUT_EVENT_HANDLER
#define JMF_XINPUT_EVENT_HANDLER

#define XB_JOY_DEADZONE 0.18f
#define XB_TRIGGER_DEADZONE 0.10f

#define PI 3.14159265359f

// Dependencies
#include "JMXInputEventListener.h"
#include "JMEventHandler.h"

class JMXInputEventHandler : public JMXInputEventListener, public JMEventHandler
{
public:
	// Default constructor. 
	// HWND wnd - window handle to the window wanting to receive input
	JMXInputEventHandler(HWND wnd);

	// Function to process input for this class
	// bool dontSendEvents - process input but don't send events
	void processXInputEvents(bool dontSendEvents = false);

	// Calls when a joy stick was moved
	virtual void eventXInputJoyMoved(const JMXInputEvent &evt);
	// Calls when a trigger has been moved
	virtual void eventXInputTriggerMoved(const JMXInputEvent &evt);
	// Calls when button pressed
	virtual void eventXInputButtonPressed(const JMXInputEvent &evt);
	// Calls when button released
	virtual void eventXInputButtonReleased(const JMXInputEvent &evt);

protected:
	// Window handle
	HWND windowHandle;
		
	// Variable for storing the event data
	JMXInputEvent xInputdata;

	// Array button down state
	bool xInputButtonDown[XB_NOBUTTON];
	// Array button pressed state
	bool xInputButtonPressed[XB_NOBUTTON];
	// Array button released state
	bool xInputButtonReleased[XB_NOBUTTON];
};

#endif
