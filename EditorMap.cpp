#include <fstream>
#include <sstream>
#include "EditorMap.h"
#include "EditorState.h"
#include "GameEngine.h"

EditorMap::EditorMap(EditorState *editorState)
{
	this->editorState = editorState;
	this->window = &editorState->game->window;
}

///Ta funkcja jest cala petla wybierania nazwy dla mapy
std::string EditorMap::ChooseName()
{
	sf::Font font;
	font.loadFromFile("fonts/Aller_Bd.ttf");
	std::string mapName = "";
	sf::Text text(mapName, font, 20);
	text.setPosition(editorState->game->screen.width / 2, editorState->game->screen.height / 2);


	sf::Text instruction("Choose Map's name:", font, 20);

	instruction.setPosition(editorState->game->screen.width / 2, editorState->game->screen.height / 2 - 50);

	sf::FloatRect textRect = instruction.getLocalBounds();
	instruction.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);


	while (true)
	{
		// wysrodkowywanie tekstu wpisywania nazwy mapy
		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);

		text.setString(mapName);

		
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				exit(0);
			}
			if (event.type == sf::Event::KeyPressed)
			{
				// proces wpisywania
				if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z)
				{
					mapName += (char)(event.key.code + 97);
				}
				if (event.key.code == sf::Keyboard::Return)
				{
					return mapName;
				}
				if (event.key.code == sf::Keyboard::BackSpace)
				{
					if (mapName.length() > 0)
					mapName.pop_back();
				}
			}
		}

		window->clear();
		window->draw(instruction);
		window->draw(text);
		window->display();
	}
}

void EditorMap::SaveAndQuit()
{
	sf::VideoMode *screen = &editorState->game->screen;
	sf::View camera(sf::Vector2f(screen->width / 2, screen->height / 2), sf::Vector2f(screen->width, screen->height));
	window->setView(camera);

	std::string mapName = "maps/";
	mapName += ChooseName();
	mapName += ".txt";
	if (mapName == "maps/.txt")
		return;

	// zapisywanie plytek terenu
	std::ofstream tilesFile;
	tilesFile.open(mapName);
	for (int i = 0; i < editorTiles.size(); ++i)
	{
		tilesFile << editorTiles[i].id << "\n";
		tilesFile << editorTiles[i].sprite.getPosition().x << "\n";
		tilesFile << editorTiles[i].sprite.getPosition().y << "\n";
	}
	tilesFile.close();

	// zapisywanie jednostek
	mapName.erase(mapName.length() - 4);
	mapName += "Unit.txt";
	std::ofstream unitsFile;
	unitsFile.open(mapName);
	for (int i = 0; i < editorUnits.size(); ++i)
	{
		unitsFile << editorUnits[i].name << "\n";
		unitsFile << (int)editorUnits[i].faction << "\n";
		unitsFile << editorUnits[i].sprite.getPosition().x << "\n";
		unitsFile << editorUnits[i].sprite.getPosition().y << "\n";
	}
	unitsFile.close();

	exit(-1);
}