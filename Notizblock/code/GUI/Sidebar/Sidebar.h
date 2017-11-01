#pragma once
#include <SFML\Graphics.hpp>

#include <iostream>
#include "Element\Element.h"

class Sidebar
{
	public:

		void Create(sf::RenderWindow *window);

		void Render();
		void Update();

		void SetScale(sf::Vector2f NewScale);

		int GetPressedElement();

	private:

		sf::RenderWindow *_MainWindow;

		sf::Texture _SidebarBackgroundTexture;
		sf::Sprite _SidebarBackgroundSprite;

		//_Small, _Medium, _Big, _Red, _Green, _Blue;
		std::vector<Element*> _Elements; 

};