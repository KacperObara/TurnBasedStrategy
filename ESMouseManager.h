#pragma once
#include <SFML/Graphics.hpp>
#include "EditorGui.h"

class Tile;
class EditorState;
class EditorMap;
/**
Odpowiada za wszystko zwiazane z myszka w edytorze map.
*/
class ESMouseManager
{
public:
	static ESMouseManager& Object(EditorState *editorState)
	{
		static ESMouseManager instance(editorState);
		return instance;
	}

	void Update(sf::Event event);
	void Draw();

	sf::Vector2i mousePosition;
	sf::Sprite sprite;

	EditorTile selectedTile; // when mouse clicked on hovering
	EditorUnit selectedUnit;

	void MouseHover();
	void LeftMouseClick();
	void RightMouseClick();

	EditorState *editorState;
	EditorGui *editorGui;
	EditorMap *editorMap;

	ESMouseManager(ESMouseManager const&) = delete;		// Don't Implement
	void operator=(ESMouseManager const&) = delete;  // Don't Implement

private:
	ESMouseManager() {}
	ESMouseManager(EditorState *editorState);

	~ESMouseManager()
	{
		delete editorState;
	}
};

