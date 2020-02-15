#include "Tile.h"

Tile::Tile(SDL_Point tilesize, int id, SDL_Point screenpos)
	: ID(id)
{
	tilePos = new SDL_Rect();
	screenPos = new SDL_Rect();
	tilePos->w = tilesize.x;
	tilePos->h = tilesize.y;
	screenPos->w = tilesize.x;
	screenPos->h = tilesize.y;
	screenPos->x = screenpos.x;
	screenPos->y = screenpos.y;
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

	tilePos->x = x*32;
	tilePos->y = y*32;
}

Tile::~Tile()
{
}

void Tile::cout()
{
	std::cout << screenPos->x << " " << screenPos->y << " " << screenPos->w << " " << screenPos->h << "screenPos" << std::endl;
	std::cout << tilePos->x << " " << tilePos->y << " " << tilePos->w << " " << tilePos->h << "tilePos" << std::endl;
}
