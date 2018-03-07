#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Unit;
class GameState;
/**
Wspomaga ladowanie jednostek klasy Unit, oraz wyszukiwanie jednostek na mapie.
*/
class UnitManager
{
public:

	std::vector<Unit*> units;

	UnitManager(GameState *gameState);

	GameState *gameState;

	Unit* FindByPosition(sf::Vector2f position);

	void LoadUnit();

	void SaveToFile(Unit *unit);
	Unit& ReadFromFile(std::string name);

	~UnitManager()
	{
		for (std::vector<Unit *>::iterator it = units.begin(); it != units.end(); ++it)
		{
			delete (*it);
		}
		units.clear();
	}
};

