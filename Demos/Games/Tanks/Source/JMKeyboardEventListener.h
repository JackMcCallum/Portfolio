/****************************************************
Author: 
	Jack McCallum

Class: 
	JMF::KeyboardEventListener : public JMF::EventListener

Description:
	Listener class for matching handler class
	Virtual event methods can be inherited as needed.
	for this to be able to receive events it must be added
	as a handler like:
	handler->addListener(listener);

	see JMFKeyboardEventHandler.h for more info

****************************************************/

#pragma once
#ifndef JMF_KEYBOARD_EVENT_LISTENER
#define JMF_KEYBOARD_EVENT_LISTENER

// Dependencies
#include "JMEventListener.h"

struct JMKeyEvent
{
	// Default constructor
	JMKeyEvent() 
	{
		key = 0;
	};

	JMKeyEvent(int k) 
	{
		key = k;
	};

	// key value VK____ or '_'
	int key;
};

class JMKeyboardEventListener : public JMEventListener
{
public:
	// Calls when mouse button pressed
	virtual void eventKeyboardKeyPressed(const JMKeyEvent &evt);
	// Calls when mouse button released
	virtual void eventKeyboardKeyReleased(const JMKeyEvent &evt);
};

#endif