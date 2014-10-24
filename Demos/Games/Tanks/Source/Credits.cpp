#include "StdAfx.h"
#include "Credits.h"

// ------------------------------------------------------------------------------------------------------------
Credits::Credits(String uname, OgreMain* oMain) : NavigatableInterface(oMain)
{
	// Create an overlay for this menu
	overlay = OverlayManager::getSingletonPtr()->create(uname+"Credits");

	// Add a button
	backButton = new MenuButton("RETURN", uname+"Button", overlay);
	backButton->setPosition(800,10000-1600);

	creditsPane = new CreditsDisplay(uname+"CreditsPane", overlay);
}
// ------------------------------------------------------------------------------------------------------------
Credits::~Credits()
{
	delete backButton;
	delete creditsPane;
	OverlayManager::getSingletonPtr()->destroy(overlay);
}
// ------------------------------------------------------------------------------------------------------------
void Credits::open()
{
	overlay->show();
	enter();
}
// ------------------------------------------------------------------------------------------------------------
void Credits::close()
{
	leave();
	overlay->hide();
}
// ------------------------------------------------------------------------------------------------------------
void Credits::update(float timeSinceLastFrame)
{
	backButton->update(timeSinceLastFrame);
	creditsPane->update(timeSinceLastFrame);
}
// ------------------------------------------------------------------------------------------------------------
void Credits::navigateUp()
{
	backButton->setSelected(true);
}
// ------------------------------------------------------------------------------------------------------------
void Credits::navigateDown()
{
	backButton->setSelected(true);
}
// ------------------------------------------------------------------------------------------------------------
void Credits::navigateForward()
{
	if (backButton->isSelected())
		close();
}
// ------------------------------------------------------------------------------------------------------------
void Credits::navigateBackward()
{
	close();
}
// ------------------------------------------------------------------------------------------------------------
void Credits::navigateMouse(float mx, float my)
{
	if (backButton->inside(mx, my))
		backButton->setSelected(true);
	else
		backButton->setSelected(false);
}
// ------------------------------------------------------------------------------------------------------------
