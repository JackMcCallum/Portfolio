/****************************************************
Author: Jack McCallum

Description:
Simple class that sets up Ogre3D and the render window.
It Also loads the resources from the assets folder and
gives us access to the pointers and window handle we need.
The settings for the window are hard coded with #define bellow.
Is a singleton.

****************************************************/

#pragma once

// Window settings
#define CFG_WNAME "Tanks" // Window caption
#define CFG_WIDTH 1280 // Window width
#define CFG_HEIGHT 720 // Window height
#define CFG_VSYNC 0 // Vertical synchronize
#define CFG_FSAA 4 // Anti aliasing
#define CFG_AF 8 // Anisotropic filtering
#define CFG_FSCREEN 0 // Full screen

class OgreMain
{
public:
	// Default constructor
	OgreMain();
	// Destructor
	~OgreMain();

	// Initialize Ogre
	void initialize();
	// Load assets
	void loadResources();
	// Toggle full screen mode
	void toggleFullScreen();

	// Return pointer to the Root
	Root* getRoot();
	// Return a pointer to the render window
	RenderWindow* getWindow();
	// Return a pointer to the scene manager
	SceneManager* getSceneManager();
	// Returns a pointer to the scene camera
	Camera* getCamera();
	// Returns a pointer to the scene viewport
	Viewport* getViewport();
	// Return the render window handle
	HWND getWindowHandle();

private:
	// Ogre Root
	Root* ogreRoot;
	// Render window
	RenderWindow* renderWindow;
	// Scene Manager
	SceneManager* sceneManager;
	// Scene Camera
	Camera* sceneCamera;
	// Window Viewport
	Viewport* sceneViewport;

	// Is initialized or not
	bool initialized;
};
