#pragma once
#include <SFML/Graphics.hpp>

enum Terrain { Plains, Forest, Hill, Water };
/**
Klasa przechowujaca wlasciwosci jednej plytki terenu
*/
class Tile
{
public:
	Tile(sf::Sprite sprite)
	{
		this->sprite = sprite;
	}
	sf::Sprite sprite;

	Terrain terrain;
	int moveCost;

	Tile *leftTile;
	Tile *rightTile;
	Tile *upTile;
	Tile *downTile;

	~Tile()
	{
	}
};
