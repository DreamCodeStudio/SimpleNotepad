#include "TabManager.h"

void TabManager::Create(sf::RenderWindow *window)
{
	_MainWindow = window;

	/* Set start value */
	_XPosition = 10;

	/* Create the first Tab */
	this->CreateNewTab();

	_CreateButton.Create(_MainWindow, -1, sf::Vector2f(1700, 950));

	_ActiveTabIndex = 0;
}

void TabManager::Update()
{
	/* Update all open tabs */
	for (unsigned int c = 0; c < _OpenTabs.size(); c++)
	{
		_OpenTabs[c]->Update();
	}
	/* Update all Buttons */
	for (unsigned int c = 0; c < _Buttons.size(); c++)
	{
		_Buttons[c]->Update();

		/* If the user wants to change the active tab */
		if (_Buttons[c]->IsPressed())
		{
			_OpenTabs[_ActiveTabIndex]->SetVisibility(false);
			_OpenTabs[c]->SetVisibility(true);
			_ActiveTabIndex = c;
		}
	}

	_CreateButton.Update();

	/* If the Create button was pressed */
	if (_CreateButton.IsPressed())
	{
		this->CreateNewTab();
	}
}

void TabManager::Render()
{
	/* Render all open tabs */
	for (unsigned int c = 0; c < _OpenTabs.size(); c++)
	{
		_OpenTabs[c]->Render();
	}
	/* Render all Buttons */
	for (unsigned int c = 0; c < _Buttons.size(); c++)
	{
		_Buttons[c]->Render();
	}

	_CreateButton.Render();
}

void TabManager::CreateNewTab()
{
	/* Set all other tabs invisible */
	for (unsigned int c = 0; c < _OpenTabs.size(); c++)
	{
		_OpenTabs[c]->SetVisibility(false);
	}

	/* Create new Tab */
	_OpenTabs.push_back(new Tab);
	_OpenTabs[_OpenTabs.size() - 1]->Create(_MainWindow);
	_OpenTabs[_OpenTabs.size() - 1]->SetVisibility(true);

	_Buttons.push_back(new Button);
	_Buttons[_Buttons.size() - 1]->Create(_MainWindow, _Buttons.size(), sf::Vector2f(static_cast<float>(_XPosition), 950));

	_ActiveTabIndex = static_cast<int>(_OpenTabs.size() - 1);

	_XPosition += 200;
}