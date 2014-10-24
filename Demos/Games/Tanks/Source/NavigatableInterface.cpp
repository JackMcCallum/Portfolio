#include "StdAfx.h"
#include "NavigatableInterface.h"

// ------------------------------------------------------------------------------------------------------------
NavigatableInterface::NavigatableInterface(OgreMain* oMain) : EventLoop(oMain)
{
	// Do Nothing
}
// ------------------------------------------------------------------------------------------------------------
void NavigatableInterface::navigateUp()
{
	// Do Nothing
}
// ------------------------------------------------------------------------------------------------------------
void NavigatableInterface::navigateDown()
{
	// Do Nothing
}
// ------------------------------------------------------------------------------------------------------------
void NavigatableInterface::navigateLeft()
{
	// Do Nothing
}
// ------------------------------------------------------------------------------------------------------------
void NavigatableInterface::navigateRight()
{
	// Do Nothing
}
// ------------------------------------------------------------------------------------------------------------
void NavigatableInterface::navigateForward()
{
	// Do Nothing
}
// ------------------------------------------------------------------------------------------------------------
void NavigatableInterface::navigateBackward()
{
	// Do Nothing
}
// ------------------------------------------------------------------------------------------------------------
void NavigatableInterface::navigateMouse(float mx, float my)
{
	// Do Nothing
}
// ------------------------------------------------------------------------------------------------------------
void NavigatableInterface::eventMousePressed(const JMMouseEvent &evt)
{
	if (evt.button == MB_LBUTTON)
		navigateForward();
}
// ------------------------------------------------------------------------------------------------------------
void NavigatableInterface::eventMouseMoved(const JMMouseEvent &evt)
{
	navigateMouse(evt.scaledX, evt.scaledY);
}
// ------------------------------------------------------------------------------------------------------------
void NavigatableInterface::eventKeyboardKeyPressed(const JMKeyEvent &evt)
{
	// Send appropriate navigation function
	switch (evt.key)
	{
	case 'W': 
		navigateUp();
		break;
	case 'A': 
		navigateLeft();
		break;
	case 'S': 
		navigateDown();
		break;
	case 'D': 
		navigateRight();
		break;
	case VK_UP: 
		navigateUp();
		break;
	case VK_LEFT: 
		navigateLeft();
		break;
	case VK_DOWN: 
		navigateDown();
		break;
	case VK_RIGHT: 
		navigateRight();
		break;
	case VK_BACK: 
		navigateBackward();
		break;
	case VK_ESCAPE: 
		navigateBackward();
		break;
	case VK_SPACE: 
		navigateForward();
		break;
	case VK_RETURN: 
		navigateForward();
		break;
	}
}
// ------------------------------------------------------------------------------------------------------------
void NavigatableInterface::eventPreRender(const JMFrameEvent &evt)
{
	processInput();
	update(evt.timeSinceLastFrame);
}
// ------------------------------------------------------------------------------------------------------------
