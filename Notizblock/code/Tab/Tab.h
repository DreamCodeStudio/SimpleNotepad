#pragma once
#include <SFML\Graphics.hpp>
#include <fstream>

#include "..\GUI\Textbox\Textbox.h"
#include "..\..\GUI\Sidebar\Sidebar.h"

class Tab
{
	public:

		void Create(sf::RenderWindow *window);

		void Update();
		void Render();

		void SetVisibility(bool NewStatus);

		void OnResizeEvent();
		void OnTextEnteredEvent(char Input);

		void SaveToFile(std::string FileName);
		void LoadFromFile(std::string FileName);

	private:

		void UpdateSidebar();
		void UpdateTextboxes();

		sf::RenderWindow *_MainWindow;

		bool _IsVisible;
		bool _IsDrawing;

		sf::Texture _BackgroundTexture;
		sf::Sprite _BackgroundSprite;


		/* Drawing */
		std::vector<std::vector<sf::CircleShape*>> _DrawingStack;
		std::vector<sf::CircleShape*> _CurrentDrawing;
		sf::Clock _UndoCooldown;

		/* Textbox */
		std::vector<Textbox*> _Textboxes;

		/* Sidebar */
		Sidebar _Sidebar;
		
		/* Sidebar settings */
		sf::Color _SelectedColor;
		int _SelectedWritingSize;
		float _SelectedDrawingSize;
};