#pragma once
#include "State.h"
#include "TilesetManager.h"

class GameEngine;
class EditorMap;
class EditorGui;
class ESMouseManager;
/**
Posiada podobna funkcjonalnosc jak GameState, ale odpowiada za wszystko zwiazane z edytorem.
*/
class EditorState :public State
{
public:
	EditorState(GameEngine &game);
	
	void Update();
	void Draw();

	void LoadTextures();
	void LoadUnits();

	TilesetManager tilesetManager;
	EditorMap *editorMap;
	EditorGui *editorGui;
	ESMouseManager *mouseManager;

	sf::VertexArray boundaryLines;

};

