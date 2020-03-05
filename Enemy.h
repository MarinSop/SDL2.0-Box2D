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

	float _playerDetectionDistance = 200.0f;
	float _moveSpeed = 1.0f;
	float _jumpHeight = 150.0f;
	float _dragForce = 0.8f;

	void detectPlayer(Player* player);

};

