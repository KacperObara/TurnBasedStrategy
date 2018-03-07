#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <vector>
#include "State.h"
#include "TilesetManager.h"

class GSMouseManager;
class Unit;
class GameMap;
class UnitManager;
class FactionManager;
class GameGui;

/**
Klasa odpowiadajaca za wszystko zwiazane z rozgrywka. To tu wykonuje sie glowna petla programu,
gdy uzytkownik jest w trakcie gry. Rowniez tutaj inicjalizowane sa obiekty klas pomocniczych.
*/

class GameState :public State
{
    public:
        GameState(GameEngine &game);

        void Update();
        void Draw();

		TilesetManager tilesetManager;
		void Load_textures();

		void EndTurn();

		GSMouseManager *mouseManager;
		GameMap *gameMap;
		UnitManager *unitManager;
		FactionManager *factionManager;
		GameGui *gameGui;
		
    protected:
    private:

		~GameState()
		{
			delete mouseManager;
			delete unitManager;
			delete factionManager;
		}
};

#endif // GAMESTATE_H
