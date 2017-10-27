#pragma once
#include <SFML\Graphics.hpp>

class Tab
{
	public:

		void Create(sf::RenderWindow *window);

		void Update();
		void Render();

		void SetVisibility(bool NewStatus);

	private:

		sf::RenderWindow *_MainWindow;

		bool _IsVisible;
		bool _IsDrawing;

		sf::Texture _BackgroundTexture;
		sf::Sprite _BackgroundSprite;

		float _Radius;
		sf::Color _Color;

		std::vector<std::vector<sf::CircleShape*>> _DrawingStack;
		std::vector<sf::CircleShape*> _CurrentDrawing;

		sf::Clock _UndoCooldown;

};