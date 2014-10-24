/****************************************************
Author: 
	Jack McCallum

Class: 
	JMF::MouseEventListener : public JMF::EventListener

Description: 
	Listener class for matching handler class
	Virtual event methods can be inherited as needed.
	for this to be able to receive events it must be added
	as a handler like:
	handler->addListener(listener);

	see JMFMouseEventHandler.h for more info

****************************************************/

#pragma once
#ifndef JMF_MOUSE_EVENT_LISTENER
#define JMF_MOUSE_EVENT_LISTENER

// Dependencies
#include "JMEventListener.h"

// Mouse key states that can be used to check the state of an event
enum MouseButton
{
	MB_NOBUTTON = 0x00,
	MB_LBUTTON = 0x01, // VK_LBUTTON
	MB_RBUTTON = 0x02, // VK_RBUTTON
	MB_MBUTTON = 0x04, // VK_MBUTTON
	MB_XBUTTON1 = 0x05, // VK_XBUTTON1
	MB_XBUTTON2 = 0x06, // VK_XBUTTON2
	MB_END
};

struct JMMouseEvent
{
	// Default constructor
	JMMouseEvent() 
	{
		globalX = 0;
		globalY = 0;
		windowX = 0;
		windowY = 0;
		relativeX = 0;
		relativeY = 0;
		scaledX = 0;
		scaledY = 0;
		button = MB_NOBUTTON;
	};

	// Simple constructor for quick access to this struct
	JMMouseEvent(int gx, int gy, int wx, int wy, int rx, int ry, float sx, float sy, MouseButton btn = MB_NOBUTTON)
	{
		globalX = gx;
		globalY = gy;
		windowX = wx;
		windowY = wy;
		relativeX = rx;
		relativeY = ry;
		scaledX = sx;
		scaledY = sy;
		button = btn;
	}
		
	// Global mouse X position, relative to your monitor
	int globalX;
	// Global mouse Y position, relative to your monitor
	int globalY;

	// Window mouse X position, relative to the window
	int windowX;
	// Window mouse Y position, relative to the window
	int windowY;

	// Relative mouse X position, relative to the last mouse position
	int relativeX; 
	// Relative mouse Y position, relative to the last mouse position
	int relativeY;

	// Scaled mouse X position between 0 and 1 of the window
	float scaledX;
	// Scaled mouse Y position between 0 and 1 of the window
	float scaledY;

	MouseButton button;
};

class JMMouseEventListener : public JMEventListener
{
public:
	// Called when mouse moves
	virtual void eventMouseMoved(const JMMouseEvent &evt);
	// Calls when mouse button pressed
	virtual void eventMousePressed(const JMMouseEvent &evt);
	// Calls when mouse button released
	virtual void eventMouseReleased(const JMMouseEvent &evt);
};

#endif