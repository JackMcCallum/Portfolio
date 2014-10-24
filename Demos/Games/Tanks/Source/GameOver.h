/************************************************************************/
/* @class TanksMain
 * @author Jack McCallum
 * 
 * @description
 * Simple event loop that displays the win/lose and score
 * 
/************************************************************************/

#pragma once
#include "NavigatableInterface.h"

class OgreMain;
class MenuButton;

class GameOver : public NavigatableInterface
{
public:
	GameOver(String uname, OgreMain* oMain);
	virtual ~GameOver();

	// Open/close the menu, close should be controlled internally most likely
	virtual void open();
	virtual void close();

	// Update animations etc...
	virtual void update(float timeSinceLastFrame);

	// Navigate the standard menu
	virtual void navigateUp();
	virtual void navigateDown();
	virtual void navigateForward();
	virtual void navigateBackward();
	virtual void navigateMouse(float mx, float my);

	// Sets the state true = win
	void setState(bool win, int score);

private:
	Overlay* overlay;
	MenuButton* backButton;
	OverlayContainer* container;
	String caption0;
	String caption1;
	bool currentState;

	TextAreaOverlayElement* textArea0;
	TextAreaOverlayElement* textArea1;

	int resultingScore;

};

