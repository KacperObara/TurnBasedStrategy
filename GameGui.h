#pragma once
#include "Unit.h"

class TilesetManager;
class GameState;
class GSMouseManager;
/**
Zajmuje sie wyswietlaniem GUI gry.
*/
class GameGui
{
public:
	static GameGui& Object(GameState *gameState)
	{
		static GameGui instance(gameState);
		return instance;
	}

	GSMouseManager *mouseManager;
	TilesetManager *tilesetManager;

	sf::RenderWindow *window;
	sf::VideoMode *screen;

	sf::Font font;
	sf::Text unitName;
	sf::Text unitHP;

	sf::Vector2i position;
	sf::Sprite background;
	Unit activeUnit;
	sf::Sprite endTurnButton;

	sf::IntRect GetEndTurnRect();

	void Update(sf::Event &event);
	void Draw();

	void UpdateText();

	//void ChangeActiveUnit();

	GameGui(GameGui const&) = delete;		// Don't Implement
	void operator=(GameGui const&) = delete;  // Don't Implement

private:
	GameGui() {}
	GameGui(GameState *gameState);

	~GameGui()
	{
		delete mouseManager;
		//delete tilesetManager;
		//delete window;
		//delete screen;
	}
};

