#pragma warning(disable : 4996)
#include "Button.h"

void Button::Create(sf::RenderWindow *window, int Number, sf::Vector2f Position)
{
	_MainWindow = window;
	
	/* Load the background image of the button */
	_BackgroundTexture.loadFromFile("Data\\ButtonBackground.png");
	_BackgroundSprite.setTexture(_BackgroundTexture);

	/* Load the font */
	_Font.loadFromFile("Data\\arial.ttf");

	/* Convert int to string and set the string as output text */
	std::string StrNumber;
	std::stringstream str;
	str << Number;
	str >> StrNumber;
	
	if (Number == -1)
	{
		StrNumber = "+";
	}

	_NumberText.setString(StrNumber);
	_NumberText.setFont(_Font);
	_NumberText.setCharacterSize(20);
	_NumberText.setColor(sf::Color(50, 50, 50));

	this->SetPosition(Position);
}

void Button::Update()
{
	/* If the mouse hovers over the button */
	if (sf::Mouse::getPosition(*_MainWindow).x > _BackgroundSprite.getPosition().x && sf::Mouse::getPosition(*_MainWindow).x < _BackgroundSprite.getPosition().x + _BackgroundSprite.getGlobalBounds().width &&
		sf::Mouse::getPosition(*_MainWindow).y > _BackgroundSprite.getPosition().y && sf::Mouse::getPosition(*_MainWindow).y < _BackgroundSprite.getPosition().y + _BackgroundSprite.getGlobalBounds().height)
	{
		_IsPressed = false;
		_BackgroundSprite.setColor(sf::Color(150, 150, 150));

		/* Check if the button is pressed */
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _Cooldown.getElapsedTime().asMilliseconds() > sf::milliseconds(500).asMilliseconds())
		{
			/* Change color */
			_BackgroundSprite.setColor(sf::Color(50, 50, 50));
			_IsPressed = true;
			_Cooldown.restart();
		}
	}
	else
	{
		/* Default color */
		_BackgroundSprite.setColor(sf::Color(255, 255, 255));
	}
}

void Button::Render()
{
	/* Draw background and label */
	_MainWindow->draw(_BackgroundSprite);
	_MainWindow->draw(_NumberText);
}

bool Button::IsPressed()
{
	if (_IsPressed == true)
	{
		_IsPressed = false;
		return true;
	}

	return false;
}

void Button::SetPosition(sf::Vector2f NewPosition)
{
	_BackgroundSprite.setPosition(NewPosition);
	_NumberText.setPosition(sf::Vector2f(_BackgroundSprite.getPosition().x + ((_BackgroundSprite.getGlobalBounds().width - _NumberText.getGlobalBounds().width) / 2), _BackgroundSprite.getPosition().y + ((_BackgroundSprite.getGlobalBounds().height - _NumberText.getGlobalBounds().height) / 2)));
}

void Button::SetScale(sf::Vector2f NewScale)
{
	_BackgroundSprite.setScale(NewScale);
	_NumberText.setScale(NewScale);
}