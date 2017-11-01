#pragma warning(disable : 4996)
#include "Textbox.h"

void Textbox::Create(sf::RenderWindow *window, sf::Vector2f StartPosition, int CharacterSize, sf::Color TextColor)
{
	_MainWindow = window;

	/* Load font */
	_Font.loadFromFile("Data\\Fonts\\arial.ttf");

	/* Set start values */
	_StartX = StartPosition.x;
	_StartY = StartPosition.y;

	_CharacterSize = CharacterSize;
	_TextColor = TextColor;
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) //If the user pressed CTRL + Z to undo the last drawing, the user does not want to write some text
	{
		return;
	}
	switch (static_cast<int>(Input))
	{
		/* Return */
		case 13: {
			_TextStr.push_back('\n');
		}
				 break;
		/* Backspace */
		case 8: {
			if (_TextStr.size() > 0)  //If theres something to delete
			{
				_TextStr.pop_back();	//Delete the last written letter
			}
		}
				break;
		/* Escape */
		case 27: {
			//Exit 
		}
				 break;
		default: {
			/* Add letter to the string */
			_TextStr.push_back(Input);
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
	float StartXPosition = _StartX;
	float StartYPosition = _StartY;
	for (unsigned int c = 0; c < _TextStr.size(); c++)
	{
		_Text.push_back(new sf::Text);
		_Text[_Text.size() - 1]->setFont(_Font);
		_Text[_Text.size() - 1]->setCharacterSize(_CharacterSize);
		_Text[_Text.size() - 1]->setColor(_TextColor);
		_Text[_Text.size() - 1]->setPosition(sf::Vector2f(StartXPosition, StartYPosition));
		_Text[_Text.size() - 1]->setString(_TextStr[c]);

		StartXPosition += _Text[_Text.size() - 1]->getGlobalBounds().width + 2;
		if (StartXPosition >= _MainWindow->getSize().x)
		{
			StartXPosition = _StartX;
			StartYPosition += _Text[_Text.size() - 1]->getCharacterSize();
		}
		if (_TextStr[c] == '\n')
		{
			StartXPosition = _StartX;
			StartYPosition += _Text[_Text.size() - 1]->getCharacterSize();
		}
	}
}
