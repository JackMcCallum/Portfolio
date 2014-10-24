/************************************************************************/
/* @class Game
 * @author Jack McCallum
 * 
 * @description
 * Class from where all the game is controlled, it is entered via TanksMain
 * also controlls the score and win/lose condision
 * 
/************************************************************************/

#pragma once

#include "EventLoop.h"

class StandardMenu;
class FreeCam;
class CollisionManager;
class EffectsManager;
class HPDisplay;
class GameOver;
class Player;
class Game;

// This is a class for sending pointers to managers etc to our objects without making a huge mess
struct GameData
{
	OgreMain* ogreMain;
	CollisionManager* collisionManager;
	EffectsManager* effectsManager;
	Game* game;
	// Effects manager etc...
};

class Game : public EventLoop
{
public:
	Game(OgreMain* oMain);
	virtual ~Game();

	virtual void eventKeyboardKeyPressed(const JMKeyEvent &evt);
	
	// Goto other event loops
	void gotoPauseMenu();
	void gotoGameOverWin();
	void gotoGameOverLose();
	
	// Generates a level with a given seed
	void generateLevel(int seed);

	// Updates
	virtual void eventPreRender(const JMFrameEvent &evt);
	
	// Creation and destruction of the scene
	virtual void eventEnteringLoop(const JMFrameEvent &evt);
	virtual void eventLeavingLoop(const JMFrameEvent &evt);

	// Score control
	void addScore(int val);
	
private:
	// Game objects
	StandardMenu* pauseMenu;
	FreeCam* freeCam;
	GameOver* gameOver;
	Player* player;

	// Pointers to be sent to other objects
	GameData gameData;

	// Interface
	HPDisplay* hpDisplay;
	Overlay* overlay;

	// Score
	int score;
};

