#include "StdAfx.h"
#include "JMMouseEventHandler.h"

// ------------------------------------------------------------------------------------------------------------
JMMouseEventHandler::JMMouseEventHandler(HWND wnd)
{
	windowHandle = wnd;

	for (int i=0; i<MB_END; i++)
	{
		mouseButtonDown[i] = false;
		mouseButtonPressed[i] = false;
		mouseButtonReleased[i] = false;
	}
}
// ------------------------------------------------------------------------------------------------------------
void JMMouseEventHandler::processMouseEvents(bool dontSendEvents)
{
	// ==========================
	// ===== Procees Movment ====
	// ========================== 
		
	// Don't try and use the window if it was closed or doesn't exist
	if (!IsWindow(windowHandle))
		return;
		
	POINT glob, wind;
	assert(GetCursorPos(&glob));
	wind = glob;
	assert(ScreenToClient(windowHandle, &wind));

	RECT rect;
	GetClientRect(windowHandle, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
			
	// Check if any of the cursor positions have chance since last time
	if (mouseData.globalX != glob.x ||
		mouseData.globalY != glob.y ||
		mouseData.windowX != wind.x ||
		mouseData.windowY != wind.y)
	{
		// Update relative positions
		mouseData.relativeX = glob.x - mouseData.globalX;
		mouseData.relativeY = glob.y - mouseData.globalY;
				
		// Update global positions
		mouseData.globalX = glob.x;
		mouseData.globalY = glob.y;

		// Update window positions
		mouseData.windowX = wind.x;
		mouseData.windowY = wind.y;

		// Update scaled positions
		mouseData.scaledX = mouseData.windowX/float(width);
		mouseData.scaledY = mouseData.windowY/float(height);

		// Send MouseMoved event
		// Only send the event if the window is active
		if (GetActiveWindow() == windowHandle && !dontSendEvents)
		{
			mouseData.button = MB_NOBUTTON;
			eventMouseMoved(mouseData);
		}
	}

	// ==========================
	// ===== Procees Buttons ====
	// ========================== 

	for (int i=0; i<MB_END; i++)
	{
		// We are checking key states from windows,
		// http://msdn.microsoft.com/en-us/library/dd375731%28VS.85%29.aspx
		// So we want to skip VK_CANCEL cause obviously its not a mouse button
		if (i == VK_CANCEL) continue;

		// Calculate Button Pressed for only 1 frame
		if (GetKeyState(i) < 0)
		{
			if (!mouseButtonDown[i])
				mouseButtonPressed[i] = true;
			else
				mouseButtonPressed[i] = false;

			mouseButtonDown[i] = true;
			mouseButtonReleased[i] = false;
		}
		// Calculate Button released for only 1 frame
		else
		{
			if (mouseButtonDown[i])
				mouseButtonReleased[i] = true;
			else
				mouseButtonReleased[i] = false;
			mouseButtonDown[i] = false;
			mouseButtonPressed[i] = false;
		}

		// Send appropriate events if window is active
		if (GetActiveWindow() == windowHandle && !dontSendEvents)
		{
			// Pressed Events
			if (mouseButtonPressed[i])
			{
				mouseData.button = (MouseButton)i;
				eventMousePressed(mouseData);
			}
			// Released Events
			else if (mouseButtonReleased[i])
			{
				mouseData.button = (MouseButton)i;
				eventMouseReleased(mouseData);
			}
		}

		// End loop
	}

}
// ------------------------------------------------------------------------------------------------------------
void JMMouseEventHandler::eventMouseMoved(const JMMouseEvent &evt)
{
	// Iterate all objects listening in on these events and send it to them
	listenerIter = listenerList.begin();
	while (listenerIter != listenerList.end())
	{
		static_cast<JMMouseEventListener*>(*listenerIter)->eventMouseMoved(evt);
		listenerIter++;
	}
}
// ------------------------------------------------------------------------------------------------------------
void JMMouseEventHandler::eventMousePressed(const JMMouseEvent &evt)
{
	// Iterate all objects listening in on these events and send it to them
	listenerIter = listenerList.begin();
	while (listenerIter != listenerList.end())
	{
		static_cast<JMMouseEventListener*>(*listenerIter)->eventMousePressed(evt);
		listenerIter++;
	}
}
// ------------------------------------------------------------------------------------------------------------
void JMMouseEventHandler::eventMouseReleased(const JMMouseEvent &evt)
{
	// Iterate all objects listening in on these events and send it to them
	listenerIter = listenerList.begin();
	while (listenerIter != listenerList.end())
	{
		static_cast<JMMouseEventListener*>(*listenerIter)->eventMouseReleased(evt);
		listenerIter++;
	}
}
