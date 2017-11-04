#pragma once
#include <SFML\Graphics.hpp>

#include <iostream>

class Textbox
{
	public:

		void Create(sf::RenderWindow *window, sf::Vector2f StartPosition, int CharacterSize, sf::Color TextColor);

		void Render();
		void OnTextEntered(char Input);
		void Finish();

		std::string GetText();
		void Clear();

	private:

		void UpdateDisplayText();

		sf::RenderWindow *_MainWindow;

		std::string _TextStr;
		std::vector<sf::Text*> _Text;
		sf::Font _Font;
		sf::RectangleShape _Cursor;

		float _StartX, _StartY;
		int _CharacterSize;
		sf::Color _TextColor;
};