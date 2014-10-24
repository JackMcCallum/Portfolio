#include "StdAfx.h"
#include "JMKeyboardEventHandler.h"

// ------------------------------------------------------------------------------------------------------------
JMKeyboardEventHandler::JMKeyboardEventHandler(HWND wnd)
{
	windowHandle = wnd;

	// Zero the memory
	for (int i=0; i<KEY_MAX; i++)
	{
		keyboardButtonDown[i] = false;
		keyboardButtonReleased[i] = false;
		keyboardButtonPressed[i] = false;
	}
}
// ------------------------------------------------------------------------------------------------------------
void JMKeyboardEventHandler::processKeyboardEvents(bool dontSendEvents)
{

	// ==========================
	// ====== Procees Keys ======
	// ========================== 

	for (int i=0; i<KEY_MAX; i++)
	{
		// Skip the mouse buttons
		if (i == VK_LBUTTON ||
			i == VK_RBUTTON || 
			i == VK_MBUTTON ||
			i == VK_XBUTTON1 ||
			i == VK_XBUTTON2)
			continue;

		// Calculate Button Pressed for only 1 frame
		if (GetKeyState(i) < 0)
		{
			if (!keyboardButtonDown[i])
				keyboardButtonPressed[i] = true;
			else
				keyboardButtonPressed[i] = false;

			keyboardButtonDown[i] = true;
			keyboardButtonReleased[i] = false;
		}
		// Calculate Button released for only 1 frame
		else
		{
			if (keyboardButtonDown[i])
				keyboardButtonReleased[i] = true;
			else
				keyboardButtonReleased[i] = false;
		
			keyboardButtonDown[i] = false;
			keyboardButtonPressed[i] = false;
		}

		// Send appropriate events if window is active
		if (GetActiveWindow() == windowHandle && !dontSendEvents)
		{
			// Pressed Events
			if (keyboardButtonPressed[i])
				eventKeyboardKeyPressed(JMKeyEvent(i));
			// Released Events
			else if (keyboardButtonReleased[i])
				eventKeyboardKeyReleased(JMKeyEvent(i));

		}

		// End loop
	}
}
// ------------------------------------------------------------------------------------------------------------
void JMKeyboardEventHandler::eventKeyboardKeyPressed(const JMKeyEvent &evt)
{
	// Iterate all objects listening in on these events and send it to them
	listenerIter = listenerList.begin();
	while (listenerIter != listenerList.end())
	{
		static_cast<JMKeyboardEventListener*>(*listenerIter)->eventKeyboardKeyPressed(evt);
		listenerIter++;
	}
}
// ------------------------------------------------------------------------------------------------------------
void JMKeyboardEventHandler::eventKeyboardKeyReleased(const JMKeyEvent &evt)
{
	// Iterate all objects listening in on these events and send it to them
	listenerIter = listenerList.begin();
	while (listenerIter != listenerList.end())
	{
		static_cast<JMKeyboardEventListener*>(*listenerIter)->eventKeyboardKeyReleased(evt);
		listenerIter++;
	}
}
