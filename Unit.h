#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "TilesetManager.h"
#include "GameState.h"
#include "GameMap.h"
#include "FactionManager.h"


class Animation;

enum Type { Ground, Naval, Air };
enum ArmorType { NoArmor, Low, High };
/**
Przechowuje statystyki jednostek, oraz zajmuje sie ich ladowaniem i zapisywaniem do pliku.
*/
class Unit
{
public:
	
	Faction faction;

	Type type;
	ArmorType armorType;


	int maxHP;
	int HP;

	int movementPoints;

	bool moved = false;
	bool attacked = false;
	std::string name;
	sf::Sprite sprite;
	Tile *tile;

	// base/..|Defense/Attack|Ground/Naval/Air|NoArmor/Low/High
	int AttGNA;
	int AttGL;
	int AttGH;

	int AttNNA;
	int AttNL;
	int AttNH;

	int AttANA;
	int AttAL;
	int AttAH;

	int DefG;
	int DefN;
	int DefA;

	GameState *gameState;

	Unit() 
	{
	}
	Unit(GameState *gameState)
	{
		this->gameState = gameState;
	}

	void Move(Tile *tile);



	// Insertion operator 
	///Serializacja pozwalajaca na odczytywanie z pliku calego obiektu naraz
	friend std::ostream& operator<<(std::ostream& file, const Unit& unit); 

	// Extraction operator
	///Serializacja pozwalajaca na zapisywanie do pliku calego obiektu naraz
	friend std::istream& operator>>(std::istream& file, Unit& unit); 

	~Unit()
	{
	}
};
