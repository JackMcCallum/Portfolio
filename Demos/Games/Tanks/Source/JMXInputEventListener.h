/****************************************************
Author: 
	Jack McCallum

Class: 
	JMF::XInputEventListener : public JMF::EventListener

Description: 
	Listener class for matching handler class
	Virtual event methods can be inherited as needed.
	for this to be able to receive events it must be added
	as a handler like:
	handler->addListener(listener);

	see JMFXInputEventHandler.h for more info

****************************************************/

#pragma once
#ifndef JMF_XINPUT_EVENT_LISTENER
#define JMF_XINPUT_EVENT_LISTENER

// Dependencies
#include "JMEventListener.h"

// Button index enumeration for checking what button was pressed on the event called
enum XInputButtons 
{
	XB_DPAD_UP,			// 0x0001
	XB_DPAD_DOWN,		// 0x0002
	XB_DPAD_LEFT,		// 0x0004
	XB_DPAD_RIGHT,		// 0x0008
	XB_START,			// 0x0010
	XB_BACK,			// 0x0020
	XB_LEFT_THUMB,		// 0x0040
	XB_RIGHT_THUMB,		// 0x0080
	XB_LEFT_SHOULDER,	// 0x0100
	XB_RIGHT_SHOULDER,	// 0x0200
	XB_BLANK0,			// an xbox controller doesn't use 
	XB_BLANK1,			// 0x0400 or 0x0800 for some reason
	XB_A,				// 0x1000
	XB_B,				// 0x2000
	XB_X,				// 0x4000
	XB_Y,				// 0x8000
	XB_NOBUTTON
};
	
struct XInputJoy
{
	// Default constructor
	XInputJoy() 
	{
		axisx = 0;
		axisy = 0;
	}

	// Simple constructor for quick creation
	XInputJoy(float x, float y)
	{
		axisx = x;
		axisy = y;
	}

	// Trigger X axis -1 to 1
	float axisx;
	// Trigger Y axis -1 to 1
	float axisy;
};

struct XInputTrigger
{
	// Default constructor
	XInputTrigger() 
	{
		left = 0;
		right = 0;
	}

	// Simple constructor for quick creation
	XInputTrigger(float l, float r)
	{
		left = l;
		right = r;
	}

	// Clamped value of left trigger 1-0 with 0 being released
	float left;
	// Clamped value of right trigger 1-0 with 0 being released
	float right;
};

struct JMXInputEvent
{
	// Default constructor
	JMXInputEvent() 
	{
		joyleft = XInputJoy();
		joyright = XInputJoy();
		triggers = XInputTrigger();
		button = XB_NOBUTTON;
	};
	// Simple constructor for quick creation
	JMXInputEvent(float jleftx, float jlefty, float jrightx, float jrighty, float trigleft, float trigright, float , XInputButtons btn = XB_NOBUTTON) 
	{
		joyleft.axisx = jleftx;
		joyleft.axisy = jlefty;

		joyright.axisx = jrightx;
		joyright.axisy = jrighty;

		triggers.left = trigleft;
		triggers.right = trigright;

		button = btn;
	};
	// Simple constructor for quick creation
	JMXInputEvent(XInputJoy jleft, XInputJoy jright, XInputTrigger trig, XInputButtons btn = XB_NOBUTTON)
	{
		joyleft = jleft;
		joyright = jright;
		triggers = trig;
		button = btn;
	};

	// Data for left joy stick
	XInputJoy joyleft;
	// Data for right joy stick
	XInputJoy joyright;
	// Data for triggers
	XInputTrigger triggers;
	// Data for all buttons
	XInputButtons button;
};

class JMXInputEventListener : public JMEventListener
{
public:
	// Calls when a joy stick was moved
	virtual void eventXInputJoyMoved(const JMXInputEvent &evt);
	// Calls when a trigger has been moved
	virtual void eventXInputTriggerMoved(const JMXInputEvent &evt);
	// Calls when button pressed
	virtual void eventXInputButtonPressed(const JMXInputEvent &evt);
	// Calls when button released
	virtual void eventXInputButtonReleased(const JMXInputEvent &evt);
};

#endif