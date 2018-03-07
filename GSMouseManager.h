#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"

class Tile;
class GameMap;
class Unit;
/**
Odpowiada za wszystko zwiazane z myszka. Czyli zaznaczanie pol/jednostek, jak rowniez wykonywanie rozkazow prawym przyciskiem myszki.
*/
class GSMouseManager
{
	public:
		GSMouseManager(GameState *gameState);

		void Update(sf::Event &event);
		void Draw();

		sf::Vector2i mousePosition;
		
		sf::Sprite sprite;

		Tile *hoveringTile; // where mouse hover
		Tile *activeTile; // when mouse clicked on hovering

		Unit *activeUnit;

		GameState *gameState;
		GameMap *gameMap;

		void MouseHover();
		void LeftMouseClick();
		void RightMouseClick();

		~GSMouseManager()
		{
			delete activeUnit;
			//delete activeTile;
			//delete hoveringTile;
		}
};

