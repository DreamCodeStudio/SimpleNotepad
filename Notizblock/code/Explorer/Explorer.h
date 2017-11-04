#pragma once
#include <SFML\Graphics.hpp>

#include "..\GUI\Textbox\Textbox.h"

class Explorer
{
	public:

		void Create(sf::RenderWindow *window);
		void Open();
		void Close();

		void Render();
		void OnTextEnteredEvent(char Input);

		void Clear();
		bool IsOpen();
		std::string GetText();

	private:

		sf::RenderWindow *_MainWindow;

		Textbox _Textbox;
		sf::RectangleShape _Background;

		bool _IsVisible;
};