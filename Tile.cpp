#include "Tile.h"

Tile::Tile(SDL_Point tilesize, int id, SDL_Point screenpos)
	: ID(id)
{
	tileSize = tilesize;
	screenPos = screenpos;
	int w = 12;
	int h = 8;
	//SDL_QueryTexture(_tex,NULL,NULL,&w,&h);
	int x = 0;
	int y = 0;
	for (int i = 0; i < ID - 1; i++)
	{
		if (y < h)
		{
			if (x < w - 1)
			{
				++x;
			}
			else
			{
				x = 0;
				++y;
			}
		}
	}

	tilePos.x = x*32;
	tilePos.y = y*32;
}

Tile::~Tile()
{
}
