#include <iostream>
#include "FactionManager.h"
#include "Unit.h"
#include "GameState.h"
#include "UnitManager.h"

FactionManager::FactionManager(GameState *gameState)
{
	this->gameState = gameState;
	this->unitManager = gameState->unitManager;
	activeFaction = Red;
}

bool FactionManager::CheckFaction(Faction faction)
{
	if (faction == activeFaction)
		return true;
	return false;
}

void FactionManager::ChangeActiveFaction()
{
	if (activeFaction == Red)
	{
		activeFaction = Blue;
	}
	else if (activeFaction == Blue)
	{
		activeFaction = Red;
	}
}

void FactionManager::Fight(Unit *attacker, Unit *defender)
{
	if (attacker->attacked == true)
		return;
	
	int attack = ChooseDamageType(attacker, defender);
	if (attacker->maxHP <= 0)
	{
		std::cout << "maxHP attackera <= 0\n";
		exit(-1);
	}

	int defense = ChooseDefense(attacker, defender);

	int damage = 0;
	if (attack - defense > 0)
		damage = attack - defense;
	else
		damage = 1;

	std::cout << attack << " " << defense << "\n";
	defender->HP -= damage;

	std::cout << "Defender HP: " << defender->HP << "\n";

	if (defender->HP < 0)
	{
		unitManager->units.erase(std::remove(unitManager->units.begin(), unitManager->units.end(), defender), unitManager->units.end());
	}

	attacker->attacked = true;
}

int FactionManager::ChooseDefense(Unit *attacker, Unit *defender)
{
	if (attacker->type == Ground)
		return defender->DefG;

	else if (attacker->type == Naval)
		return defender->DefN;

	else if (attacker->type == Air)
		return defender->DefA;

	else
	{
		std::cout << "Error in Unit::ChooseDefense\n";
		exit(-1);
	}
}

int FactionManager::ChooseDamageType(Unit *attacker, Unit *defender)
{
	if (attacker->type == Ground)
	{
		if (defender->armorType == NoArmor)
		{
			return attacker->AttGNA;
		}
		if (defender->armorType == Low)
		{
			return attacker->AttGL;
		}
		if (defender->armorType == High)
		{
			return attacker->AttGH;
		}
	}
	else if (attacker->type == Naval)
	{
		if (defender->armorType == NoArmor)
		{
			return attacker->AttNNA;
		}
		if (defender->armorType == Low)
		{
			return attacker->AttNL;
		}
		if (defender->armorType == High)
		{
			return attacker->AttNH;
		}
	}
	else if (attacker->type == Air)
	{
		if (defender->armorType == NoArmor)
		{
			return attacker->AttANA;
		}
		if (defender->armorType == Low)
		{
			return attacker->AttAL;
		}
		if (defender->armorType == High)
		{
			return attacker->AttAH;
		}
	}
	else
	{
		std::cout << "Error in Unit::ChooseDamageType\n";
		exit(-1);
	}
}