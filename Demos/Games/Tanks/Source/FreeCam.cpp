#include "StdAfx.h"
#include "FreeCam.h"

// ------------------------------------------------------------------------------------------------------------
FreeCam::FreeCam(OgreMain* oMain) : EventLoop(oMain)
{
	// Get the camera
	camera = ogreMain->getCamera();

	// Zero memory
	wDown = false;
	aDown = false;
	sDown = false;
	dDown = false;
	cameraDrag = false;
}
// ------------------------------------------------------------------------------------------------------------
void FreeCam::eventPreRender(const JMFrameEvent &evt)
{
	// Process input
	processInput();

	// the player is causing the cameras up vector to be horizontal, so fix that up while we go freecam
	ogreMain->getCamera()->setFixedYawAxis(true, Vector3(0,1,0));

	// Move camera appropriately according to the keyboard input
	if (wDown) camera->moveRelative(Vector3(0,0,-0.08f*evt.timeSinceLastFrame));
	if (aDown) camera->moveRelative(Vector3(-0.08f*evt.timeSinceLastFrame,0,0));
	if (sDown) camera->moveRelative(Vector3(0,0,0.08f*evt.timeSinceLastFrame));
	if (dDown) camera->moveRelative(Vector3(0.08f*evt.timeSinceLastFrame,0,0));
}
// ------------------------------------------------------------------------------------------------------------
void FreeCam::eventMouseMoved(const JMMouseEvent &evt)
{
	// Rotate the camera around if we're right clicking
	if (cameraDrag)
	{
		camera->yaw(Degree(-evt.relativeX*0.3f));
		camera->pitch(Degree(-evt.relativeY*0.25f));
	}
}
// ------------------------------------------------------------------------------------------------------------
void FreeCam::eventKeyboardKeyPressed(const JMKeyEvent &evt)
{
	// Adjust input data
	if (evt.key == 'W')
		wDown = true;
	else if (evt.key == 'A')
		aDown = true;
	else if (evt.key == 'S')
		sDown = true;
	else if (evt.key == 'D')
		dDown = true; 
	else if (evt.key == VK_ESCAPE)
		leave();
}
// ------------------------------------------------------------------------------------------------------------
void FreeCam::eventKeyboardKeyReleased(const JMKeyEvent &evt)
{
	// Adjust input data
	if (evt.key == 'W')
		wDown = false;
	else if (evt.key == 'A')
		aDown = false;
	else if (evt.key == 'S')
		sDown = false;
	else if (evt.key == 'D')
		dDown = false;
}
// ------------------------------------------------------------------------------------------------------------
void FreeCam::eventMousePressed(const JMMouseEvent &evt)
{
	// Adjust input data
	if (evt.button == MB_RBUTTON)
		cameraDrag = true;
}
// ------------------------------------------------------------------------------------------------------------
void FreeCam::eventMouseReleased(const JMMouseEvent &evt)
{
	// Adjust input data
	if (evt.button == MB_RBUTTON)
		cameraDrag = false;
}
// ------------------------------------------------------------------------------------------------------------

