#pragma once
#include "SDL.h"
#include <string>
#include <vector>
#include "GraphicBody.h"
#include "Tile.h"
class Tilemap
{
public:
	Tilemap(SDL_Renderer* renderer, int width, int height, int tileWidth, int tileHeight, const char* path
		, std::string ground, std::string barrier);
	~Tilemap();

	void create(SDL_Renderer* renderer);
	void draw(SDL_Renderer* renderer);

private:
	int _width;
	int _height;
	SDL_Point _tileSize;
	SDL_Texture* _tilemapTexture;

	std::vector<Tile*> _tiles;
	std::vector<int> _ground;
	std::vector<int> _barrier;
};

