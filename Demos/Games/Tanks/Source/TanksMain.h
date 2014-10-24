/************************************************************************/
/* @class TanksMain
 * @author Jack McCallum
 * 
 * @description
 * This is the hub that everything is controlled from,
 * The beginning! Let there be light!
 * 
/************************************************************************/

#pragma once

#include "Game.h"
#include "StandardMenu.h"
#include "Credits.h"

class TanksMain
{
public:
	~TanksMain();

	void start();

	void gotoMainMenu();
	void gotoGame();
	void gotoCredits();

private:
	OgreMain* ogreMain;

	StandardMenu* mainMenu;
	Credits* credits;
	Game* game;

};