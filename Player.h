#pragma once
#include "box2d/box2d.h"
#include "SDL.h"
#include "SDL_image.h"
#include "PhysicBody.h"
#include "GraphicBody.h"

class Player
{
public:
	Player(b2World* world, SDL_Renderer* renderer, char const* texPath);
	~Player();

	void update();
	void draw(SDL_Renderer* render);

	void inputHandler();
	void jump();
private:
	PhysicBody _physicBody;
	GraphicBody _graphicsBody;
	SDL_Texture* _playerTexture;
	float _dragForce = 0.8f;
	float _jumpHeight = 250.0f;
	float _moveSpeed = 1.f;
	SDL_Rect rect;

};

