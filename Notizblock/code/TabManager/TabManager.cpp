#include "TabManager.h"

void TabManager::Create(sf::RenderWindow *window)
{
	_MainWindow = window;

	/* Set start value */
	_XPosition = 10;

	/* Create the first Tab */
	this->CreateNewTab();

	/* Create CreateButton */
	_CreateButton.Create(_MainWindow, -1, sf::Vector2f(1700, 950));
	this->OnResizeEvent();	//If the window is not opened with 1920x1080 resolution

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
	if (_CreateButton.IsPressed() && _OpenTabs.size() < 8) //Max. 8 tabs open
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

void TabManager::OnResizeEvent()
{
	float ScaleFactor = _MainWindow->getSize().x / 1920.0f;

	/* Scale the tab buttons */
	for (unsigned int c = 0; c < _OpenTabs.size(); c++)
	{
		_Buttons[c]->SetScale(sf::Vector2f(ScaleFactor, ScaleFactor));
		_Buttons[c]->SetPosition(sf::Vector2f(200.0f * ScaleFactor * c, static_cast<float>(_MainWindow->getSize().y - 70 * ScaleFactor)));
	}

	_CreateButton.SetScale(sf::Vector2f(ScaleFactor, ScaleFactor));
	_CreateButton.SetPosition(sf::Vector2f(_MainWindow->getSize().x - 200.0f * ScaleFactor, static_cast<float>(_MainWindow->getSize().y - 70 * ScaleFactor)));

	_OpenTabs[_ActiveTabIndex]->OnResizeEvent(); //The Sidebar (which is owned by the Tab class) must rescale too
}

void TabManager::OnTextEnteredEvent(char Input)
{
	_OpenTabs[_ActiveTabIndex]->OnTextEnteredEvent(Input);
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
	this->OnResizeEvent(); //Check if the new tab button should be resized
}