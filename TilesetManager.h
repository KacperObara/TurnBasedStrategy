#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.hpp"
/**
Zbior przechowujacy jeden zbior plytek
*/
class Tileset
{
public:
	Tileset(){}
	Tileset(sf::Texture texture)
	{
		this->texture = texture;
	}
	sf::Texture texture;
	std::vector <Tile> tiles; 
};
/**
Klasa, ktora zarzadza wszystkimi teksturami w grze. laduje wszystkie potrzebne tekstury, po czym dzieli je na pojedyncze kafelki.
*/
class TilesetManager
{
public:

	void loadTexture(const std::string name, const std::string filename);

	Tile &getTile(const std::string texture, const int ID);
	sf::Texture &getTexture(const std::string texture);
	int getSize(const std::string texture);

	///Funkcja tnie caly zestaw kafelkow na pojedyncze o wielkosci 50x50 pikseli
	void SliceTiles(std::string tilesetName);

	///Funkcja zwraca nazwe kolejnego zestawu kafelkow, uzywana jest do iterowania po wszystkich teksturach
	std::string getNextTileset(const std::string texture);

	const int tileSize = 50;
private:
	std::map<std::string, Tileset> tilesets; 

};

