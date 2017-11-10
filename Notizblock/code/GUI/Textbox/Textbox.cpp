#pragma warning(disable : 4996)
#include "Textbox.h"

void Textbox::Create(sf::RenderWindow *window, sf::Vector2f StartPosition, int CharacterSize, sf::Color TextColor)
{
	_MainWindow = window;
	_StartPosition = StartPosition;

	/* Load font */
	_Font.loadFromFile("Data\\Fonts\\arial.ttf");

	/* Set start values */
	_StartX = StartPosition.x;
	_StartY = StartPosition.y;

	/* Create Cursor */
	_Cursor.setSize(sf::Vector2f(3.0f, static_cast<float>(CharacterSize)));
	_Cursor.setFillColor(TextColor);
	_Cursor.setPosition(StartPosition);
	_CursorPosition = 0;

	_CharacterSize = CharacterSize;
	_TextColor = TextColor;

	_IsActive = true;

}

void Textbox::Render()
{
	/* Render Cursor */
	_MainWindow->draw(_Cursor);

	/* Render every letter */
	for (unsigned int c = 0; c < _Text.size(); c++)
	{
		_MainWindow->draw(*_Text[c]);
	}
}

void Textbox::Update()
{
	this->UpdateActivityStatus(); //Check if the user wants to select this textbox 
	this->UpdateCursorMovement(); //Check if the user want to move the cursor 
}

void Textbox::OnTextEntered(char Input)
{
	if (_IsActive == false) //If the textbox is not selected anymore
	{
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) //If the user pressed CTRL + Z to undo the last drawing, the user does not want to write some text
	{
		return;
	}

	switch (static_cast<int>(Input))
	{
		/* Return */
		case 13: {
			/* Add return to the string */
			if (_TextStr.size() == _CursorPosition)
			{
				_TextStr.push_back('\n');
			}
			else
			{
				_TextStr.insert(_TextStr.begin() + _CursorPosition, '\n');
			}

			_CursorPosition++;
		}
				 break;
		/* Backspace */
		case 8: {

			if (_TextStr.size() == 0)
			{
				return;
			}

			if (_CursorPosition == _TextStr.size())
			{
				_TextStr.pop_back();	//Delete the last written letter
				_CursorPosition--;
			}
			else
			{
				if (_CursorPosition > 0)
				{
					_TextStr.erase(_TextStr.begin() + _CursorPosition - 1, _TextStr.begin() + _CursorPosition);
					_CursorPosition--;
				}
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
			if (_TextStr.size() == _CursorPosition)
			{
				_TextStr.push_back(Input);
			}
			else
			{
				_TextStr.insert(_TextStr.begin() + _CursorPosition, Input);
			}

			_CursorPosition++;
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

void Textbox::UpdateActivityStatus()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		_IsActive = false;
		this->SetCursorVisibility(false);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		/* Get the Width of the textbox */
		float WidthMax = 0;
		float Width = 0;
		float LineCounter = 1;
		for (unsigned int c = 0; c < _Text.size(); c++)  //Go threw all written letters to find out what the width and heigh of the Textbox is
		{
			if (_Text[c]->getString() != "\n")  
			{
				Width = Width + _Text[c]->getGlobalBounds().width;
			}
			else
			{
				LineCounter++;
				if (Width > WidthMax)
				{
					WidthMax = Width;
				}
				Width = 0;
			}
		}
		if (LineCounter == 1)
		{
			WidthMax = Width;
		}

		/* If the user clicks on the Textbox he wants to select it again */
		if (sf::Mouse::getPosition(*_MainWindow).x > _StartPosition.x && sf::Mouse::getPosition(*_MainWindow).x < _StartPosition.x + WidthMax &&
			sf::Mouse::getPosition(*_MainWindow).y > _StartPosition.y && sf::Mouse::getPosition(*_MainWindow).y < _StartPosition.y + LineCounter * _CharacterSize)
		{
			_IsActive = true;
			this->SetCursorVisibility(true);
		}
	}
}

void Textbox::UpdateCursorMovement()
{
	if (_IsActive == false)
	{
		return;
	}

	/* Check if the user moved the cursor */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && _CursorPosition > 0)
	{
		_CursorPosition--;
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && _CursorPosition < static_cast<int>(_TextStr.size()))
	{
		_CursorPosition++;
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
	}
	
	if (_CursorPosition > 0)
	{
		_Cursor.setPosition(_Text[_CursorPosition - 1]->getPosition().x + _Text[_CursorPosition - 1]->getGlobalBounds().width, _Text[_CursorPosition - 1]->getPosition().y);
	}
	if (_CursorPosition == 0)
	{
		_Cursor.setPosition(_StartPosition);
	}
}

void Textbox::SetCursorVisibility(bool NewStatus)
{
	if (NewStatus == false)
	{
		_Cursor.setSize(sf::Vector2f(0, 0));
	}
	else
	{
		_Cursor.setSize(sf::Vector2f(3.0f, static_cast<float>(_CharacterSize)));
	}
}

int Textbox::GetCharacterSize()
{
	return _CharacterSize;
}

sf::Color Textbox::GetColor()
{
	return _TextColor;
}

sf::Vector2f Textbox::GetStartPosition()
{
	return _StartPosition;
}

std::string Textbox::GetText()
{
	return _TextStr;
}

void Textbox::Clear()
{
	/* Clear the textbox */
	for (unsigned int c = 0; c < _Text.size(); c++)
	{
		delete _Text[c];
	}
	_Text.clear();
	_TextStr.clear();

	_CursorPosition = 0;
}

void Textbox::SetText(std::string NewText)
{
	_TextStr = NewText;
	_Cursor.setSize(sf::Vector2f(0, 0));
	this->UpdateDisplayText();
}

void Textbox::SetActiveStatus(bool NewStatus)
{
	_IsActive = NewStatus;
}