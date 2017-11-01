#include "Tab.h"

void Tab::Create(sf::RenderWindow *window)
{
	_MainWindow = window;

	/* Set start values */

	_IsVisible = false;
	_IsDrawing = false;
	_IsWriting = false;

	_SelectedColor = sf::Color(0, 0, 0);
	_SelectedDrawingSize = 3.0f;
	_SelectedWritingSize = 30;

	/* Set a white rectangle as background */
	_BackgroundTexture.loadFromFile("Data\\Textures\\Background.png");
	_BackgroundSprite.setTexture(_BackgroundTexture);

	/* Create Sidebar */
	_Sidebar.Create(_MainWindow);
}

void Tab::SetVisibility(bool NewStatus)
{
	_IsVisible = NewStatus;
}

void Tab::Update()
{
	if (_IsVisible == false && _MainWindow->hasFocus())
	{
		return;
	}

	/* If the left mouse button is pressed - the user wants to draw */
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _IsWriting == false)
	{
		_IsDrawing = true; //User is drawing

		_CurrentDrawing.push_back(new sf::CircleShape); //Create new circle 
		_CurrentDrawing[_CurrentDrawing.size() - 1]->setRadius(_SelectedDrawingSize);	//set radius
		_CurrentDrawing[_CurrentDrawing.size() - 1]->setFillColor(_SelectedColor);	//set color
		_CurrentDrawing[_CurrentDrawing.size() - 1]->setPosition(sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(*_MainWindow).x), static_cast<float>(sf::Mouse::getPosition(*_MainWindow).y))); //set position
	}
	else
	{
		/* If the user just stopped drawing */
		if (_IsDrawing == true)
		{
			_DrawingStack.push_back(_CurrentDrawing); //Safe the drawing of the user
			_CurrentDrawing.clear();				  //Clear the CurrentDrawing vector
			_IsDrawing = false;						  //User stopped drawing
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && _IsDrawing == false)
	{
		/* The user wants to write something */
		_IsWriting = true;

		/* Create new Textbox */
		_Textboxes.push_back(new Textbox);
		_Textboxes[_Textboxes.size() - 1]->Create(_MainWindow, sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(*_MainWindow).x), static_cast<float>(sf::Mouse::getPosition(*_MainWindow).y)), _SelectedWritingSize, _SelectedColor);
	}

	/* Exit from writing to drawing */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		_IsWriting = false;
	}

	/* If the user wants to undo the last drawing */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && _UndoCooldown.getElapsedTime().asMilliseconds() > sf::milliseconds(500).asMilliseconds() && _DrawingStack.size() > 0)
	{
		_DrawingStack.pop_back();
		_UndoCooldown.restart();
	}

	this->UpdateSidebar();
}

void Tab::UpdateSidebar()
{
	_Sidebar.Update();

	if (_Sidebar.GetPressedElement() != -1)
	{
		if (_Sidebar.GetPressedElement() == 0)
		{
			_SelectedWritingSize = 20;
			_SelectedDrawingSize = 1.5f;
		}
		if (_Sidebar.GetPressedElement() == 1)
		{
			_SelectedWritingSize = 30;
			_SelectedDrawingSize = 3.0f;
		}
		if (_Sidebar.GetPressedElement() == 2)
		{
			_SelectedWritingSize = 30;
			_SelectedDrawingSize = 4.5f;
		}
		if (_Sidebar.GetPressedElement() == 3)
		{
			_SelectedColor = sf::Color(255, 0, 0);
		}
		if (_Sidebar.GetPressedElement() == 4)
		{
			_SelectedColor = sf::Color(0, 255, 0);
		}
		if (_Sidebar.GetPressedElement() == 5)
		{
			_SelectedColor = sf::Color(0, 0, 0);
		}
	}
}

void Tab::Render()
{
	if (_IsVisible == false)
	{
		return;
	}

	/* Render Background */
	_MainWindow->draw(_BackgroundSprite);

	/* Draw the whole vector to the screen */
	for (unsigned int c = 0; c < _DrawingStack.size(); c++)
	{
		for (unsigned int i = 0; i < _DrawingStack[c].size(); i++)
		{
			_MainWindow->draw(*_DrawingStack[c][i]);
		}
	}

	/* Draw all the the circle in the CurrentDrawing vector */
	for (unsigned int c = 0; c < _CurrentDrawing.size(); c++)
	{
		_MainWindow->draw(*_CurrentDrawing[c]);
	}

	/* Render the text */
	for (unsigned int c = 0; c < _Textboxes.size(); c++)
	{
		_Textboxes[c]->Render();
	}

	/* Render sidebar */
	_Sidebar.Render();
}

void Tab::OnResizeEvent()
{
	float Factor = _MainWindow->getSize().y / 1080.0f;
	_Sidebar.SetScale(sf::Vector2f(Factor, Factor));
}

void Tab::OnTextEnteredEvent(char Input)
{
	if (_IsWriting == true)
	{
		_Textboxes[_Textboxes.size() - 1]->OnTextEntered(Input);
	}
}
