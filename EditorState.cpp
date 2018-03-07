#include "EditorState.h"
#include "EditorMap.h"
#include "EditorGui.h"
#include "ESMouseManager.h"

EditorState::EditorState(GameEngine &game)
{
	this->game = &game;
	
	LoadTextures();

	editorMap = &editorMap->Object(this);
	editorGui = &editorGui->Object(this);

	LoadUnits();
	
	mouseManager = &mouseManager->Object(this);

	boundaryLines = sf::VertexArray(sf::LinesStrip, 3);

	boundaryLines[0].position = sf::Vector2f(0, 4000);
	boundaryLines[1].position = sf::Vector2f(0, 0);
	boundaryLines[2].position = sf::Vector2f(5000, 0);
}

void EditorState::Update()
{
	sf::Event event;
	while (game->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			editorMap->SaveAndQuit();

		// tab zmienia kolor stawianych jednostek
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Tab)
			{
				if (editorGui->activeFaction == Blue)
					editorGui->activeFaction = Red;

				else if (editorGui->activeFaction == Red)
					editorGui->activeFaction = Blue;
			}
		}
	}
	// przesuwanie mapy strzalkami
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		game->camera.move(sf::Vector2f(-3, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		game->camera.move(sf::Vector2f(3, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		game->camera.move(sf::Vector2f(0, -3));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		game->camera.move(sf::Vector2f(0, 3));
	}

	mouseManager->Update(event);
	editorGui->Update();
}

void EditorState::Draw()
{
	game->window.clear();


	game->window.draw(boundaryLines);
	
	mouseManager->Draw();
	
	// rysowane sa namalowane plytki
	for (int i = 0; i < editorMap->editorTiles.size(); ++i)
	{
		game->window.draw(editorMap->editorTiles[i].sprite);
	}

	// rysowane sa namalowane jednostki
	for (int i = 0; i < editorMap->editorUnits.size(); ++i)
	{
		if (editorMap->editorUnits[i].faction == Red)
			editorMap->editorUnits[i].sprite.setColor(sf::Color(255, 150, 150));

		else if (editorMap->editorUnits[i].faction == Blue)
			editorMap->editorUnits[i].sprite.setColor(sf::Color(150, 150, 255));

		game->window.draw(editorMap->editorUnits[i].sprite);
	}

	editorGui->Draw();
}

void EditorState::LoadTextures()
{
	tilesetManager.loadTexture("Map", "images/tilesets/Map.png");
	tilesetManager.loadTexture("Mouse", "images/Mouse.png");
	tilesetManager.loadTexture("Rifleman", "images/units/Rifleman.png");
	tilesetManager.loadTexture("PpanzInf", "images/units/PpanzInf.png");
	tilesetManager.loadTexture("ArmoredTruck", "images/units/ArmoredTruck.png");
	tilesetManager.loadTexture("Tank", "images/units/Tank.png");

}
void EditorState::LoadUnits()
{
	editorGui->units.push_back(EditorUnit("Rifleman", tilesetManager.getTile("Rifleman", 0).sprite));
	editorGui->units.push_back(EditorUnit("PpanzInf", tilesetManager.getTile("PpanzInf", 0).sprite));
	editorGui->units.push_back(EditorUnit("ArmoredTruck", tilesetManager.getTile("ArmoredTruck", 0).sprite));
	editorGui->units.push_back(EditorUnit("Tank", tilesetManager.getTile("Tank", 0).sprite));
}

