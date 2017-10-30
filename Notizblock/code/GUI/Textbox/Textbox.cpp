#pragma warning(disable : 4996)
#include "Textbox.h"

void Textbox::Create(sf::RenderWindow *window)
{
	_MainWindow = window;

	/* Load font */
	_Font.loadFromFile("Data\\arial.ttf");
}

void Textbox::Render()
{
	/* Render every letter */
	for (unsigned int c = 0; c < _Text.size(); c++)
	{
		_MainWindow->draw(*_Text[c]);
	}
}

void Textbox::OnTextEntered(char Input)
{
	switch (static_cast<int>(Input))
	{
		/* Return */
		case 13: {
			_TextStr.push_back('\n');
		}
				 break;
		/* Backspace */
		case 8: {
			if (_TextStr.size() > 0)
			{
				_TextStr.pop_back();
			}
		}
				break;
		default: {
			/* Add letter to the string */
			_TextStr.push_back(Input);
			std::cout << "Input: " << Input << std::endl;
		}
	}

	this->UpdateDisplayText();
}

void Textbox::UpdateDisplayText()
{
	/* Clear the old output text */
	for (unsigned int c = 0; c < _Text.size(); c++)
	{
		delete _Text[c];
	}
	_Text.clear();

	/* Set the _TextStr as new output string */
	float StartXPosition = 50.0f;
	float StartYPosition = 20.0f;
	for (unsigned int c = 0; c < _TextStr.size(); c++)
	{
		_Text.push_back(new sf::Text);
		_Text[_Text.size() - 1]->setFont(_Font);
		_Text[_Text.size() - 1]->setCharacterSize(20);
		_Text[_Text.size() - 1]->setColor(sf::Color(0, 0, 0));
		_Text[_Text.size() - 1]->setPosition(sf::Vector2f(StartXPosition, StartYPosition));
		_Text[_Text.size() - 1]->setString(_TextStr[c]);

		StartXPosition += _Text[_Text.size() - 1]->getGlobalBounds().width;
		if (StartXPosition >= _MainWindow->getSize().x)
		{
			StartXPosition = 50.0f;
			StartYPosition += _Text[_Text.size() - 1]->getCharacterSize();
		}
		if (_TextStr[c] == '\n')
		{
			StartXPosition = 50.0f;
			StartYPosition += _Text[_Text.size() - 1]->getCharacterSize();
		}
	}
}