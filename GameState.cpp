#include <SFML/Graphics.hpp>
#include "GameEngine.h"
#include "GameState.h"
#include "GSMouseManager.h"
#include "Tile.hpp"
#include "GameMap.h"
#include "Unit.h"
#include "UnitManager.h"
#include "FactionManager.h"
#include "GameGui.h"

GameState::GameState(GameEngine &game)
{
    this->game = &game;
	Load_textures();

	gameMap = new GameMap(*this, tilesetManager);
	gameMap->LoadMap();
	
	unitManager = new UnitManager(this);
	unitManager->LoadUnit();

	factionManager = new FactionManager(this);

	mouseManager = new GSMouseManager(this);

	gameGui = &gameGui->Object(this);
}

void GameState::Update()
{
	sf::Event event;
	while (game->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			game->window.close();

		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				EndTurn();
			}
		}

	}
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

	gameGui->Update(event);
}

void GameState::Draw()
{
	game->window.clear();

	for (unsigned int i = 0; i < gameMap->mapTiles.size(); ++i)
		game->window.draw(gameMap->mapTiles[i].sprite);

	for (int i = 0; i < unitManager->units.size(); ++i)
	{
		game->window.draw(unitManager->units[i]->sprite);
	}

	for (int i = 0; i < gameMap->movementTiles.size(); ++i)
		game->window.draw(gameMap->movementTiles[i]->sprite);

	for (int i = 0; i < gameMap->borderEnemyTiles.size(); ++i)
	{
		game->window.draw(gameMap->borderEnemyTiles[i]->sprite);
	}

	mouseManager->Draw();

	gameGui->Draw();
}

void GameState::Load_textures()
{
	tilesetManager.loadTexture("Map", "images/tilesets/Map.png");
	tilesetManager.loadTexture("Mouse", "images/Mouse.png");
	tilesetManager.loadTexture("Rifleman", "images/units/Rifleman.png");
	tilesetManager.loadTexture("PpanzInf", "images/units/PpanzInf.png");
	tilesetManager.loadTexture("ArmoredTruck", "images/units/ArmoredTruck.png");
	tilesetManager.loadTexture("Tank", "images/units/Tank.png");
}

void GameState::EndTurn()
{
	if (gameGui->GetEndTurnRect().contains(mouseManager->mousePosition))
	{
		factionManager->ChangeActiveFaction();
		for (int i = 0; i < unitManager->units.size(); ++i)
		{
			unitManager->units[i]->moved = false;
			unitManager->units[i]->attacked = false;
		}
		gameMap->movementTiles.clear();
		gameMap->borderEnemyTiles.clear();
		gameGui->activeUnit.sprite.setColor(sf::Color::Transparent);
	}
}