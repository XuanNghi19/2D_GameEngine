#include "Map.h"
#include "Game.h"
#include <fstream>
#include <stdio.h>

Map::Map()
{
	
}

Map::~Map()
{
	
}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	for (int y = 0; y < sizeY; y++)
	{
		mapFile.ignore();

		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);
			std::cout << tile << " ";
			Game::AddTile(atoi(&tile), x * 32, y * 32);
			mapFile.ignore();
		}
		std::cout << std::endl;
	}

	mapFile.close();
}
