#include "Game.h"

Game::Game()
{
	isRunning = true;
	_world = new b2World(_gravity);
	_contactListener = new MyContactListener();
	_world->SetContactListener(_contactListener);
	_player = new Player(_world);
	SDL_Point size = { 1000,10 };
	SDL_Color color = { 0,255,0,255 };
	//_physicBody.addRectBody(_world, b2Vec2(512.0f, 700.0f), b2Vec2(size.x, size.y), BodyType::Static,false,NULL,NULL,NULL,NULL);
	//_graphicsBody.addGraphics(size, _physicBody.getBody()->GetPosition(), color);
	_map = new Map();
	_map->load(_world);
}

	Game::~Game()
{

}

void Game::update(SDL_Window* window)
{
	EventHandler(window);
	_world->Step(1/60.0f,6,3);
	_player->update();
	_map->update();
}

void Game::render(SDL_Renderer* renderer)
{
	_player->draw(renderer);
	_map->draw(renderer);
	//_graphicsBody.draw(renderer);
}

void Game::EventHandler(SDL_Window* window)
{
	_player->inputHandler();
	
	SDL_Event _events;
	while (SDL_PollEvent(&_events))
	{
		switch (_events.type)
		{
		case SDL_KEYDOWN:
			if (_events.key.keysym.sym == SDLK_ESCAPE)
			{
				isRunning = false;
				SDL_DestroyWindow(window);
			}
			if (_events.key.keysym.sym == SDLK_SPACE)
			{
				if (_contactListener->isOnGround == true)
				{
				_player->jump();
				}
			}
			break;


		case SDL_KEYUP:
			break;


		case SDL_QUIT:
			isRunning = false;
			SDL_DestroyWindow(window);
			break;
		default:
			break;
		}
	}


}
