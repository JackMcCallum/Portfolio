/************************************************************************/
/* @class TanksMain
 * @author Jack McCallum
 * 
 * @description
 * Anything that has an isolated system can derive from EventLoop
 * It can enter and leave the loop as you need and event have loops within the loops
 * use this for things like pause menu, main menu, game, credits etc...
 * 
/************************************************************************/

#pragma once

// Dependencies
#include "OgreFrameEventHandler.h"
#include "JMMouseEventHandler.h"
#include "JMKeyboardEventHandler.h"
#include "OgreMain.h"

class EventLoop : 
	public JMFrameEventListener,
	public JMMouseEventListener,
	public JMKeyboardEventListener
{
public:
	// Default Constructor
	EventLoop(OgreMain* oMain);
	// Destructor
	virtual ~EventLoop();

	// Enter the event loop, return the output string
	String enter();
	// Leave the event loop, output string to catch
	void leave(String output = "");

	// Set or get the output string
	String getOutput();
	void setOutput(String s);

	// Process all forms of input
	void processInput(bool dontSendEvents = false);

	// Get pointers to the event handlers
	OgreFrameEventHandler* getFrameEventHandler();
	JMMouseEventHandler* getMouseEventHandler();
	JMKeyboardEventHandler* getKeyboardEventHandler();
	
	// If we don't implement it in a derived class, it will automatically process input still
	virtual void eventPreRender(const JMFrameEvent &evt);

	virtual void eventEnteringLoop(const JMFrameEvent &evt);


protected:
	// Pointer to the OgreMain singleton
	OgreMain* ogreMain;

private:
	// Event handlers for this event loop
	OgreFrameEventHandler* frameEventHandler;
	JMMouseEventHandler* mouseEventHandler;
	JMKeyboardEventHandler* keyboardEventHandler;

	// Output string that the event loop returns
	String eventLoopOutput;
};
