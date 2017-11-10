#pragma once
#include <SFML\Graphics.hpp>

#include <iostream>

class Textbox
{
	public:

		void Create(sf::RenderWindow *window, sf::Vector2f StartPosition, int CharacterSize, sf::Color TextColor);

		void Render();
		void Update();
		
		void OnTextEntered(char Input);
		void SetText(std::string NewText);
		void SetActiveStatus(bool NewStatus);

		int GetCharacterSize();
		std::string GetText();
		sf::Color GetColor();
		sf::Vector2f GetStartPosition();
		void Clear();

	private:

		void UpdateDisplayText();
		void UpdateActivityStatus();
		void UpdateCursorMovement();

		void SetCursorVisibility(bool NewStatus);

		sf::RenderWindow *_MainWindow;

		bool _IsActive;

		sf::Vector2f _StartPosition;
		std::string _TextStr;
		std::vector<sf::Text*> _Text;
		sf::Font _Font;
		sf::RectangleShape _Cursor;

		int _CursorPosition;
		float _StartX, _StartY;
		int _CharacterSize;
		sf::Color _TextColor;
};