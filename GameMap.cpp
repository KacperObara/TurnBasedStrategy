#include <set>
#include <fstream>
#include "GameMap.h"
#include "GameState.h"
#include "TilesetManager.h"
#include "Tile.hpp"
#include "Unit.h"
#include "UnitManager.h"

void GameMap::LoadMap()
{
	std::ifstream mapFile;
	std::string mapName = "maps/";
	mapName += gameState->game->mapName;
	mapName += ".txt";
	mapFile.open(mapName);
	if (mapFile.good() == false)
		exit(-5);
	
	// load map tiles from file
	std::string line = "";
	int lineNumber = 1;
	int x, y, id;
	while (getline(mapFile, line))
	{
		switch (lineNumber) 
		{
			case 1: id = atoi(line.c_str());		break;
			case 2: x = atoi(line.c_str());			break;
			case 3: y = atoi(line.c_str());			break;
		}
		if (lineNumber % 3 == 0)
		{
			lineNumber = 0;
			mapTiles.push_back(tilesetManager->getTile("Map", id));
			mapTiles[mapTiles.size() - 1].sprite.setPosition(x, y);
		}
		++lineNumber;
	}
	mapFile.close();

	// choosing bordering tiles
	for (int i = 0; i < mapTiles.size(); ++i)
	{
		mapTiles[i].leftTile = nullptr;
		mapTiles[i].rightTile = nullptr;
		mapTiles[i].upTile = nullptr;
		mapTiles[i].downTile = nullptr;

		sf::Vector2f positionLeft = mapTiles[i].sprite.getPosition();
		sf::Vector2f positionRight = mapTiles[i].sprite.getPosition();
		sf::Vector2f positionUp = mapTiles[i].sprite.getPosition();
		sf::Vector2f positionDown = mapTiles[i].sprite.getPosition();
		positionUp.y -= 50;
		positionDown.y += 50;
		positionLeft.x -= 50;
		positionRight.x += 50;
		for (int j = 0; j < mapTiles.size(); ++j)
		{
			if (mapTiles[j].sprite.getPosition() == positionUp)
			{
				mapTiles[i].upTile = &mapTiles[j];
			}
			if (mapTiles[j].sprite.getPosition() == positionDown)
			{
				mapTiles[i].downTile = &mapTiles[j];
			}
			if (mapTiles[j].sprite.getPosition() == positionLeft)
			{
				mapTiles[i].leftTile = &mapTiles[j];
			}
			if (mapTiles[j].sprite.getPosition() == positionRight)
			{
				mapTiles[i].rightTile = &mapTiles[j];
			}
		}
	}
}
///Funkcja oblicza, gdzie zaznaczona jednostka moze sie poruszyc 
void GameMap::CalculateAvailableMovement(Unit *unit)
{ 

	CalculateMovementTiles(unit->tile, unit->movementPoints);
	
	for (int i = 0; i < movementTiles.size(); ++i)
	{
		for (int j = 0; j < movementTiles.size(); ++j)
		{
			if (i == j)
				continue;
			
			if (movementTiles[i]->sprite.getPosition() == movementTiles[j]->sprite.getPosition())
			{
				movementTiles.erase(movementTiles.begin() + j);
				--j;
			}
		}
		if (unit->sprite.getPosition() == movementTiles[i]->sprite.getPosition())
		{
			movementTiles.erase(movementTiles.begin() + i);
			--i;
		}
	}

	if (unit->moved == true)
	{
		for (int i = 0; i < movementTiles.size(); ++i)
		{
			sf::Sprite sprite = gameState->tilesetManager.getTile("Mouse", 3).sprite;
			sprite.setPosition(movementTiles[i]->sprite.getPosition());
			movementTiles[i]->sprite = sprite;
		}
	}

}

void GameMap::CalculateMovementTiles(Tile *tile, int movementPoints)
{
	if (movementPoints < 0)
		return;
	if (tile->terrain == Water)
		return;

	sf::Sprite sprite = gameState->tilesetManager.getTile("Mouse", 1).sprite;
	sprite.setPosition(tile->sprite.getPosition());
	movementTiles.push_back(new Tile(sprite));

	if (tile->leftTile != nullptr)
		CalculateMovementTiles(tile->leftTile, (movementPoints - tile->leftTile->moveCost));
	if (tile->rightTile != nullptr)
		CalculateMovementTiles(tile->rightTile, (movementPoints - tile->rightTile->moveCost));
	if (tile->upTile != nullptr)
		CalculateMovementTiles(tile->upTile, (movementPoints - tile->upTile->moveCost));
	if (tile->downTile != nullptr)
		CalculateMovementTiles(tile->downTile, (movementPoints - tile->downTile->moveCost));
}

void GameMap::CheckBorderingEnemies(Unit *unit)
{
	borderEnemyTiles.clear();

	Tile *tile;// = new Tile(tilesetManager->getTile("Mouse", 2).sprite);

	sf::Vector2f position;
	Unit *enemyUnit;
	// if enemy is at the border with unit, it will show red rectangle
	if (unit->tile->leftTile != nullptr)
	{
		position = unit->tile->leftTile->sprite.getPosition();
		enemyUnit = gameState->unitManager->FindByPosition(position);
		if (enemyUnit != nullptr && enemyUnit->faction != unit->faction)
		{
			tile = new Tile(tilesetManager->getTile("Mouse", 2).sprite);
			tile->sprite.setPosition(unit->tile->leftTile->sprite.getPosition());
			borderEnemyTiles.push_back(tile);
		}
	}

	if (unit->tile->rightTile != nullptr)
	{
		position = unit->tile->rightTile->sprite.getPosition();
		enemyUnit = gameState->unitManager->FindByPosition(position);
		if (enemyUnit != nullptr && enemyUnit->faction != unit->faction)
		{
			tile = new Tile(tilesetManager->getTile("Mouse", 2).sprite);
			tile->sprite.setPosition(unit->tile->rightTile->sprite.getPosition());
			borderEnemyTiles.push_back(tile);
		}
	}

	if (unit->tile->upTile != nullptr)
	{
		position = unit->tile->upTile->sprite.getPosition();
		enemyUnit = gameState->unitManager->FindByPosition(position);
		if (enemyUnit != nullptr && enemyUnit->faction != unit->faction)
		{
			tile = new Tile(tilesetManager->getTile("Mouse", 2).sprite);
			tile->sprite.setPosition(unit->tile->upTile->sprite.getPosition());
			borderEnemyTiles.push_back(tile);
		}
	}

	if (unit->tile->downTile != nullptr)
	{
		position = unit->tile->downTile->sprite.getPosition();
		enemyUnit = gameState->unitManager->FindByPosition(position);
		if (enemyUnit != nullptr && enemyUnit->faction != unit->faction)
		{
			tile = new Tile(tilesetManager->getTile("Mouse", 2).sprite);
			tile->sprite.setPosition(unit->tile->downTile->sprite.getPosition());
			borderEnemyTiles.push_back(tile);
		}
	}
}

bool GameMap::FindBorderEnemy(sf::Vector2f position)
{
	for (int i = 0; i < borderEnemyTiles.size(); ++i)
	{
		if (borderEnemyTiles[i]->sprite.getPosition() == position)
			return true;
	}
	return false;
}