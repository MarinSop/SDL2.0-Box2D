#pragma once
#include "SDL.h"
#include "box2d/box2d.h"
#include "PhysicBody.h"
#include "Player.h"
#include "GraphicBody.h"
#include "MyContactListener.h"
class Game
{
public:
	Game();
	~Game();

	void update(SDL_Window* window);
	void render(SDL_Renderer* renderer);

	bool isRunning;

private:

	b2World* _world;
	b2Vec2 _gravity = b2Vec2(0.0f,1.0f);

	Player* _player;
	PhysicBody _physicBody;
	GraphicBody _graphicsBody;
	MyContactListener* _contactListener;
	void EventHandler(SDL_Window* window);
};

