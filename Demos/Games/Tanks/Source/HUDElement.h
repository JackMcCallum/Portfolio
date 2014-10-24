/************************************************************************/
/* @class HUDElement
 * @author Jack McCallum
 * 
 * @description
 * Base class for interactive HUD elements
 * Provides a simple set of variables that can be 
 * used to create interactive menus and GUIs etc...
 * In this case i will be using it for:
 *		- main menu dialog
 *		- pause menu dialog
 *		- credits dialog
 *		- win/lose dialog
 *		- game HUD
 * 
/************************************************************************/



#pragma once
#ifndef _HUD_ELEMENT
#define _HUD_ELEMENT

class HUDElement
{
public:
	// Default constructor
	HUDElement(String name, Overlay* parent);
	// Destructor
	virtual ~HUDElement();

	// Update animations etc...
	virtual void update(float timeSinceLastFrame) = 0;

	
	// Set position, this is entirely Dependant on container's metrics mode
	void setPosition(float x, float y);

	// Optional visual conditions
	void setSelected(bool val);
	void setEnabled(bool val);
	void setHidden(bool val);

	// Returns true if selected
	bool isSelected();
	// Returns true if enabled
	bool isEnabled();
	// Returns true if hidden
	bool isHidden();
	
	// Get if a clamped point on screen (0-1)
	// is within the rect of this container
	virtual bool inside(float x, float y);

	String getName();
	// Optional system for controlling the output of a dialog
	// Set the output string
	void setOutput(String o);
	// Get the output string
	String getOutput();
	
protected:
	// Element name for generating children names on OverlayElements
	// Must be unique
	String elementName;
	// Output string, optional system for controlling the output of a dialog
	String outputString;

	// Pointer to the parent overlay provided externally
	Overlay* parentOverlay;
	// This elements container
	OverlayContainer* container;
	
	// Selected
	bool selected;
	// Enabled
	bool enable;
	// Hidden
	bool hidden;
};

#endif