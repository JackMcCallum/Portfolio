#include "StdAfx.h"
#include "StandardMenu.h"

// ------------------------------------------------------------------------------------------------------------
StandardMenu::StandardMenu(String uname, OgreMain* oMain) : NavigatableInterface(oMain)
{
	uniqueName = uname;

	// Create an overlay for this menu
	menuOverlay = OverlayManager::getSingletonPtr()->create(uniqueName + "Menu");
}
// ------------------------------------------------------------------------------------------------------------
StandardMenu::~StandardMenu()
{
	// Destroy all child buttons
	buttonIter = buttonList.begin();
	while (buttonIter != buttonList.end())
	{
		delete (*buttonIter);
		buttonList.remove(*buttonIter++);
	}

	OverlayManager::getSingletonPtr()->destroy(menuOverlay);
}
//-------------------------------------------------------------------------------------------------------------
void StandardMenu::update(float timeSinceLastFrame)
{
	// Update all child buttons
	buttonIter = buttonList.begin();
	while (buttonIter != buttonList.end())
		(*buttonIter++)->update(timeSinceLastFrame);
}
//-------------------------------------------------------------------------------------------------------------
void StandardMenu::open()
{
	menuOverlay->show();
	enter();
}
//-------------------------------------------------------------------------------------------------------------
void StandardMenu::close()
{
	leave(getOutput());
	menuOverlay->hide();
}
// ------------------------------------------------------------------------------------------------------------
void StandardMenu::addButton(String caption, String returnStr)
{
	// Add a button
	MenuButton* mb = new MenuButton(caption, caption+StringConverter::toString(uniqueNameGen++), menuOverlay);
	mb->setOutput(returnStr);
	mb->setPosition(800,800.0f+buttonList.size()*1200);
	buttonList.push_back(mb);
}
// ------------------------------------------------------------------------------------------------------------
void StandardMenu::removeButton(String caption)
{
	// Remove a button by name
	// Also position all the buttons again
	int i = 0;
	buttonIter = buttonList.begin();
	while (buttonIter != buttonList.end())
	{
		if ((*buttonIter)->getCaption() == caption)
		{
			delete (*buttonIter);
			buttonList.remove(*buttonIter++);
		}
		else
		{
			(*buttonIter++)->setPosition(800,800.0f+i*1200);
			i++;
		}
	}
}
// ------------------------------------------------------------------------------------------------------------
void StandardMenu::navigateUp()
{
	int eleCount = buttonList.size();

	// If we actually have button
	if (eleCount > 0)
	{
		bool foundSelected = false;
		int indexSelected = 0;

		// Find a selected button to be our index
		buttonIter = buttonList.begin(); 
		while (buttonIter != buttonList.end())
		{
			HUDElement* element = (*buttonIter++);
			if (element->isSelected())
			{
				foundSelected = true;
				break;
			}
			indexSelected++;
		}

		// If we did not find a selected button
		if (!foundSelected)
		{
			// Select one
			(*buttonList.rbegin())->setSelected(true); 
		}
		// else select the previous one that was selected
		else
		{
			// First deselect the old one
			int i = 0;
			buttonIter = buttonList.begin();
			while (buttonIter != buttonList.end())
			{
				HUDElement* element = (*buttonIter++);
				if (i == indexSelected)
				{
					element->setSelected(false);

					indexSelected--;
					if (indexSelected < 0)
						indexSelected = eleCount-1;

					break;
				}
				i++;
			}

			// Now select the new one
			i = 0;
			buttonIter = buttonList.begin();
			while (buttonIter != buttonList.end())
			{
				HUDElement* element = (*buttonIter++);
				if (i == indexSelected)
				{
					element->setSelected(true);
					break;
				}

				i++;
			}
		}
	}
}
// ------------------------------------------------------------------------------------------------------------
void StandardMenu::navigateDown()
{
	int eleCount = buttonList.size();

	if (eleCount > 0)
	{

		bool foundSelected = false;
		int indexSelected = 0;

		// Find a selected element to be our index
		buttonIter = buttonList.begin(); 
		while (buttonIter != buttonList.end())
		{
			HUDElement* element = (*buttonIter++);
			if (element->isSelected())
			{
				foundSelected = true;
				break;
			}
			indexSelected++;
		}

		// If we did not find a selected button
		if (!foundSelected)
		{
			(*buttonList.begin())->setSelected(true); 
		}
		// else select the previous one that was selected
		else
		{
			// First deselect the old one
			int i = 0;
			buttonIter = buttonList.begin();
			while (buttonIter != buttonList.end())
			{
				HUDElement* element = (*buttonIter++);
				if (i == indexSelected)
				{
					element->setSelected(false);

					indexSelected++;
					if (indexSelected >= eleCount)
						indexSelected = 0;

					break;
				}

				i++;
			}

			// Now select the new one
			i = 0;
			buttonIter = buttonList.begin();
			while (buttonIter != buttonList.end())
			{
				HUDElement* element = (*buttonIter++);
				if (i == indexSelected)
				{
					element->setSelected(true);
					break;
				}

				i++;
			}
		}
	}
}
// ------------------------------------------------------------------------------------------------------------
void StandardMenu::navigateForward()
{
	// Find the selected button, set the output and leave
	buttonIter = buttonList.begin();
	while (buttonIter != buttonList.end())
	{
		HUDElement* element = (*buttonIter++);
		if (element->isSelected())
		{
			setOutput(element->getOutput());
			close();
			break;
		}
	}
}
// ------------------------------------------------------------------------------------------------------------
void StandardMenu::navigateBackward()
{
	// De select all buttons
	buttonIter = buttonList.begin(); 
	while (buttonIter != buttonList.end())
		(*buttonIter++)->setSelected(false);

	close();
}
//-------------------------------------------------------------------------------------------------------------
void StandardMenu::navigateMouse(float mx, float my)
{
	// Find and select a button under the mouse
	buttonIter = buttonList.begin(); 
	while (buttonIter != buttonList.end())
	{
		HUDElement* button = (*buttonIter++);
		if (button->inside(mx, my))
			button->setSelected(true);
		else
			button->setSelected(false);
	}
}
//-------------------------------------------------------------------------------------------------------------