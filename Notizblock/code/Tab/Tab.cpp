#include "Tab.h"

void Tab::Create(sf::RenderWindow *window)
{
	_MainWindow = window;

	/* Set start values */

	_IsVisible = false;
	_IsDrawing = false;

	_SelectedColor = sf::Color(0, 0, 0);
	_SelectedDrawingSize = 3.0f;
	_SelectedWritingSize = 30;

	/* Set a white rectangle as background */
	_BackgroundTexture.loadFromFile("Data\\Textures\\Background.png");
	_BackgroundSprite.setTexture(_BackgroundTexture);

	/* Create Sidebar */
	_Sidebar.Create(_MainWindow);
}

void Tab::SetVisibility(bool NewStatus)
{
	_IsVisible = NewStatus;
}

void Tab::Update()
{
	if (_IsVisible == false && _MainWindow->hasFocus())
	{
		return;
	}

	/* If the left mouse button is pressed - the user wants to draw */
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		_IsDrawing = true; //User is drawing

		/* If theres already a point on the same position ...*/
		if (_CurrentDrawing.size() > 0)
		{
			if (sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(*_MainWindow).x), static_cast<float>(sf::Mouse::getPosition(*_MainWindow).y)) == _CurrentDrawing[_CurrentDrawing.size() - 1]->getPosition())
			{
				return; //Exit
			}
		}

		_CurrentDrawing.push_back(new sf::CircleShape); //Create new circle 
		_CurrentDrawing[_CurrentDrawing.size() - 1]->setRadius(_SelectedDrawingSize);	//set radius
		_CurrentDrawing[_CurrentDrawing.size() - 1]->setFillColor(_SelectedColor);	//set color
		_CurrentDrawing[_CurrentDrawing.size() - 1]->setPosition(sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(*_MainWindow).x), static_cast<float>(sf::Mouse::getPosition(*_MainWindow).y))); //set position
	}
	else
	{
		/* If the user just stopped drawing */
		if (_IsDrawing == true)
		{
			_DrawingStack.push_back(_CurrentDrawing); //Safe the drawing of the user
			_CurrentDrawing.clear();				  //Clear the CurrentDrawing vector
			_IsDrawing = false;						  //User stopped drawing
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && _IsDrawing == false)
	{
		/* Create new Textbox */
		_Textboxes.push_back(new Textbox);
		_Textboxes[_Textboxes.size() - 1]->Create(_MainWindow, sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(*_MainWindow).x), static_cast<float>(sf::Mouse::getPosition(*_MainWindow).y)), _SelectedWritingSize, _SelectedColor);
		while (sf::Mouse::isButtonPressed(sf::Mouse::Right));
	}

	/* If the user wants to undo the last drawing */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && _UndoCooldown.getElapsedTime().asMilliseconds() > sf::milliseconds(500).asMilliseconds() && _DrawingStack.size() > 0)
	{
		_DrawingStack.pop_back();
		_UndoCooldown.restart();
	}

	this->UpdateSidebar();
	this->UpdateTextboxes();
}

void Tab::UpdateSidebar()
{
	_Sidebar.Update();

	if (_Sidebar.GetPressedElement() != -1)
	{
		if (_Sidebar.GetPressedElement() == 0)
		{
			_SelectedWritingSize = 20;
			_SelectedDrawingSize = 1.5f;
		}
		if (_Sidebar.GetPressedElement() == 1)
		{
			_SelectedWritingSize = 30;
			_SelectedDrawingSize = 3.0f;
		}
		if (_Sidebar.GetPressedElement() == 2)
		{
			_SelectedWritingSize = 30;
			_SelectedDrawingSize = 4.5f;
		}
		if (_Sidebar.GetPressedElement() == 3)
		{
			_SelectedColor = sf::Color(255, 0, 0);
		}
		if (_Sidebar.GetPressedElement() == 4)
		{
			_SelectedColor = sf::Color(0, 255, 0);
		}
		if (_Sidebar.GetPressedElement() == 5)
		{
			_SelectedColor = sf::Color(0, 0, 0);
		}
	}
}

void Tab::UpdateTextboxes()
{
	for (unsigned int c = 0; c < _Textboxes.size(); c++)
	{
		_Textboxes[c]->Update();
	}
}

