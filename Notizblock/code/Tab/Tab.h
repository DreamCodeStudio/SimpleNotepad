#pragma once
#include <SFML\Graphics.hpp>

#include "..\GUI\Textbox\Textbox.h"

class Tab
{
	public:

		void Create(sf::RenderWindow *window);

		void Update();
		void Render();

		void SetVisibility(bool NewStatus);

		void OnTextEnteredEvent(char Input);

	private:

		sf::RenderWindow *_MainWindow;

		bool _IsVisible;
		bool _IsDrawing;

		sf::Texture _BackgroundTexture;
		sf::Sprite _BackgroundSprite;


		/* Drawing */
		float _Radius;
		sf::Color _Color;
		std::vector<std::vector<sf::CircleShape*>> _DrawingStack;
		std::vector<sf::CircleShape*> _CurrentDrawing;
		sf::Clock _UndoCooldown;

		/* Textbox */
		Textbox _Textbox;


};