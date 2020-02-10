#pragma once
#include "box2d/box2d.h"
#include "SDL.h"
#include "PhysicBody.h"
#include "GraphicBody.h"

class Player
{
public:
	Player(b2World* world);
	~Player();

	void update();
	void draw(SDL_Renderer* render);

	void inputHandler();
	void jump();
private:
	PhysicBody _physicBody;
	GraphicBody _graphicsBody;
	float dragForce = 0.5f;
	SDL_Rect rect;

};

