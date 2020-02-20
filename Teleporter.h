#pragma once
#include "GraphicBody.h"
#include "Player.h"

class Teleporter
{
public:
	Teleporter(SDL_Renderer* renderer, b2Vec2 size, b2Vec2 pos, b2Vec2  tileSize, int id, b2Vec2 posToTP, const char* texPath);
	~Teleporter();

	void update(Player& player);
	void draw(SDL_Renderer* renderer);
private:
	GraphicBody* _graphicBody;
	b2Vec2 _teleportToPos;

	SDL_Texture* _tex;
};

