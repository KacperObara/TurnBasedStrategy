#pragma once
#include "GameState.h"
#include "TilesetManager.h"

class Tile;

/**
Odpowiada za ladowanie mapy z pliku, wyliczanie pozycji sasiadujacych pol, 
oraz obliczanie dostepnych pol dla jednostek w trakcie ich poruszania sie i atakowania.
*/

class GameMap
{
public:
	GameState *gameState;
	TilesetManager *tilesetManager;
	GameMap(GameState &gameState, TilesetManager &tilesetManager)
	{
		this->gameState = &gameState;
		this->tilesetManager = &tilesetManager;
	}

	std::vector <Tile> mapTiles; // tiles that are drawn on the screen
	std::vector <Tile*> movementTiles; // available tiles for active unit to move
	std::vector <Tile*> borderEnemyTiles; // red rectangle, when bordering with enemy
	bool FindBorderEnemy(sf::Vector2f position);

	void LoadMap();
	void CalculateAvailableMovement(Unit *unit);
	void CheckBorderingEnemies(Unit *unit);

private:
	void CalculateMovementTiles(Tile *tile, int movementPoints);

	~GameMap()
	{
		delete tilesetManager;

		for (std::vector< Tile* >::iterator it = movementTiles.begin(); it != movementTiles.end(); ++it)
		{
			delete (*it);
		}
		movementTiles.clear();

		for (std::vector< Tile* >::iterator it = borderEnemyTiles.begin(); it != borderEnemyTiles.end(); ++it)
		{
			delete (*it);
		}
		borderEnemyTiles.clear();
	}
};

