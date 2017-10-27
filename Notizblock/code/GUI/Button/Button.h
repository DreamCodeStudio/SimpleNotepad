#pragma once
#include <SFML\Graphics.hpp>

#include <iostream>
#include <sstream>

class Button
{
	public:

		void Create(sf::RenderWindow *window, int Number, sf::Vector2f Position);

		void Update();
		void Render();

		bool IsPressed();

		void SetPosition(sf::Vector2f NewPosition);
		void SetScale(sf::Vector2f NewScale);

	private:

		sf::RenderWindow *_MainWindow;

		sf::Texture _BackgroundTexture;
		sf::Sprite _BackgroundSprite;
		sf::Font _Font;
		sf::Text _NumberText;
		sf::Clock _Cooldown;

		bool _IsPressed;
};