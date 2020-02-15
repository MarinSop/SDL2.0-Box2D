#include "Tilemap.h"

Tilemap::Tilemap(SDL_Renderer* renderer,int width,int height,int tileWidth,int tileHeight,const char* path
,std::string ground)
	:_width(width),_height(height)
{
	SDL_Surface* surface = IMG_Load(path);
	_tilemapTexture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	_tileSize.x = tileWidth;
	_tileSize.y = tileHeight;
	int result = 0;
	for (int i = 1; i < ground.size();++i)
	{
		int j = ground[i] - '0';
		
		if (j >= 0)
		{
			result = result * 10 + j;
		}
		else
		{
			_ground.push_back(result);
			result = 0;
		}
	}
	_ground.push_back(result);

		std::cout << _ground[0] << std::endl;


}

Tilemap::~Tilemap()
{
}

void Tilemap::create(SDL_Renderer* renderer)
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < _ground.size(); ++i)
	{
		if (y <= _height-1)
		{
			if (x <= _width-1)
			{
				if (_ground[i] > 0)
				{
					SDL_Point screenPos = { x * 32,y * 32 };
					_tiles.push_back(new Tile(_tileSize,_ground[i],screenPos));
				}
				++x;
			}
			else
			{
				x = 0;
				++y;
			}
		}
		//std::cout << "x  i  y  " << x << y << std::endl;
	}


}

void Tilemap::draw(SDL_Renderer* renderer)
{
	for (int i = 0; i < _tiles.size(); i++)
	{
		//_tiles[i]->cout();
		SDL_RenderCopyEx(renderer, _tilemapTexture, _tiles[i]->tilePos, _tiles[i]->screenPos,0,NULL,SDL_FLIP_NONE);
	}
}

