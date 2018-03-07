#include <iostream>
#include <string>
/// C++-standard header file name  
//#include <experimental/filesystem> 
/// Microsoft-specific implementation header file name  
//#include <filesystem> 
#include <Windows.h>
#include <vector>
#include <iostream>
#include <string>
#include "MainMenuState.h"
#include "GameState.h"
#include "EditorState.h"

///funkcja zapisuje do wektora wszystkie nazwy plikow z podanego folderu
std::vector<std::string> get_all_files_names_within_folder(std::string folder)
{
	std::vector<std::string> names;
	std::string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}

	for (int i = 0; i < names.size(); ++i)
	{
		if (names[i].find("Unit") != std::string::npos)
		{
			names.erase(names.begin() + i);
			--i;
		}
		else
		{
			names[i].erase(names[i].length() - 4);
		}
	}
	return names;
}

MainMenuState::MainMenuState(GameEngine & game)
{
	this->game = &game;

	font.loadFromFile("fonts/Aller_Bd.ttf");

	std::string path = "maps/";

	int x = 50, y = 50;
	
	std::vector<std::string> pathnames = get_all_files_names_within_folder("maps");
	
	for (int i = 0; i < pathnames.size(); ++i)
	{
		sf::Text text(pathnames[i], font, 30);
		text.setPosition(x, y);
		y += 50;
		listOfMaps.push_back(text);
	}

	activeBox.setFillColor(sf::Color::Transparent);
	activeBox.setOutlineColor(sf::Color(192, 192, 192));
	activeBox.setOutlineThickness(3.0f);


	sf::Vector2f position(game.screen.width/2, 50);
	sf::Vector2f size(80, 45);

	sf::Text text("Play", font, 30);
	text.setPosition(position);
	playButton = Button(sf::RectangleShape(size), text);
	position.x -= 10;
	playButton.buttonRectangle.setPosition(position);


	position = sf::Vector2f(game.screen.width / 2, 110);
	size = sf::Vector2f(150, 45);
	text = sf::Text("New Map", font, 30);
	text.setPosition(position);
	editorButton = Button(sf::RectangleShape(size), text);
	position.x -= 10;
	editorButton.buttonRectangle.setPosition(position);
}

void MainMenuState::Update()
{
	mousePosition = sf::Mouse::getPosition(game->window);

	sf::Event event;
	while (game->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			game->window.close();

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.key.code == sf::Mouse::Left)
			{
				for (int i = 0; i < listOfMaps.size(); ++i)
				{
					// jesli kliknal na nazwe mapy
					if (listOfMaps[i].getGlobalBounds().contains((sf::Vector2f)mousePosition))
					{
						if (activePath == listOfMaps[i].getString())
						{
							game->mapName = activePath;
							game->ChangeState(new GameState(*game));
							return;
						}
						activePath = listOfMaps[i].getString();
						activeBox.setPosition(listOfMaps[i].getPosition().x, listOfMaps[i].getPosition().y + 3);
						activeBox.setSize(sf::Vector2f(listOfMaps[i].getGlobalBounds().width, listOfMaps[i].getGlobalBounds().height + 8));
					}

					// jesli kliknal w play
					if (playButton.buttonRectangle.getGlobalBounds().contains((sf::Vector2f)mousePosition))
					{
						if (activePath != "")
						{
							game->mapName = activePath;
							game->ChangeState(new GameState(*game));
							return;
						}
					}

					// jesli kliknal w nowa mape
					if (editorButton.buttonRectangle.getGlobalBounds().contains((sf::Vector2f)mousePosition))
					{
						game->ChangeState(new EditorState(*game));
						return;
					}
				}
			}
		}
	}
}

void MainMenuState::Draw()
{
	game->window.clear();

	for (int i = 0; i < listOfMaps.size(); ++i)
		game->window.draw(listOfMaps[i]);

	game->window.draw(playButton.buttonRectangle);
	game->window.draw(playButton.buttonText);

	game->window.draw(editorButton.buttonRectangle);
	game->window.draw(editorButton.buttonText);

	game->window.draw(activeBox);
}
