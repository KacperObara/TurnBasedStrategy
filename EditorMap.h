#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "EditorGui.h"
#include "Tile.hpp"

class EditorState;
/**
Odpowiada za zapisywanie stworzonej mapy do pliku.
*/
class EditorMap
{
public:
	static EditorMap& Object(EditorState *editorState)
	{
		static EditorMap instance(editorState);
		return instance;
	}

	std::vector <EditorTile> editorTiles;
	std::vector <EditorUnit> editorUnits;

	void SaveAndQuit();
	std::string ChooseName();

	EditorState *editorState;
	sf::RenderWindow *window;

	EditorMap(EditorMap const&) = delete;		// Don't Implement
	void operator=(EditorMap const&) = delete;  // Don't Implement

private:
	EditorMap() {}
	EditorMap(EditorState *editorState);

	~EditorMap()
	{
		//delete editorState;
		//delete window;
	}
};

