#include <fstream>
#include <sstream>
#include "UnitManager.h"
#include "Unit.h"
#include "GameState.h"
#include "GameMap.h"

UnitManager::UnitManager(GameState *gameState)
{
	this->gameState = gameState;
}

Unit* UnitManager::FindByPosition(sf::Vector2f position)
{
	for (int i = 0; i < units.size(); ++i)
	{
		if (units[i]->sprite.getPosition() == position)
		{
			return units[i];
		}
	}
	return nullptr;
}

void UnitManager::LoadUnit()
{
	std::ifstream unitFile;
	std::string mapName = "maps/";
	mapName += gameState->game->mapName;
	mapName += "Unit.txt";
	unitFile.open(mapName);
	if (unitFile.good() == false)
		exit(-4);

	// load map tiles from file
	std::string line = "";
	int lineNumber = 1;
	int x, y, faction;
	std::string name;
	while (getline(unitFile, line))
	{
		switch (lineNumber)
		{
		case 1: name = line;					break;
		case 2: faction = atoi(line.c_str());	break;
		case 3: x = atoi(line.c_str());			break;
		case 4: y = atoi(line.c_str());			break;
		}
		if (lineNumber % 4 == 0)
		{
			lineNumber = 0;

			Unit *unit = &ReadFromFile(name);
			unit->faction = (Faction)faction;
			unit->sprite.setPosition(x, y);

			for (int i = 0; i < gameState->gameMap->mapTiles.size(); ++i)
			{
				if (unit->sprite.getPosition() == gameState->gameMap->mapTiles[i].sprite.getPosition())
				{
					unit->tile = &gameState->gameMap->mapTiles[i];
					break;
				}
			}
			if (unit->faction == Red)
				unit->sprite.setColor(sf::Color(255, 150, 150));

			else if (unit->faction == Blue)
				unit->sprite.setColor(sf::Color(150, 150, 255));
			units.push_back(unit);
		}
		++lineNumber;
	}
	unitFile.close();
}

void UnitManager::SaveToFile(Unit *unit)
{
	std::stringstream path;
	path << "config/units/" << unit->name << ".txt";
	std::ofstream file(path.str());
	file << *unit; // store the object to file
	file.close();
}

Unit& UnitManager::ReadFromFile(std::string name)
{
	std::stringstream path;
	path << "config/units/" << name << ".txt";
	std::ifstream file(path.str());
	Unit *unit = new Unit(gameState);
	file >> *unit;
	file.close();

	return *unit;
}