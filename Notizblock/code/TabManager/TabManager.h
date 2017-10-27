#pragma once
#include "SFML\Graphics.hpp"

#include "..\Tab\Tab.h"
#include "..\GUI\Button\Button.h"

class TabManager
{
	public:

		void Create(sf::RenderWindow *window);

		void Update();
		void Render();

		void Resize();

	private:

		void CreateNewTab();

		sf::RenderWindow *_MainWindow;

		std::vector<Tab*> _OpenTabs;
		std::vector<Button*> _Buttons;
		
		Button _CreateButton;

		int _ActiveTabIndex;
		int _XPosition;
};