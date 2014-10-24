#include "StdAfx.h"
#include "TanksMain.h"
#include "SplashScreen.h"

// ------------------------------------------------------------------------------------------------------------
TanksMain::~TanksMain()
{
	delete mainMenu;
	delete credits;
	delete game;
	delete ogreMain;
}
// ------------------------------------------------------------------------------------------------------------
void TanksMain::start()
{
	
	// Create an initialize OgreMain singleton
	ogreMain = new OgreMain();
	ogreMain->initialize();

	// Initialize and show the splash screen
	SplashScreen* splash = new SplashScreen(ogreMain->getRoot(), ogreMain->getWindow(), ogreMain->getSceneManager());
	splash->show();

	// Load ogre
	ogreMain->loadResources();

	// Create the menu
	mainMenu = new StandardMenu("Main Menu", ogreMain);
	mainMenu->addButton("NEW GAME", "new");
	mainMenu->addButton("CREDITS", "credits");
	mainMenu->addButton("EXIT GAME", "exit");

	// Create the credits
	credits = new Credits("Credits", ogreMain);

	// Create the game
	game = new Game(ogreMain);

	// Hide splash screen
	splash->hide();
	delete splash;

	// And finally, open up the main menu
	gotoMainMenu();
	//gotoGame();
}
// ------------------------------------------------------------------------------------------------------------
void TanksMain::gotoMainMenu()
{
	mainMenu->open();
	String result = mainMenu->getOutput();

	if (result == "new")
		gotoGame();
	else if (result == "credits")
		gotoCredits();
}
// ------------------------------------------------------------------------------------------------------------
void TanksMain::gotoGame()
{
	game->enter();
	String result = game->getOutput();
	
	if (result == "main")
		gotoMainMenu();
	else if (result == "restart")
		gotoGame();
}
// ------------------------------------------------------------------------------------------------------------
void TanksMain::gotoCredits()
{
	credits->open();
	gotoMainMenu();
}
// ------------------------------------------------------------------------------------------------------------