/****************************************************
Author: 
	Jack McCallum

Class: 
	JMF::KeyboardEventHandler : public JMF::KeyboardEventListener, public JMF::EventHandler

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

	see JMFKeyboardEventListener.h for more info

****************************************************/

#pragma once
#ifndef JMF_KEYBOARD_EVENT_HANDLER
#define JMF_KEYBOARD_EVENT_HANDLER

#define KEY_MAX 0xFF

// Dependencies
#include "JMKeyboardEventListener.h"
#include "JMEventHandler.h"

class JMKeyboardEventHandler : public JMEventHandler
{
public:
	// Default constructor. 
	// HWND wnd - window handle to the window wanting to receive input
	JMKeyboardEventHandler(HWND wnd);

	// Function to process input for this class
	// bool dontSendEvents - process input but don't send events
	void processKeyboardEvents(bool dontSendEvents = false);

	// Calls when mouse button pressed
	virtual void eventKeyboardKeyPressed(const JMKeyEvent &evt);
	// Calls when mouse button released
	virtual void eventKeyboardKeyReleased(const JMKeyEvent &evt);

protected:
	// Window handle
	HWND windowHandle;

	// Array button down state
	bool keyboardButtonDown[KEY_MAX];
	// Array button pressed state
	bool keyboardButtonPressed[KEY_MAX];
	// Array button released state
	bool keyboardButtonReleased[KEY_MAX];
};

#endif
