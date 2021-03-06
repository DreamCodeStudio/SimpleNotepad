#include "Element.h"

void Element::Create(sf::RenderWindow *window, std::string IconPath, sf::Vector2f Position)
{
	_MainWindow = window;

	_IconTexture.loadFromFile(IconPath);
	_IconSprite.setTexture(_IconTexture);
	_IconSprite.setPosition(Position);
}

void Element::Render()
{
	_MainWindow->draw(_IconSprite);
}

void Element::Update()
{
	_IsPressed = false;
	_IconSprite.setColor(sf::Color(255, 255, 255));

	if (sf::Mouse::getPosition(*_MainWindow).x > _IconSprite.getPosition().x && sf::Mouse::getPosition(*_MainWindow).x < _IconSprite.getPosition().x + _IconSprite.getGlobalBounds().width &&
		sf::Mouse::getPosition(*_MainWindow).y > _IconSprite.getPosition().y && sf::Mouse::getPosition(*_MainWindow).y < _IconSprite.getPosition().y + _IconSprite.getGlobalBounds().height)

	{
		_IconSprite.setColor(sf::Color(150, 150, 150));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			_IconSprite.setColor(sf::Color(50, 50, 50));
			_IsPressed = true;
		}
	}
}

bool Element::IsPressed()
{
	return _IsPressed;
}

void Element::SetScale(sf::Vector2f NewScale)
{
	_IconSprite.setScale(NewScale);
}

void Element::SetPosition(sf::Vector2f NewPosition)
{
	_IconSprite.setPosition(NewPosition);
}