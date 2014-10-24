/************************************************************************/
/* @class SplashScreen
 * @author Jack McCallum
 * 
 * @description
 * This is a simple class that loads a single image, 
 * Ogre then render it as a splash screen,
 * Then we can load our resources and what not,
 * Then delete this when we're done.
 * 
/************************************************************************/

#pragma once
#ifndef _SPLASH_SCREEN
#define _SPLASH_SCREEN

class SplashScreen
{
public:
	// Default constructor
	SplashScreen(Ogre::Root* root, Ogre::RenderWindow* rw, Ogre::SceneManager* sm);
	// Destructor
	~SplashScreen();
	
	// Show the splash screen
	void show();
	// Hide the splash screen
	void hide();

private:
	// Ogre Root
	Root* ogreRoot;
	// Render window
	RenderWindow* renderWindow;
	// Scene Manager
	SceneManager* sceneManager;

	// Temporary camera for rendering the splash
	Camera* camera;
	// Temporary view for rendering the splash
	Viewport* viewport;

	// The splash screens geometry attached to the:
	Ogre::Rectangle2D* rectangle;
	// The splash screens node
	Ogre::SceneNode* node;
};

#endif