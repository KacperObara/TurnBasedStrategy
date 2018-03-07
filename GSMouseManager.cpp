#include <SFML/Graphics.hpp>
#include "GSMouseManager.h"
#include "GameState.h"
#include "GameEngine.h"
#include "Tile.hpp"
#include "Unit.h"
#include "GameMap.h"
#include "UnitManager.h"
#include "GameGui.h"
#include <iostream>

GSMouseManager::GSMouseManager(GameState *gameState)
{
	this->gameState = gameState;
	this->gameMap = this->gameState->gameMap;
	sprite = this->gameState->tilesetManager.getTile("Mouse", 0).sprite;
}


void GSMouseManager::Update(sf::Event &event)
{
	mousePosition = sf::Mouse::getPosition(gameState->game->window);
	mousePosition = (sf::Vector2i)gameState->game->window.mapPixelToCoords(mousePosition);
	MouseHover();

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			LeftMouseClick();
		}
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			RightMouseClick();
		}
	}
}

void GSMouseManager::Draw()
{
	gameState->game->window.draw(sprite);
}

void GSMouseManager::MouseHover()
{
	int x = mousePosition.x;
	int y = mousePosition.y;

	int offset = x % 50;
	x -= offset;

	offset = y % 50;
	y -= offset;

	sprite.setPosition(sf::Vector2f(x, y));


	// zaznaczanie tile
	for (int i = 0; i < gameState->gameMap->mapTiles.size(); ++i)
	{
		if (gameMap->mapTiles[i].sprite.getPosition().x == x && gameState->gameMap->mapTiles[i].sprite.getPosition().y == y)
		{
			hoveringTile = &gameState->gameMap->mapTiles[i];
			return;
		}
	}
	// if here, then mouse is not on tile
	hoveringTile = nullptr;
}

void GSMouseManager::LeftMouseClick()
{
	activeTile = hoveringTile;

	if (activeTile != nullptr)
	{
		Unit *unit = gameState->unitManager->FindByPosition(activeTile->sprite.getPosition());
		if (unit != nullptr)
		{
			if (gameState->factionManager->CheckFaction(unit->faction))
			{
				activeUnit = unit;
				gameMap->movementTiles.clear();
				gameMap->borderEnemyTiles.clear();
				gameMap->CalculateAvailableMovement(activeUnit);
				gameMap->CheckBorderingEnemies(activeUnit);
				return;
			}
		}
		activeUnit = nullptr;
		gameMap->borderEnemyTiles.clear();
		gameMap->movementTiles.clear();
	}
}

void GSMouseManager::RightMouseClick()
{
	if (activeUnit != nullptr && hoveringTile != nullptr)
	{
		for (int i = 0; i < gameMap->movementTiles.size(); ++i)
		{
			if (gameMap->movementTiles[i]->sprite.getPosition() == hoveringTile->sprite.getPosition())
			{
				Unit *unit = gameState->unitManager->FindByPosition(hoveringTile->sprite.getPosition());
				if (unit == nullptr)
				{
					unit = gameState->unitManager->FindByPosition(activeTile->sprite.getPosition());
					if (unit->moved == false)
					{
						unit->Move(hoveringTile);
						gameMap->movementTiles.clear();
						gameMap->borderEnemyTiles.clear();
						activeTile = nullptr;
						activeUnit = nullptr;
					}
					return;
				}
				else if (gameMap->FindBorderEnemy(unit->sprite.getPosition()) == true)
				{
					Unit *attacker = gameState->unitManager->FindByPosition(activeTile->sprite.getPosition());
					Unit *defender = gameState->unitManager->FindByPosition(hoveringTile->sprite.getPosition());
					gameState->factionManager->Fight(attacker, defender);
					return;
				}
			}
			else if (gameMap->FindBorderEnemy(hoveringTile->sprite.getPosition()) == true)
			{
				Unit *attacker = gameState->unitManager->FindByPosition(activeTile->sprite.getPosition());
				Unit *defender = gameState->unitManager->FindByPosition(hoveringTile->sprite.getPosition());
				gameState->factionManager->Fight(attacker, defender);
				return;
			}
		}
	}
}