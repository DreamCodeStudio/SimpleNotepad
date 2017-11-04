#pragma once
#include "SFML\Graphics.hpp"

#include "..\Tab\Tab.h"
#include "..\GUI\Button\Button.h"
#include "..\Explorer\Explorer.h"

#define NO_PROGRESS 0
#define SAVE_PROGRESS 1
#define LOAD_PROGRESS 2

class TabManager
{
	public:

		void Create(sf::RenderWindow *window);

		void Update();
		void Render();

		void OnResizeEvent();
		void OnTextEnteredEvent(char Input);

	private:

		void CreateNewTab();

		sf::RenderWindow *_MainWindow;

		std::vector<Tab*> _OpenTabs;
		std::vector<Button*> _Buttons;
		
		Button _CreateButton, _SafeButton, _LoadButton;

		int _ActiveTabIndex;
		int _XPosition;

		Explorer _Explorer;
		int _CurrentProgress;

};