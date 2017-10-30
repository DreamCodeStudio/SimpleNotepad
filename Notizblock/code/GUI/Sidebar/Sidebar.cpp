#include "Sidebar.h"

void Sidebar::Create(sf::RenderWindow *window)
{
	_MainWindow = window;

	/* Load background */
	_SidebarBackgroundTexture.loadFromFile("Data\\Textures\\Sidebar.png");
	_SidebarBackgroundSprite.setTexture(_SidebarBackgroundTexture);
	_SidebarBackgroundSprite.setPosition(sf::Vector2f(5, 10));
	
	/* Create Sidebar elements */
	for (unsigned int c = 0; c < 6; c++)
	{
		_Elements.push_back(new Element);
	}
	_Elements[0]->Create(_MainWindow, "Data\\Elements\\Small.png", sf::Vector2f(18, 30));
	_Elements[1]->Create(_MainWindow, "Data\\Elements\\Medium.png", sf::Vector2f(18, 120));
	_Elements[2]->Create(_MainWindow, "Data\\Elements\\Big.png", sf::Vector2f(18, 210));
	_Elements[3]->Create(_MainWindow, "Data\\Elements\\Red.png", sf::Vector2f(18, 300));
	_Elements[4]->Create(_MainWindow, "Data\\Elements\\Green.png", sf::Vector2f(18, 390));
	_Elements[5]->Create(_MainWindow, "Data\\Elements\\Blue.png", sf::Vector2f(18, 480));
}

void Sidebar::Render()
{
	_MainWindow->draw(_SidebarBackgroundSprite);

	/* Render all Elements */
	for (unsigned int c = 0; c < _Elements.size(); c++)
	{
		_Elements[c]->Render();
	}
}

void Sidebar::Update()
{
	/* Update all Elements */
	for (unsigned int c = 0; c < _Elements.size(); c++)
	{
		_Elements[c]->Update();
	}
}

void Sidebar::SetScale(sf::Vector2f NewScale)
{
	_SidebarBackgroundSprite.setScale(NewScale);
	std::cout << NewScale.x << std::endl;

	/* Scale all Elements */
	for (unsigned int c = 0; c < _Elements.size(); c++)
	{
		_Elements[c]->SetScale(NewScale);
		_Elements[c]->SetPosition(sf::Vector2f(_SidebarBackgroundSprite.getPosition().x + (13 * NewScale.x), _SidebarBackgroundSprite.getPosition().y + (20 * NewScale.x) + (90.0f * NewScale.x * c)));
	}
}