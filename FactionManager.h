#pragma once

enum Faction { Red, Blue };

class Unit;
class GameState;
class UnitManager;
/**
Klasa zarzadzajaca turami, oraz wynikiem walki miedzy jednostkami.
*/
class FactionManager
{
public:
	

	Faction activeFaction;

	FactionManager(GameState *gameState);

	GameState *gameState;
	UnitManager *unitManager;

	void ChangeActiveFaction();
	bool CheckFaction(Faction faction);

	void Fight(Unit *attacker, Unit *defender);
	int ChooseDamageType(Unit *attacker, Unit *defender);
	int ChooseDefense(Unit *attacker, Unit *defender);

	~FactionManager()
	{
		delete unitManager;
	}
};

