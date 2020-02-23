#pragma once
#include "box2d/box2d.h"
#include "SDL.h"
#include "SDL_image.h"
#include "PhysicBody.h"
#include "GraphicBody.h"

class Player
{
public:
	Player(b2World* world, SDL_Renderer* renderer, char const* texPath,b2Vec2 startingPos);
	~Player();

	void update();
	void draw(SDL_Renderer* render);

	void inputHandler();
	void jump();

	void freeze();
	void unFreeze();

	void setPosition(b2Vec2 pos, float angle);
	b2Vec2 getPosition();
	b2Vec2 getBodyPosition() { return _physicBody->getBody()->GetPosition(); }
private:
	PhysicBody* _physicBody;
	GraphicBody* _graphicsBody;
	SDL_Texture* _playerTexture;
	float _dragForce = 0.5f;
	float _jumpHeight = 150.0f;
	float _moveSpeed = 1.0f;
	b2World* _world;
	SDL_Rect rect;

};

