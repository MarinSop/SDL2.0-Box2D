#include "GraphicBody.h"

GraphicBody::GraphicBody()
{
	_gamePos = new SDL_Rect();
	_tilePos = new SDL_Rect();
}

GraphicBody::~GraphicBody()
{
	SDL_DestroyTexture(_tex);
	_tex = nullptr;
	delete _gamePos;
	delete _tilePos;
}

void GraphicBody::addGraphics(SDL_Renderer* renderer, SDL_Point size, b2Vec2 pos, SDL_Point tileSize,int id)
{
	_gamePos->w = size.x;
	_gamePos->h = size.y;
	_gamePos->x = pos.x;// *M2P - _gamePos.w / 2.0f;
	_gamePos->y = pos.y;// *M2P - _gamePos.h / 2.0f;
	b2Vec2 texPos = imageTilePos(id);
	_tilePos->x = texPos.x*32;
	_tilePos->y = texPos.y*32;
	_tilePos->w = tileSize.x;
	_tilePos->h = tileSize.y;
}

void GraphicBody::addTexture(SDL_Renderer* renderer,const char* path)
{
	SDL_Surface* surface = IMG_Load(path);
	_tex = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
}

void GraphicBody::setPhysicPosition(b2Vec2 pos, float angle)
{
	_gamePos->x = pos.x * M2P - _gamePos->w / 2.0f;
	_gamePos->y = pos.y * M2P - _gamePos->h / 2.0f;
	_angle = angle * 57.3f;
}

void GraphicBody::draw(SDL_Renderer* render, SDL_Texture* tex)
{
	SDL_RenderCopyEx(render,tex,_tilePos,_gamePos,_angle,NULL,SDL_FLIP_NONE);
}

void GraphicBody::drawWithAddedTex(SDL_Renderer* renderer)
{
	SDL_RenderCopyEx(renderer, _tex, _tilePos, _gamePos, _angle, NULL, SDL_FLIP_NONE);
}


SDL_Rect* GraphicBody::getGamePos()
{
	return _gamePos;
}

b2Vec2 GraphicBody::imageTilePos(int id)
{
	int w = 12;
	int h = 8;
	b2Vec2 result;
	int x = 0;
	int y = 0;
	for (int i = 0; i < id-1; i++)
	{
		if (y < h)
		{
			if (x < w-1)
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

	result = b2Vec2(x, y);

	return result;
}
