#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class TilesetManager;
class EditorState;

enum Faction {Red, Blue};
/**
Zajmuje sie wyswietlaniem GUI edytora.
*/
class EditorUnit
{
public:
	EditorUnit(){}
	EditorUnit(std::string name, sf::Sprite sprite, Faction faction)
	{
		this->name = name;
		this->sprite = sprite;
		this->faction = faction;
	}
	EditorUnit(std::string name, sf::Sprite sprite)
	{
		this->name = name;
		this->sprite = sprite;
	}
	std::string name;
	sf::Sprite sprite;
	Faction faction;
};

class EditorTile
{
public:
	EditorTile() {}
	EditorTile(int id, sf::Sprite sprite)
	{
		this->id = id;
		this->sprite = sprite;
	}
	int id;
	sf::Sprite sprite;
};

class EditorGui
{
public:
	static EditorGui& Object(EditorState *editorState)
	{
		static EditorGui instance(editorState);
		return instance;
	}

	std::vector <EditorTile> tileset;
	std::string tilesetName;

	std::vector <EditorUnit> units;

	Faction activeFaction;
	/// funkcja najpierw aktualizuje plytki, a nastepnie jednostki
	void Update();
	void Draw();

	EditorState *editorState;
	TilesetManager *tilesetManager;

	EditorGui(EditorGui const&) = delete;		// Don't Implement
	void operator=(EditorGui const&) = delete;  // Don't Implement

private:
	EditorGui() {}
	EditorGui(EditorState *editorState);

	~EditorGui()
	{
		//delete editorState;
		//delete tilesetManager;
	}
};

