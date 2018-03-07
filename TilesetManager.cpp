#include <fstream>
#include <sstream>
#include "TilesetManager.h"

void TilesetManager::loadTexture(const std::string name, const std::string filename)
{
	sf::Texture texture;
	texture.loadFromFile(filename);
	Tileset tileset(texture);

	this->tilesets[name] = tileset; // Add texture to the list of textures

	SliceTiles(name);
}

Tile &TilesetManager::getTile(const std::string tilesetName, const int ID)
{
	return this->tilesets.at(tilesetName).tiles[ID];
}

sf::Texture &TilesetManager::getTexture(const std::string tilesetName)
{
	return this->tilesets.at(tilesetName).texture;
}

int TilesetManager::getSize(const std::string tilesetName)
{
	return this->tilesets.at(tilesetName).tiles.size();
}


void TilesetManager::SliceTiles(std::string textureName)
{
	unsigned int xSize = getTexture(textureName).getSize().x;
	unsigned int ySize = getTexture(textureName).getSize().y;

	for (unsigned int y = 0; y < ySize; y += tileSize)
	{
		for (unsigned int x = 0; x < xSize; x += tileSize)
		{
			sf::IntRect position(x, y, tileSize, tileSize); // mozna skrocic kod z 3 do jednej linijki, ale ladnie widac
			sf::Sprite sprite(getTexture(textureName), position);
			tilesets.at(textureName).tiles.push_back(Tile(sprite));
		}
	}

	std::stringstream path;
	path << "config/tiles/" << textureName << ".txt";

	std::ifstream file;
	file.open(path.str());
	if (file.good() == false)
	{
		file.close();
		file.clear();
		return;
	}
		
	std::string line;
	int lineNumber = -6;
	int i = 0;
	while (getline(file, line))
	{
		if (i >= getSize(textureName))
			break;

		switch (lineNumber)
		{
			case 1: tilesets.at(textureName).tiles[i].terrain = static_cast<Terrain>(atoi(line.c_str())); break; // cast string to int and then int to enum
			case 2: tilesets.at(textureName).tiles[i].moveCost = atoi(line.c_str()); break;
		}
		if (lineNumber % 3 == 0 && lineNumber > 0)
		{
			lineNumber = 0;
			++i;
		}
		++lineNumber;
	}
	file.close();
	file.clear();
}


std::string TilesetManager::getNextTileset(const std::string texture)
{
	std::map<std::string, Tileset>::iterator it;

	for (it = tilesets.begin(); it != tilesets.end(); ++it)
	{
		if (it->first == texture)
		{
			++it;
			return it->first;
		}
	}
	it = tilesets.begin();
	return it->first;
}