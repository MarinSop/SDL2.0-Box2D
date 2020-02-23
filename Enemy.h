#pragma once
#include "PhysicBody.h"
#include "GraphicBody.h"
#include "Player.h"
#include <string>
class Enemy
{
public:
	Enemy(SDL_Renderer* renderer,b2World* world);
	~Enemy();
	
	void update(Player* player);
	void draw(SDL_Renderer* renderer);


private:
	b2World* _world;
	PhysicBody* _physicBody;
	GraphicBody* _graphicBody;

};