void Tab::Render()
{
	if (_IsVisible == false)
	{
		return;
	}

	/* Render Background */
	_MainWindow->draw(_BackgroundSprite);

	/* Draw the whole vector to the screen */
	for (unsigned int c = 0; c < _DrawingStack.size(); c++)
	{
		for (unsigned int i = 0; i < _DrawingStack[c].size(); i++)
		{
			_MainWindow->draw(*_DrawingStack[c][i]);
		}
	}

	/* Draw all the the circle in the CurrentDrawing vector */
	for (unsigned int c = 0; c < _CurrentDrawing.size(); c++)
	{
		_MainWindow->draw(*_CurrentDrawing[c]);
	}

	/* Render the text */
	for (unsigned int c = 0; c < _Textboxes.size(); c++)
	{
		_Textboxes[c]->Render();
	}

	/* Render sidebar */
	_Sidebar.Render();
}

void Tab::OnResizeEvent()
{
	float Factor = _MainWindow->getSize().y / 1080.0f;
	_Sidebar.SetScale(sf::Vector2f(Factor, Factor));
}

void Tab::OnTextEnteredEvent(char Input)
{
	for (unsigned int c = 0; c < _Textboxes.size(); c++)
	{
		_Textboxes[c]->OnTextEntered(Input);
	}
}

void Tab::SaveToFile(std::string FileName)
{
	/* Write every drawing point to file */
	std::fstream write;
	write.open(FileName.c_str(), std::ios::out | std::ios::app);
	for (unsigned int c = 0; c < _DrawingStack.size(); c++)
	{
		for (unsigned int i = 0; i < _DrawingStack[c].size(); i++)
		{
			write << _DrawingStack[c][i]->getPosition().x << "/" << _DrawingStack[c][i]->getPosition().y << "/" << _DrawingStack[c][i]->getRadius() << "/";
			if (_DrawingStack[c][i]->getFillColor() == sf::Color(255, 0, 0))
			{
				write << "1" << std::endl;
			}
			if (_DrawingStack[c][i]->getFillColor() == sf::Color(0, 255, 0))
			{
				write << "2" << std::endl;
			}
			if (_DrawingStack[c][i]->getFillColor() == sf::Color(0, 0, 0))
			{
				write << "3" << std::endl;
			}
		}
	}

	/* Now save all the text */
	for (unsigned int c = 0; c < _Textboxes.size(); c++)
	{
		write << "T" << "/" << _Textboxes[c]->GetStartPosition().x << "/" << _Textboxes[c]->GetStartPosition().y << "/" << _Textboxes[c]->GetCharacterSize() << "/";
		if (_Textboxes[c]->GetColor() == sf::Color(255, 0, 0))
		{
			write << "1/";
		}
		if (_Textboxes[c]->GetColor() == sf::Color(0, 255, 0))
		{
			write << "2/";
		}
		if (_Textboxes[c]->GetColor() == sf::Color(0, 0, 0))
		{
			write << "3/";
		}

		write << _Textboxes[c]->GetText() << std::endl;

	}

	write.close();
}

