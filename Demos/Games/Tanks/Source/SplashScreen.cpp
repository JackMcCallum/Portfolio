#include "StdAfx.h"
#include "SplashScreen.h"

// ------------------------------------------------------------------------------------------------------------
SplashScreen::SplashScreen(Ogre::Root* root, Ogre::RenderWindow* rw, Ogre::SceneManager* sm)
{
	// Retrieve the pointers first
	ogreRoot = root;
	renderWindow = rw;
	sceneManager = sm;

	// Check for errors
	assert(ogreRoot);
	assert(renderWindow);
	assert(sceneManager);
	
	camera = sceneManager->createCamera("SplashCam");
	viewport = renderWindow->addViewport(camera, -10);
	// Make whats behind the image black, just in case
	viewport->setBackgroundColour(Ogre::ColourValue::Black);
	
	// Ogre::Rectangle2D aparently dosnt like the camera being a 0,0,0
	camera->setPosition(256,256,256);
	camera->lookAt(0,0,0);

	rectangle = new Ogre::Rectangle2D(true);
	rectangle->setBoundingBox(Ogre::AxisAlignedBox(-100000.0f*Ogre::Vector3::UNIT_SCALE, 100000.0f*Ogre::Vector3::UNIT_SCALE));
	rectangle->setCorners(-1.001f, 1.001f, 1.001f, -1.001f);

	node = sceneManager->getRootSceneNode()->createChildSceneNode();
	node->attachObject(rectangle);
	node->setVisible(false);
	
	// Pointer to Ogre3D's resource manager
	Ogre::ResourceGroupManager* manager = Ogre::ResourceGroupManager::getSingletonPtr();
	assert(manager);
	
	// Add resource directories
	manager->addResourceLocation("../../Assets/Splash/", "FileSystem", "Splash");
	manager->initialiseResourceGroup("Splash");
	manager->loadResourceGroup("Splash");
	
	rectangle->setMaterial("Material_SplashScreen");

	this->show();
}
// ------------------------------------------------------------------------------------------------------------
SplashScreen::~SplashScreen()
{
	// Leave a blank screen
	//hide();

	// Unload the resource group
	Ogre::ResourceGroupManager* manager = Ogre::ResourceGroupManager::getSingletonPtr();
	assert(manager);
	
	manager->unloadResourceGroup("Splash");

	renderWindow->removeViewport(-10);
	sceneManager->destroyCamera(camera);

	sceneManager->destroySceneNode(node);
	delete rectangle;

}
// ------------------------------------------------------------------------------------------------------------
void SplashScreen::show()
{
	node->setVisible(true);
	ogreRoot->renderOneFrame();

}
// ------------------------------------------------------------------------------------------------------------
void SplashScreen::hide()
{
	node->setVisible(false);
	ogreRoot->renderOneFrame();
}
