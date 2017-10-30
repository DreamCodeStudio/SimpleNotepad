#pragma once
#include <SFML\Graphics.hpp>

class Element
{
	public:

		void Create(sf::RenderWindow *window, std::string IconPath, sf::Vector2f Position);

		void Render();
		void Update();

		void SetScale(sf::Vector2f NewScale);
		void SetPosition(sf::Vector2f NewPosition);

		bool IsPressed();

	private:

		sf::RenderWindow *_MainWindow;

		sf::Texture _IconTexture;
		sf::Sprite _IconSprite;

		bool _IsPressed;
	
};