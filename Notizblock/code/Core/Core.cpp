#include "Core.h"

Core::Core()
{
	_MainWindow.create(sf::VideoMode(1420, 580), "Notizblock");

	_TabManager.Create(&_MainWindow);
}

void Core::Run()
{
	this->HandleEvents();
	this->Update();
	this->Render();
}

bool Core::IsOpen()
{
	return _MainWindow.isOpen();
}

/* ############## Private ############### */

void Core::HandleEvents()
{
	sf::Event event;
	while (_MainWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_MainWindow.close();
			return;
		}
		if (event.type == sf::Event::Resized)
		{
			/* If the window gets resized */
			_MainWindow.setView(sf::View(sf::FloatRect(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height))));
			_TabManager.OnResizeEvent();
		}
		if (event.type == sf::Event::TextEntered)
		{
			// Core receives Input -> TabManager -> Active Tab -> Textbox
			//									\
			//									 -> Explorer   -> Textbox

			_TabManager.OnTextEnteredEvent(event.text.unicode);
		}
	}
}

void Core::Update()
{
	_TabManager.Update();
}

void Core::Render()
{
	_MainWindow.clear();

	_TabManager.Render();

	_MainWindow.display();
}