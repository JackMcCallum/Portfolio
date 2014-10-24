#include "StdAfx.h"
#include "GameOver.h"
#include "MenuButton.h"

// ------------------------------------------------------------------------------------------------------------
GameOver::GameOver(String uname, OgreMain* oMain) : NavigatableInterface(oMain)
{
	overlay = OverlayManager::getSingletonPtr()->create(uname);
	
	backButton = new MenuButton("MAIN MENU", uname+"GameOverButton", overlay);
	backButton->setPosition(800,8400);

	container = (OverlayContainer*)OverlayManager::getSingletonPtr()->createOverlayElement("Panel", uname+"StatusDisplay");
	container->setMaterialName("Material_MenuItemBackground");
	container->setMetricsMode(GMM_RELATIVE_ASPECT_ADJUSTED);
	container->setHorizontalAlignment(GHA_CENTER);
	container->setWidth(8000);
	container->setHeight(2000);
	container->setPosition(-4000,2000);
	overlay->add2D(container);

	// Create the text area for the orange text
	OverlayManager* overlayMgr = OverlayManager::getSingletonPtr();
	textArea0 = (TextAreaOverlayElement*)overlayMgr->createOverlayElement("TextArea", uname+"Titles0");
	textArea0->setMetricsMode(GMM_RELATIVE_ASPECT_ADJUSTED);
	textArea0->setFontName("MenuFont");
	textArea0->setCharHeight(600);
	textArea0->setPosition(180, 180);
	textArea0->setColour(ColourValue(0.913f, 0.588f, 0.294f));
	container->addChild(textArea0);

	// And one for the white text
	textArea1 = (TextAreaOverlayElement*)overlayMgr->createOverlayElement("TextArea", uname+"Titles1");
	textArea1->setMetricsMode(GMM_RELATIVE_ASPECT_ADJUSTED);
	textArea1->setFontName("MenuFont");
	textArea1->setCharHeight(600);
	textArea1->setPosition(180, 180);
	textArea1->setColour(ColourValue::White);
	container->addChild(textArea1);

}
// ------------------------------------------------------------------------------------------------------------
GameOver::~GameOver()
{
	OverlayManager::getSingletonPtr()->destroyOverlayElement(container);
}
// ------------------------------------------------------------------------------------------------------------
void GameOver::open()
{
	overlay->show();
	enter();
}
// ------------------------------------------------------------------------------------------------------------
void GameOver::close()
{
	leave(getOutput());
	overlay->hide();
}
// ------------------------------------------------------------------------------------------------------------
void GameOver::update(float timeSinceLastFrame)
{
	backButton->update(timeSinceLastFrame);
	// Updates the caption based on the state

	if (currentState)
	{
		textArea0->setCaption(
			"YOU WIN!"
			""
			"");
		textArea1->setCaption(
			"\n"
			"Congratulations\n"
			"Score: " + StringConverter::toString(resultingScore));
	}
	else
	{
		textArea0->setCaption(
			"YOU LOSE!"
			""
			"");
		textArea1->setCaption(
			"\n"
			"Sucks to be you!\n"
			"Score: " + StringConverter::toString(resultingScore));
	}
}
// ------------------------------------------------------------------------------------------------------------
void GameOver::navigateUp()
{
	backButton->setSelected(true);
}
// ------------------------------------------------------------------------------------------------------------
void GameOver::navigateDown()
{
	backButton->setSelected(true);
}
// ------------------------------------------------------------------------------------------------------------
void GameOver::navigateForward()
{
	if (backButton->isSelected())
	{
		setOutput("main");
		close();
	}
}
// ------------------------------------------------------------------------------------------------------------
void GameOver::navigateBackward()
{
	setOutput("main");
	close();
}
// ------------------------------------------------------------------------------------------------------------
void GameOver::navigateMouse(float mx, float my)
{
	if (backButton->inside(mx, my))
		backButton->setSelected(true);
	else
		backButton->setSelected(false);
}
// ------------------------------------------------------------------------------------------------------------
void GameOver::setState(bool win, int score)
{
	currentState = win;
	resultingScore = score;
}
// ------------------------------------------------------------------------------------------------------------