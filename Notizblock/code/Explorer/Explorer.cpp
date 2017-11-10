#include "Explorer.h"

void Explorer::Create(sf::RenderWindow *window)
{
	_MainWindow = window;
	
	/* Create Textbox */
	_Textbox.Create(_MainWindow, sf::Vector2f(10, 10), 30, sf::Color(0, 0, 0));

	/* Create Background */
	_Background.setFillColor(sf::Color(174, 255, 173));
	_Background.setSize(sf::Vector2f(1920, 50));
	_Background.setPosition(sf::Vector2f(0, 0));
}

void Explorer::Open()
{
	_IsVisible = true;
}

void Explorer::Close()
{
	_IsVisible = false;
}

void Explorer::Render()
{
	if (_IsVisible == false)
	{
		return;
	}

	/* Render bacakground */
	_MainWindow->draw(_Background);

	/* Render Textbox */
	_Textbox.Render();
}

void Explorer::Update()
{
	if (_IsVisible == false)
	{
		return;
	}

	_Textbox.Update();
}

void Explorer::OnTextEnteredEvent(char Input)
{
	_Textbox.OnTextEntered(Input);
}

bool Explorer::IsOpen()
{
	return _IsVisible;
}

std::string Explorer::GetText()
{
	return _Textbox.GetText();
}

void Explorer::Clear()
{
	_Textbox.Clear();
}