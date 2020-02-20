#include "Game.h"

Game::Game(SDL_Renderer* renderer)
{
	isRunning = true;
	_world = new b2World(_gravity);
	_contactListener = new MyContactListener();
	_world->SetContactListener(_contactListener);
	_map = new Map();
	_map->load(_world,renderer);
	_player = new Player(_world,renderer,"textures\\player.png",_map->startingPos);
	_mouseControls = new MouseControls();
	
}

	Game::~Game()
{

}

void Game::update(SDL_Window* window)
{
	EventHandler(window);
	_mouseControls->moveBody(_map->getDynamicBodies());
	_world->Step(1/60.0f,8,3);
	_player->update();
	_map->update(*_player);
}

void Game::render(SDL_Renderer* renderer)
{
	_map->draw(renderer);
	_player->draw(renderer);
	
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
				if (_contactListener->numFootContact > 0)
				{
				_player->jump();
				}
			}
			break;


		case SDL_KEYUP:
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (_events.button.button == SDL_BUTTON_LEFT)
			{
				_mouseControls->hold = true;
				_mouseControls->activateBarriers(_map->getBarrierBodies());
				_player->freeze();
			}
			break;

		case SDL_MOUSEBUTTONUP:
			if (_events.button.button == SDL_BUTTON_LEFT)
			{
				_mouseControls->hold = false;
				_mouseControls->relese(_map->getDynamicBodies());
				_mouseControls->deactivateBarriers(_map->getBarrierBodies());
				_player->unFreeze();
			}
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


