#include "StdAfx.h"
#include "JMXInputEventHandler.h"

// ------------------------------------------------------------------------------------------------------------
JMXInputEventHandler::JMXInputEventHandler(HWND wnd)
{
	windowHandle = wnd;
}
// ------------------------------------------------------------------------------------------------------------
void JMXInputEventHandler::processXInputEvents(bool dontSendEvents)
{
	// Don't try and use the window if it was closed or doesn't exist
	if (!IsWindow(windowHandle))
		return;

	XINPUT_STATE state;
	if (XInputGetState(0, &state) != ERROR_SUCCESS)
		return;
	else
	{
		// ========================
		// Process Joy Input
		// ========================

		// Reconstruct left analog stick vector with subtracted dead zone
		float dist, dire;
		XInputJoy left, right, newleft, newright;
			
		// Store data from input query
		left.axisx = state.Gamepad.sThumbLX/32767.0f;
		left.axisy = state.Gamepad.sThumbLY/32767.0f;
		right.axisx = state.Gamepad.sThumbRX/32767.0f;
		right.axisy = state.Gamepad.sThumbRY/32767.0f;

		// Process left joy dead zone
		dist = sqrt(left.axisx*left.axisx + left.axisy*left.axisy);
		if (dist > XB_JOY_DEADZONE) 
		{
			dist -= XB_JOY_DEADZONE;
			dist *= 1/(1-XB_JOY_DEADZONE);
			dire = atan2(left.axisy, left.axisx) / PI * 180;
			newleft.axisx =  cos(dire*PI/180)*dist;
			newleft.axisy = -sin(dire*PI/180)*dist;
		}
		else
		{
			newleft.axisx = 0;
			newleft.axisy = 0;
		}
			
		// Process right joy dead zone
		dist = sqrt(right.axisx*right.axisx + right.axisy*right.axisy);
		if (dist > XB_JOY_DEADZONE) 
		{
			dist -= XB_JOY_DEADZONE;
			dist *= 1/(1-XB_JOY_DEADZONE);
			dire = atan2(right.axisy, right.axisx) / PI * 180;
			newright.axisx =  cos(dire*PI/180)*dist;
			newright.axisy = -sin(dire*PI/180)*dist;
		}
		else
		{
			newright.axisx = 0;
			newright.axisy = 0;
		}

			
		// ========================
		// Process Trigger Input
		// ========================

		XInputTrigger trig, newtrig;

		trig.left = state.Gamepad.bLeftTrigger/255.0f;
		trig.right = state.Gamepad.bRightTrigger/255.0f;

		if (trig.left > XB_TRIGGER_DEADZONE)
			newtrig.left = (trig.left-XB_TRIGGER_DEADZONE)/(1-XB_TRIGGER_DEADZONE);
		else 
			newtrig.left = 0.0f;

		if (trig.right > XB_TRIGGER_DEADZONE)
			newtrig.right = (trig.right-XB_TRIGGER_DEADZONE)/(1-XB_TRIGGER_DEADZONE);
		else 
			newtrig.right = 0.0f;

		// ========================
		// Process Button Input
		// ========================


		// From the button down information...
		for (int i=0; i<XB_NOBUTTON; i++)
		{
			// Skip 10 and 11 as they are not used by XInput
			if (i == 10 || i == 11) continue;

			int btn = int(pow(2, (float)i));
			if ((state.Gamepad.wButtons & btn) == btn)
			{
				if (!xInputButtonDown[i])
					xInputButtonPressed[i] = true;
				else
					xInputButtonPressed[i] = false;
				xInputButtonDown[i] = true;
				xInputButtonReleased[i] = false;
			}
			else
			{
				if (xInputButtonDown[i])
					xInputButtonReleased[i] = true;
				else
					xInputButtonReleased[i] = false;
				xInputButtonDown[i] = false;
				xInputButtonPressed[i] = false;
			}

			if (xInputButtonPressed[i])
			{
				xInputdata.button = (XInputButtons)i;
				eventXInputButtonPressed(xInputdata);
			}

			if (xInputButtonReleased[i])
			{
				xInputdata.button = (XInputButtons)i;
				eventXInputButtonReleased(xInputdata);
			}

		}


			


		// ========================
		// Send the events
		// ========================

		// Send appropriate events if window is active
		if (GetActiveWindow() == windowHandle && !dontSendEvents)
		{

			if (newtrig.left != xInputdata.triggers.left ||
				newtrig.right != xInputdata.triggers.right)
			{
				xInputdata.triggers.left = newtrig.left;
				xInputdata.triggers.right = newtrig.right;

				xInputdata.button = XB_NOBUTTON;
				eventXInputTriggerMoved(xInputdata);
			}

			// Check if any of the axis's have changed, if they have send an event
			if (newleft.axisx != xInputdata.joyleft.axisx || 
				newleft.axisy != xInputdata.joyleft.axisy ||
				newright.axisx != xInputdata.joyright.axisx || 
				newright.axisy != xInputdata.joyright.axisy)
			{
				xInputdata.joyleft.axisx = newleft.axisx;
				xInputdata.joyleft.axisy = newleft.axisy;

				xInputdata.joyright.axisx = newright.axisx;
				xInputdata.joyright.axisy = newright.axisy;

				xInputdata.button = XB_NOBUTTON;
				eventXInputJoyMoved(xInputdata);
			}
		}


	}
}
// ------------------------------------------------------------------------------------------------------------
void JMXInputEventHandler::eventXInputJoyMoved(const JMXInputEvent &evt)
{
	// Iterate all objects listening in on these events and send it to them
	listenerIter = listenerList.begin();
	while (listenerIter != listenerList.end())
	{
		static_cast<JMXInputEventListener*>(*listenerIter)->eventXInputJoyMoved(evt);
		listenerIter++;
	}
}
// ------------------------------------------------------------------------------------------------------------
void JMXInputEventHandler::eventXInputTriggerMoved(const JMXInputEvent &evt)
{
	// Iterate all objects listening in on these events and send it to them
	listenerIter = listenerList.begin();
	while (listenerIter != listenerList.end())
	{
		static_cast<JMXInputEventListener*>(*listenerIter)->eventXInputTriggerMoved(evt);
		listenerIter++;
	}
}
// ------------------------------------------------------------------------------------------------------------
void JMXInputEventHandler::eventXInputButtonPressed(const JMXInputEvent &evt)
{
	// Iterate all objects listening in on these events and send it to them
	listenerIter = listenerList.begin();
	while (listenerIter != listenerList.end())
	{
		static_cast<JMXInputEventListener*>(*listenerIter)->eventXInputButtonPressed(evt);
		listenerIter++;
	}
}
// ------------------------------------------------------------------------------------------------------------
void JMXInputEventHandler::eventXInputButtonReleased(const JMXInputEvent &evt)
{
	// Iterate all objects listening in on these events and send it to them
	listenerIter = listenerList.begin();
	while (listenerIter != listenerList.end())
	{
		static_cast<JMXInputEventListener*>(*listenerIter)->eventXInputButtonReleased(evt);
		listenerIter++;
	}
}
