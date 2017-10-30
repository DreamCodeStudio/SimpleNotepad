#pragma once
#include <SFML\Graphics.hpp>

#include <iostream>

class Textbox
{
	public:

		void Create(sf::RenderWindow *window);

		void Render();
		void OnTextEntered(char Input);

	private:

		void UpdateDisplayText();

		sf::RenderWindow *_MainWindow;

		std::string _TextStr;
		std::vector<sf::Text*> _Text;
		sf::Font _Font;

};