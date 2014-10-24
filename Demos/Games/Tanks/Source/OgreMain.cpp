#include "StdAfx.h"
#include "OgreMain.h"

// ------------------------------------------------------------------------------------------------------------
OgreMain::OgreMain()
{
	ogreRoot = NULL;
	renderWindow = NULL;
	sceneManager = NULL;

	initialized = false;
}
// ------------------------------------------------------------------------------------------------------------
OgreMain::~OgreMain()
{
	if (ogreRoot)
		delete ogreRoot;
}
// ------------------------------------------------------------------------------------------------------------
void OgreMain::initialize()
{
	// Don't initialize twice by accident
	if (initialized)
		return;

	// Create Ogre Root
	ogreRoot = new Ogre::Root("Plugins/plugins.cfg");
	assert(ogreRoot);

	//ogreRoot->showConfigDialog();

	// Hard code ogre to use Direct3D9
	Ogre::RenderSystem *rs = ogreRoot->getRenderSystemByName("Direct3D9 Rendering Subsystem");
	ogreRoot->setRenderSystem(rs);

	ogreRoot->initialise(false);

	// Windows Settings
	Ogre::NameValuePairList params;
	params["monitorIndex"] = "0";
	params["vsync"] = StringConverter::toString(CFG_VSYNC);
	params["FSAA"] = StringConverter::toString(CFG_FSAA);
	//params["hidden"] = "1";

	
	if (CFG_FSCREEN)
	{
		HWND desktop = GetDesktopWindow();
		RECT rect;
		GetWindowRect(desktop, &rect);
		renderWindow = ogreRoot->createRenderWindow(CFG_WNAME, rect.right, rect.bottom, true, &params);
	}
	else
		renderWindow = ogreRoot->createRenderWindow(CFG_WNAME, CFG_WIDTH, CFG_HEIGHT, false, &params);
	assert(renderWindow);
	renderWindow->setDeactivateOnFocusChange(false);

	// Scene manager
	sceneManager = ogreRoot->createSceneManager(Ogre::ST_GENERIC);
	assert(sceneManager);

	// Camera
	sceneCamera = sceneManager->createCamera("");
	assert(sceneCamera);
	sceneCamera->setFOVy(Degree(60));
	sceneCamera->setNearClipDistance(0.1f);
	sceneCamera->setPosition(3,2,4);
	sceneCamera->lookAt(1,0,-4);

	// Viewport
	sceneViewport = renderWindow->addViewport(sceneCamera);
	assert(sceneViewport);
	sceneViewport->setBackgroundColour(Ogre::ColourValue(0.2f,0.2f,0.2f));

	// Is now initialized
	initialized = true;

}
// ------------------------------------------------------------------------------------------------------------
void OgreMain::loadResources()
{
	if (!initialized)
		return;

	// Setup AF filtering as a default
	Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_ANISOTROPIC);
	Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(CFG_AF);

	// Pointer to Ogre3D's resource manager
	Ogre::ResourceGroupManager* manager = Ogre::ResourceGroupManager::getSingletonPtr();
	assert(manager);
	
	// Simplify!
	Ogre::String group = "General";
	Ogre::String type = "FileSystem";
	Ogre::String folder = "../../Assets/";

	// Add resource directories
	manager->addResourceLocation(folder + "Materials", type, group);
	manager->addResourceLocation(folder + "Models", type, group);
	manager->addResourceLocation(folder + "Textures", type, group);
	manager->addResourceLocation(folder + "Misc", type, group);

	// Get the resource group ready for loading
	manager->initialiseResourceGroup(group);

	// Load the resource group
	manager->loadResourceGroup(group);

	// Create Font
	Ogre::FontPtr font = Ogre::FontManager::getSingletonPtr()->create("MenuFont", "General");
	font->setType(Ogre::FT_TRUETYPE);
	font->setSource("EurostileExtended.ttf");
	font->setTrueTypeSize(40);
	font->setTrueTypeResolution(72);
	font->load();
	font->touch();

	font = Ogre::FontManager::getSingletonPtr()->create("HUDFont", "General");
	font->setType(Ogre::FT_TRUETYPE);
	font->setSource("EurostileExtended.ttf");
	font->setTrueTypeSize(24);
	font->setTrueTypeResolution(72);
	font->load();
	font->touch();	
}
// ------------------------------------------------------------------------------------------------------------
Ogre::Root* OgreMain::getRoot()
{
	return ogreRoot;
}
// ------------------------------------------------------------------------------------------------------------
Ogre::RenderWindow* OgreMain::getWindow()
{
	return renderWindow;
}
// ------------------------------------------------------------------------------------------------------------
Ogre::SceneManager* OgreMain::getSceneManager()
{
	return sceneManager;
}
// ------------------------------------------------------------------------------------------------------------
HWND OgreMain::getWindowHandle()
{
	HWND windowHnd = 0;
	if (renderWindow) renderWindow->getCustomAttribute("WINDOW", &windowHnd);
	return windowHnd;
}
// ------------------------------------------------------------------------------------------------------------
void OgreMain::toggleFullScreen()
{
	if (!initialized)
		return;

	if (renderWindow->isFullScreen())
	{
		renderWindow->setFullscreen(false, CFG_WIDTH, CFG_HEIGHT);
	}
	else
	{
		HWND desktop = GetDesktopWindow();
		RECT rect;
		GetWindowRect(desktop, &rect);
		renderWindow->setFullscreen(true, rect.right, rect.bottom);
	}
}

Camera* OgreMain::getCamera()
{
	return sceneCamera;
}

Viewport* OgreMain::getViewport()
{
	return sceneViewport;
}
