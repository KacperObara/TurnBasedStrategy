#include "ESMouseManager.h"
#include "EditorState.h"
#include "EditorGui.h"
#include "EditorMap.h"

#define tileSize 50

ESMouseManager::ESMouseManager(EditorState *editorState)
{
	this->editorState = editorState;
	this->editorGui = editorState->editorGui;
	this->editorMap = editorState->editorMap;
}

void ESMouseManager::Update(sf::Event event)
{
	mousePosition = sf::Mouse::getPosition(editorState->game->window);
	mousePosition = (sf::Vector2i)editorState->game->window.mapPixelToCoords(mousePosition);
	MouseHover();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		LeftMouseClick();
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		RightMouseClick();
	}
}

void ESMouseManager::Draw()
{

}

void ESMouseManager::MouseHover()
{
}

void ESMouseManager::LeftMouseClick()
{
	// czy gracz wybieral plytke?
	for (int i = 0; i < editorGui->tileset.size(); ++i)
	{
		if (editorGui->tileset[i].sprite.getGlobalBounds().contains((sf::Vector2f)mousePosition))
		{
			//selectedTile = editorGui->tileset[i];
			selectedTile = editorGui->tileset[i];
			selectedUnit.name = "";
			return;
		}
	}
	// czy gracz wybieral jednostke?
	for (int i = 0; i < editorGui->units.size(); ++i)
	{
		if (editorGui->units[i].sprite.getGlobalBounds().contains((sf::Vector2f)mousePosition))
		{
			selectedTile.sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
			selectedUnit = editorGui->units[i];
			return;
		}
	}

	// czy gracz probowal namalowac zajete pole? jak tak to maluj jednostke jesli to wybral
	int x = mousePosition.x - (mousePosition.x % tileSize);
	int y = mousePosition.y - (mousePosition.y % tileSize);

	for (int i = 0; i < editorMap->editorTiles.size(); ++i)
	{
		if (editorMap->editorTiles[i].sprite.getPosition() == sf::Vector2f(x, y))
		{
			for (int i = 0; i < editorMap->editorUnits.size(); ++i)
			{
				if (editorMap->editorUnits[i].sprite.getPosition() == sf::Vector2f(x, y))
				{
					return;
				}
			}
			if (selectedUnit.name != "")
			{
				selectedUnit.faction = editorGui->activeFaction;
				selectedUnit.sprite.setPosition(x, y);
				editorMap->editorUnits.push_back(selectedUnit);
			}
			return;
		}
	}

	if (x >= 0 && y >= 0)
	{
		if (selectedTile.sprite.getTextureRect() != sf::IntRect(0, 0, 0, 0))
		{
			selectedTile.sprite.setPosition(x, y);
			editorMap->editorTiles.push_back(selectedTile);
		}
	}
}

void ESMouseManager::RightMouseClick()
{
	int x = mousePosition.x - (mousePosition.x % tileSize);
	int y = mousePosition.y - (mousePosition.y % tileSize);

	// czy gracz usuwa pole z jednostka
	for (int i = 0; i < editorMap->editorUnits.size(); ++i)
	{
		if (editorMap->editorUnits[i].sprite.getPosition() == sf::Vector2f(x, y))
		{
			editorMap->editorUnits.erase(editorMap->editorUnits.begin() + i);
			return;
		}
	}

	// czy gracz usuwa pole z plytka
	for (int i = 0; i < editorMap->editorTiles.size(); ++i)
	{
		if (editorMap->editorTiles[i].sprite.getPosition() == sf::Vector2f(x, y))
		{
			editorMap->editorTiles.erase(editorMap->editorTiles.begin() + i);
			return;
		}
	}
}

