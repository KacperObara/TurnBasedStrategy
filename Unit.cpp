#include <fstream>
#include "Unit.h"
#include "GameState.h"
#include "TilesetManager.h"

void Unit::Move(Tile *tile)
{
	this->tile = tile;
	sprite.setPosition(tile->sprite.getPosition());
	this->moved = true;
}

std::ostream& operator<<(std::ostream& file, const Unit& unit)
{
	// write out individual members of unit with an end of line between each one
	file << unit.name << "\n";
	file << unit.type << "\n";
	file << unit.armorType << "\n";

	file << unit.maxHP << "\n";
	file << unit.movementPoints << "\n";

	file << unit.AttGNA << "\n";
	file << unit.AttGL << "\n";
	file << unit.AttGH << "\n";

	file << unit.AttNNA << "\n";
	file << unit.AttNL << "\n";
	file << unit.AttNH << "\n";

	file << unit.AttANA << "\n";
	file << unit.AttAL << "\n";
	file << unit.AttAH << "\n";

	file << unit.DefG << "\n";
	file << unit.DefN << "\n";
	file << unit.DefA;
	return file;
}

std::istream& operator>>(std::istream& file, Unit& unit)
{
	int type = NULL;
	int armorType = NULL;
	// read in individual members of unit
	file >> unit.name >> type >> armorType >> unit.maxHP >> unit.movementPoints
		 >> unit.AttGNA >> unit.AttGL >> unit.AttGH >> unit.AttNNA >> unit.AttNL >> unit.AttNH
		 >> unit.AttANA >> unit.AttAL >> unit.AttAH >> unit.DefG >> unit.DefN >> unit.DefA;

	unit.HP = unit.maxHP;
	unit.type = (Type)type;
	unit.armorType = (ArmorType)armorType;
	unit.sprite = unit.gameState->tilesetManager.getTile(unit.name, 0).sprite;

	return file;
}