#pragma once
#include <SFML\Graphics.hpp>

#include <iostream>

class Textbox
{
	public:

		void Create(sf::RenderWindow *window, sf::Vector2f StartPosition, int CharacterSize, sf::Color TextColor);

		void Render();
		void OnTextEntered(char Input);

	private:

		void UpdateDisplayText();

		sf::RenderWindow *_MainWindow;

		std::string _TextStr;
		std::vector<sf::Text*> _Text;
		sf::Font _Font;

		float _StartX, _StartY;
		int _CharacterSize;
		sf::Color _TextColor;
};