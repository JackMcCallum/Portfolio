#include "StdAfx.h"
#include "EventLoop.h"

// ------------------------------------------------------------------------------------------------------------
EventLoop::EventLoop(OgreMain* oMain)
{
	ogreMain = oMain;
	assert(ogreMain);

	// Setup all the event handlers and add this as a listener
	// Frame event handler
	frameEventHandler = new OgreFrameEventHandler(ogreMain->getRoot(), ogreMain->getWindow(), ogreMain->getCamera());
	frameEventHandler->addListener((JMFrameEventListener*)this);

	// Mouse event handler
	mouseEventHandler = new JMMouseEventHandler(ogreMain->getWindowHandle());
	mouseEventHandler->addListener((JMMouseEventListener*)this);

	// Keyboard event handler
	keyboardEventHandler = new JMKeyboardEventHandler(ogreMain->getWindowHandle());
	keyboardEventHandler->addListener((JMKeyboardEventListener*)this);
}
// ------------------------------------------------------------------------------------------------------------
EventLoop::~EventLoop()
{
	// Clean up the event handlers
	if (mouseEventHandler) 
		delete mouseEventHandler;

	if (keyboardEventHandler) 
		delete keyboardEventHandler;

	if (frameEventHandler)
		delete frameEventHandler;
}
// ------------------------------------------------------------------------------------------------------------
String EventLoop::enter()
{
	// Let input catch up
	processInput(true);
	eventLoopOutput = "";
	frameEventHandler->beginFrameLoop();
	// Continues from here when leaving the event loop, so return output
	return eventLoopOutput;
}
// ------------------------------------------------------------------------------------------------------------
void EventLoop::leave(String output)
{
	eventLoopOutput = output;
	frameEventHandler->endFrameLoop();
}
// ------------------------------------------------------------------------------------------------------------
String EventLoop::getOutput()
{
	return eventLoopOutput;
}
// ------------------------------------------------------------------------------------------------------------
void EventLoop::setOutput(std::string s)
{
	eventLoopOutput = s;
}
// ------------------------------------------------------------------------------------------------------------
void EventLoop::processInput(bool dontSendEvents)
{
	mouseEventHandler->processMouseEvents(dontSendEvents);
	keyboardEventHandler->processKeyboardEvents(dontSendEvents);
}
// ------------------------------------------------------------------------------------------------------------
void EventLoop::eventPreRender(const JMFrameEvent &evt)
{
	processInput();
}
// ------------------------------------------------------------------------------------------------------------
OgreFrameEventHandler* EventLoop::getFrameEventHandler()
{
	return frameEventHandler;
}
// ------------------------------------------------------------------------------------------------------------
JMMouseEventHandler* EventLoop::getMouseEventHandler()
{
	return mouseEventHandler;
}
// ------------------------------------------------------------------------------------------------------------
JMKeyboardEventHandler* EventLoop::getKeyboardEventHandler()
{
	return keyboardEventHandler;
}
// ------------------------------------------------------------------------------------------------------------
void EventLoop::eventEnteringLoop(const JMFrameEvent &evt)
{
	processInput(true);
}
// ------------------------------------------------------------------------------------------------------------
