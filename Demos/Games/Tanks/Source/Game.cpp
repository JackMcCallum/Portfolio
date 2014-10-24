#include "StdAfx.h"
#include "Game.h"

#include "CollisionManager.h"
#include "EffectsManager.h"
#include "StandardMenu.h"
#include "FreeCam.h"
#include "JMRandom.h"
#include "GameOver.h"

// Entities
#include "Player.h"
#include "Wall.h"
#include "Spawner.h"
#include "HPDisplay.h"

// ------------------------------------------------------------------------------------------------------------
Game::Game(OgreMain* oMain) : EventLoop(oMain)
{
	gameData.ogreMain = oMain;
	gameData.game = this;

	// Create the collision and effects manager
	gameData.collisionManager = new CollisionManager(getFrameEventHandler());
	gameData.effectsManager = new EffectsManager(getFrameEventHandler());
	
	// Create the free cam
	freeCam = new FreeCam(ogreMain);

	// Create the win/lose screen
	gameOver = new GameOver("GameOverSceen", ogreMain);
	gameOver->getFrameEventHandler()->addListener((JMFrameEventListener*)gameData.collisionManager);
	gameOver->getFrameEventHandler()->addListener((JMFrameEventListener*)gameData.effectsManager);

	// Create the pause menu and its buttons
	pauseMenu = new StandardMenu("Pause Menu", ogreMain);
	pauseMenu->addButton("RESUME GAME", "resume");
	pauseMenu->addButton("NEW LEVEL", "restart");
	pauseMenu->addButton("FREE CAMERA", "freecam");
	pauseMenu->addButton("MAIN MENU", "main");
	pauseMenu->addButton("EXIT GAME", "exit");

	// Compositors, for fancy bloom effect (these wont work on ATI cards as far as i know, and i don't know why yet)
	// Uncomment and they should work without issue aslong as their files are found by the resource manager
	//CompositorManager::getSingletonPtr()->addCompositor(gameData.ogreMain->getViewport(), "Bloom");
	//CompositorManager::getSingletonPtr()->setCompositorEnabled(gameData.ogreMain->getViewport(), "Bloom", true);

	// Overlay for the HP do be displayed on
	overlay = OverlayManager::getSingletonPtr()->create("HPOverlay");
}
// ------------------------------------------------------------------------------------------------------------
Game::~Game()
{
	// Delete pause menu and managers
	delete pauseMenu;
	delete gameData.collisionManager;
	delete gameData.effectsManager;

	// Clear the entire ogre scene
	ogreMain->getSceneManager()->clearScene();
}
// ------------------------------------------------------------------------------------------------------------
void Game::eventKeyboardKeyPressed(const JMKeyEvent &evt)
{
	// Open pause menu
	if (evt.key == VK_ESCAPE)
		gotoPauseMenu();
}
// ------------------------------------------------------------------------------------------------------------
void Game::gotoPauseMenu()
{
	// Open the pause menu
	pauseMenu->open();
	// Catch the result of the pause menu
	String result = pauseMenu->getOutput();

	// Compare the results and do appropriate operation
	if (result == "main")
		leave(result);
	else if (result == "restart")
		leave(result);
	else if (result == "freecam")
	{
		freeCam->enter();
		gotoPauseMenu();
	}
	else if (result == "exit")
		leave(result);
}
// ------------------------------------------------------------------------------------------------------------
void Game::generateLevel(int seed)
{
	// Define height/width
	const int levelWidth = 32;
	const int levelHeight = 32;

	// Define types of tiles
	enum IDs
	{
		EMPTY,
		WALL,
		VWALL,
		HWALL,
		TOWER,
		SPAWNER
	};

	int levelGrid[levelWidth][levelHeight];
	int levelGridRefined[levelWidth][levelHeight];

	// Clear the level
	for (int i=0; i<levelWidth; i++)
		for (int j=0; j<levelHeight; j++)
		{
			levelGrid[i][j] = EMPTY;
			levelGridRefined[i][j] = EMPTY;
		}

	// Fill the outside with walls
	for (int i=0; i<levelWidth; i++)
	{
		levelGrid[i][0] = WALL;
		levelGrid[i][levelHeight-1] = WALL;
		levelGrid[0][i] = WALL;
		levelGrid[levelWidth-1][i] = WALL;
	}

	// Faster RNG, no particular reason
	JMRandom r;
	r.seed(seed);

	// Put up some random walls
	for (int i=0; i<32; i++)
	{
		// First pick a position to start at
		int startx = r.generate()%levelWidth;
		int starty = r.generate()%levelHeight;

		// Round those positions to being 4 blocks apart
		startx = (int)floor(startx*0.25f)*4;
		starty = (int)floor(starty*0.25f)*4;

		// Pick a random direction/length
		int dir = r.generate()%4;
		int len = 5;//2+(1+rand()%2)*3;
		int newLen = 0;

		// Follow the direction the length and if you hit a wall, define a new length, or just use the old one if you don't
		bool endWall = false;
		for (int j=0; j<len && !endWall; j++)
		{
			levelGrid[startx][starty] = WALL;

			switch (dir)
			{
			case 0: startx++; break;
			case 1: startx--; break;
			case 2: starty++; break;
			case 3: starty--; break;
			}

			// Check if it has hit a wall
			if (startx < 0 || starty < 0 || startx > 31 || starty > 31)
				endWall = true;

		}
	}

	
	// Pick some places for some spawners
	int spawnerCount = 0;
	while (spawnerCount < 12)
	{
		int startx = (int)r.range(0,(int)levelWidth);
		int starty = (int)r.range(0,(int)levelHeight);

		// If the place is free
		// If not continue trying
		if (levelGrid[startx][starty] == EMPTY && 
			levelGrid[startx+1][starty] == EMPTY &&
			levelGrid[startx][starty+1] == EMPTY && 
			levelGrid[startx+1][starty+1] == EMPTY)
		{
			// Allocate the space
			levelGrid[startx][starty] = SPAWNER;
			levelGrid[startx+1][starty] = SPAWNER;
			levelGrid[startx][starty+1] = SPAWNER;
			levelGrid[startx+1][starty+1] = SPAWNER;
			spawnerCount++;
		}
	}
	
	// Here we're working out based on what is where to what kind of wall it is for example
	// Refine the level grid
	for (int i=0; i<levelWidth; i++)
		for (int j=0; j<levelHeight; j++)
		{
			// Copy over Spawners
			if (levelGrid[i][j] == SPAWNER)
				levelGridRefined[i][j] = SPAWNER;

			// Calculate what type of wall should be placed here
			if (levelGrid[i][j] == WALL)
			{
				// Just some fancy block checking etc.. to see if it needs to be a vertical wall, horizontal wall, or a tower (intersection wall)
				if (i == 0 || i == 31 || j == 0 || j == 31)
				{
					// For the outside layer of the grid
					if (j > 0 && j < levelWidth-1 && i == 0 && levelGrid[i+1][j] != WALL || j > 0 && j < levelWidth-1 && i == levelHeight-1 && levelGrid[i-1][j] != WALL)
						levelGridRefined[i][j] = VWALL;
					else if (i > 0 && i < levelHeight-1 && j == 0 && levelGrid[i][j+1] != WALL || i > 0 && i < levelHeight-1 && j == levelWidth-1 && levelGrid[i][j-1] != WALL)
						levelGridRefined[i][j] = HWALL;
					else
						levelGridRefined[i][j] = TOWER;
				}
				else
				{
					// For the inside layers of the grid
					if (levelGrid[i-1][j] != WALL && levelGrid[i+1][j] != WALL && levelGrid[i][j-1] == WALL && levelGrid[i][j+1] == WALL)
						levelGridRefined[i][j] = VWALL;
					else if (levelGrid[i-1][j] == WALL && levelGrid[i+1][j] == WALL && levelGrid[i][j-1] != WALL && levelGrid[i][j+1] != WALL)
						levelGridRefined[i][j] = HWALL;
					else
						levelGridRefined[i][j] = TOWER;
				}
			}
		}

	// Generate walls
	// Okay to do this is a little tricky, because we want to use an entire collision 
	// rectangle for the whole wall, not one for each grid block, to save on performance
	for (int i=0; i<levelWidth; i++)
	{
		bool makingWall = false;
		int startPos = 0;

		for (int j=0; j<levelHeight; j++)
		{
			// First things first, place all the towers, those are easy
			if (levelGridRefined[i][j] == TOWER)
			{
				Wall* wall = new Wall(gameData, Wall::WD_VERTICAL, 0);
				wall->position((i-levelWidth/2.0f)*16, (j-levelHeight/2.0f)*16);
			}
			// Maybe its a spawner, place it
			else if (levelGridRefined[i][j] == SPAWNER && 
				levelGridRefined[i+1][j] == SPAWNER &&
				levelGridRefined[i][j+1] == SPAWNER && 
				levelGridRefined[i+1][j+1] == SPAWNER)
			{
				Spawner* spawner = new Spawner(gameData);
				spawner->position((i+1-levelWidth/2.0f)*16, (j+1-levelHeight/2.0f)*16);
			}

			// If we are already following a wall
			// This is for vertical walls only
			if (makingWall)
			{
				// continue until you find an end
				if (levelGridRefined[i][j] != VWALL)
				{
					Wall* wall = new Wall(gameData, Wall::WD_VERTICAL, j-startPos);
					wall->position((i-levelWidth/2.0f)*16, (startPos-levelHeight/2.0f)*16);
					makingWall = false;
				}
			}
			// Else find a wall to follow
			else if (levelGridRefined[i][j] == VWALL)
			{
				startPos = j;
				makingWall = true;
			}
		}
	}

	// Now for the rest of the walls
	for (int j=0; j<levelHeight; j++)
	{
		bool makingWall = false;
		int startPos = 0;

		for (int i=0; i<levelWidth; i++)
		{
			// If we are already following a wall
			// This is for horizontal walls only
			if (makingWall)
			{
				// continue until you find an end
				if (levelGridRefined[i][j] != HWALL)
				{
					Wall* wall = new Wall(gameData, Wall::WD_HORIZONTAL, i-startPos);
					wall->position((startPos-levelWidth/2.0f)*16, (j-levelHeight/2.0f)*16);
					makingWall = false;
				}
			}
			// Else find a wall to follow
			else if (levelGridRefined[i][j] == HWALL)
			{
				startPos = i;
				makingWall = true;
			}
		}
	}

	// Done generating the level
}
// ------------------------------------------------------------------------------------------------------------
void Game::eventPreRender( const JMFrameEvent &evt )
{
	EventLoop::eventPreRender(evt);

	// Check for lose condition
	
	// Oh nice, i already implemented a function for the enemies to find the player
	// This should do the trick
	if (gameData.collisionManager->findPlayer() == NULL)
	{
		overlay->hide();
		gotoGameOverLose();
	}
	
	// Check for win condition
	std::list<Collidable*> clist = gameData.collisionManager->getCollidableList();
	std::list<Collidable*>::iterator iter = clist.begin();

	bool allSpawnersDead = true;
	while (iter != clist.end())
	{
		//Spawner* spawner = dynamic_cast<Spawner*>(*iter++);
		if (typeid(Spawner) == typeid(*(*iter)))
		{
			Spawner* spawner = static_cast<Spawner*>(*iter);
			if (spawner->isDead == false)
				allSpawnersDead = false;
		}
		iter++;
	}

	if (allSpawnersDead)
	{
		overlay->hide();
		gotoGameOverWin();
	}
		
	hpDisplay->update(evt.timeSinceLastFrame);

}
// ------------------------------------------------------------------------------------------------------------
void Game::eventEnteringLoop(const JMFrameEvent &evt)
{
	// Create the floor entity
	Entity* ent = ogreMain->getSceneManager()->createEntity("BackgroundPlane.mesh");
	ent->setMaterialName("Material_BackgroundPlane");
	ogreMain->getSceneManager()->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
	
	// Create the sunlight
	Light* light = ogreMain->getSceneManager()->createLight();
	light->setDirection(-1,-1,-1);
	light->setType(Light::LT_DIRECTIONAL);
	light->setDiffuseColour(ColourValue::White);
	light->setSpecularColour(ColourValue::White);
	
	// Ambient light
	ogreMain->getSceneManager()->setAmbientLight(ColourValue(0.2f,0.2f,0.2f));

	// Shadows
	ogreMain->getSceneManager()->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
	
	// Create the player
	player = new Player(gameData, getMouseEventHandler(), getKeyboardEventHandler());
	player->translate(32,32);
	// Generate the level
	generateLevel(0);

	// hit points display
	hpDisplay = new HPDisplay("HPDisplay", overlay, player->getHitPointsAddress());
	overlay->show();

	// Score gets reset
	score = 0;
}
// ------------------------------------------------------------------------------------------------------------
void Game::eventLeavingLoop(const JMFrameEvent &evt)
{
	// Clean up
	delete hpDisplay;
	gameData.collisionManager->destroyAllCollidables();
	gameData.effectsManager->destroyAllEffects();
	gameData.ogreMain->getSceneManager()->clearScene();
}
// ------------------------------------------------------------------------------------------------------------
void Game::gotoGameOverWin()
{
	// Called when you win
	gameOver->setState(true, score);
	gameOver->open();
	leave("main");
}
// ------------------------------------------------------------------------------------------------------------
void Game::gotoGameOverLose()
{
	// Called when you lose
	gameOver->setState(false, score);
	gameOver->open();
	leave("main");
}
// ------------------------------------------------------------------------------------------------------------
void Game::addScore(int val)
{
	score += val;
}
// ------------------------------------------------------------------------------------------------------------