void Tab::LoadFromFile(std::string FileName)
{
	/* Read the whole data in one string */
	std::ifstream read(FileName.c_str());
	if (!read)
	{
		return;
	}
	
	std::string File;
	while (read.good())
	{
		File.push_back(read.get());
	}

	std::vector<sf::CircleShape*> FileData; //Push everything in this Vector

	/* Resolve the strng */
	while (File.find('\n') != std::string::npos)
	{
		/* Copy the File string */
		std::string CpyFile = File;

		/* Only the first line is needed -> everything else should be deleted */
		CpyFile.erase(CpyFile.begin() + CpyFile.find('\n'), CpyFile.end());

		/* If the line holds the information for text exit here */
		if (CpyFile.find("T/") != std::string::npos)
		{
			break;
		}

		/* The information for the current drawing point is in this line */
		std::string XPosition = CpyFile;	//The first number is the X-Position
		std::string YPosition = CpyFile;	//The second number is the Y-Position
		std::string Radius = CpyFile;		//The third number is the Radius
		std::string Color = CpyFile;		//The fourth number is the color

		XPosition.erase(XPosition.begin() + XPosition.find('/'), XPosition.end()); //Delete everything which is not the first number

		/* Get YPosition */
		YPosition.erase(YPosition.begin(), YPosition.begin() + YPosition.find('/') + 1);
		YPosition.erase(YPosition.begin() + YPosition.find('/'), YPosition.end());

		/* Get Radius */
		Radius.erase(Radius.begin(), Radius.begin() + Radius.find('/') + 1);
		Radius.erase(Radius.begin(), Radius.begin() + Radius.find('/') + 1);
		Radius.erase(Radius.begin() + Radius.find('/'), Radius.end());

		/* Get Color */
		Color.erase(Color.begin(), Color.begin() + Color.find('/') + 1);
		Color.erase(Color.begin(), Color.begin() + Color.find('/') + 1);
		Color.erase(Color.begin(), Color.begin() + Color.find('/') + 1);

		//std::cout << XPosition << "/" << YPosition << "/" << Radius << "/" << Color << std::endl; //Debug output

		/* Convert to needed types */
		sf::Color DrawingColor;
		float XPositionV = static_cast<float>(atof(XPosition.c_str()));
		float YPositionV = static_cast<float>(atof(YPosition.c_str()));
		float RadiusV = static_cast<float>(atof(Radius.c_str()));
		if (atoi(Color.c_str()) == 1)
		{
			DrawingColor = sf::Color(255, 0, 0);
		}
		if (atoi(Color.c_str()) == 2)
		{
			DrawingColor = sf::Color(0, 255, 0);
		}
		if (atoi(Color.c_str()) == 3)
		{
			DrawingColor = sf::Color(0, 0, 0);
		}

		FileData.push_back(new sf::CircleShape);
		FileData[FileData.size() - 1]->setFillColor(DrawingColor);
		FileData[FileData.size() - 1]->setPosition(sf::Vector2f(XPositionV, YPositionV));
		FileData[FileData.size() - 1]->setRadius(RadiusV);
		
		File.erase(File.begin(), File.begin() + File.find('\n') + 1); //Delete current line of the file
	}
	_DrawingStack.push_back(FileData);

	File.erase(File.begin(), File.begin() + File.find("T/"));

	/* Now resolve for Textboxes */
	while (File.find("T/") != std::string::npos)
	{
		std::cout << "Searching..." << std::endl;
		std::string CpyFile = File;
		CpyFile.erase(CpyFile.begin() + CpyFile.find('\n'), CpyFile.end()); 
		CpyFile.erase(CpyFile.begin(), CpyFile.begin() + 2);//Erase T/ the start of the line

		/* Now get the X and Y Position of the Textbox */
		std::string XPosition = CpyFile;
		std::string YPosition = CpyFile;

		/* Get XPosition */
		XPosition.erase(XPosition.begin() + XPosition.find('/'), XPosition.end());
		/* Get YPosition */
		YPosition.erase(YPosition.begin(), YPosition.begin() + YPosition.find('/') + 1);
		YPosition.erase(YPosition.begin() + YPosition.find('/'), YPosition.end());

		float XPos = static_cast<float>(atof(XPosition.c_str()));
		float YPos = static_cast<float>(atof(YPosition.c_str()));
		std::cout << XPos << "/" << YPos << std::endl;

		/* Get Character size */
		std::string CharacterSize = CpyFile;
		CharacterSize.erase(CharacterSize.begin(), CharacterSize.begin() + CharacterSize.find('/') + 1);
		CharacterSize.erase(CharacterSize.begin(), CharacterSize.begin() + CharacterSize.find('/') + 1);
		CharacterSize.erase(CharacterSize.begin() + CharacterSize.find('/'), CharacterSize.end());

		int CharacterS = atoi(CharacterSize.c_str());
		std::cout << CharacterS << std::endl;

		/* Get Color */
		std::string Color = CpyFile;
		Color.erase(Color.begin(), Color.begin() + Color.find('/') + 1);
		Color.erase(Color.begin(), Color.begin() + Color.find('/') + 1);
		Color.erase(Color.begin(), Color.begin() + Color.find('/') + 1);
		Color.erase(Color.begin() + Color.find('/'), Color.end());

		sf::Color DrawingColor;
		if (atoi(Color.c_str()) == 1)
		{
			DrawingColor = sf::Color(255, 0, 0);
		}
		if (atoi(Color.c_str()) == 2)
		{
			DrawingColor = sf::Color(0, 255, 0);
		}
		if (atoi(Color.c_str()) == 3)
		{
			DrawingColor = sf::Color(0, 0, 0);
		}
		std::cout << atoi(Color.c_str()) << std::endl;
	
		/* Get Text */
		std::string Text = CpyFile;
		Text.erase(Text.begin(), Text.begin() + Text.find('/') + 1);
		Text.erase(Text.begin(), Text.begin() + Text.find('/') + 1);
		Text.erase(Text.begin(), Text.begin() + Text.find('/') + 1);
		Text.erase(Text.begin(), Text.begin() + Text.find('/') + 1);
		std::cout << Text << std::endl;

		_Textboxes.push_back(new Textbox);
		_Textboxes[_Textboxes.size() - 1]->Create(_MainWindow, sf::Vector2f(XPos, YPos), CharacterS, DrawingColor);
		_Textboxes[_Textboxes.size() - 1]->SetText(Text);

		File.erase(File.begin(), File.begin() + File.find("\n") + 1);
	}
}