#pragma once
#include <SFML\Graphics.hpp>

#include "..\TabManager\TabManager.h"

class Core
{
	public:

		Core();

		void Run();
		bool IsOpen();

	private:

		void HandleEvents();
		void Update();
		void Render();

		sf::RenderWindow _MainWindow;

		TabManager _TabManager;

};