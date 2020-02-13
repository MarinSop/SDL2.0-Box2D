#include "SDL.h"
#include "Game.h"


#define M2P 30.0f
#define P2M 1/M2P
#define WIDTH 1024.0f
#define HEIGHT 768.0f

int main(int argc, char* args[])
{
	SDL_Window* window = NULL;
	window = SDL_CreateWindow("yay", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* render = NULL;
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	Game game;
	while (game.isRunning)
	{
	game.update(window);
	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	SDL_RenderClear(render);
	game.render(render);
	SDL_RenderPresent(render);
	}
	return EXIT_SUCCESS;
}