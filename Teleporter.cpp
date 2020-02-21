#include "Teleporter.h"

Teleporter::Teleporter(SDL_Renderer* renderer, b2Vec2 size, b2Vec2 pos, b2Vec2  tileSize, int id, b2Vec2 posToTP, const char* texPath)
	: _teleportToPos(posToTP)
{
	_graphicBody = new GraphicBody();
	SDL_Surface* surface = IMG_Load("textures\\tilemap.png");
	_tex = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_Point SDLsize = { size.x,size.y };
	SDL_Point SDLtileSize = { tileSize.x, tileSize.y };
	_graphicBody->addGraphics(renderer,SDLsize,b2Vec2(pos.x,pos.y-32),SDLtileSize,id);
}

Teleporter::~Teleporter()
{
	delete _graphicBody;
	SDL_DestroyTexture(_tex);
	_tex = nullptr;
}

void Teleporter::update(Player& player)
{
	if (_graphicBody->getGamePos()->x < player.getBodyPosition().x*M2P &&
		_graphicBody->getGamePos()->x + _graphicBody->getGamePos()->w > player.getBodyPosition().x* M2P &&
		_graphicBody->getGamePos()->y < player.getBodyPosition().y * M2P &&
		_graphicBody->getGamePos()->y + _graphicBody->getGamePos()->h > player.getBodyPosition().y * M2P)
	{
		std::cout << _teleportToPos.x * 32 << " " << _teleportToPos.y * 32 << std::endl;
		player.setPosition(b2Vec2(_teleportToPos.x*32,_teleportToPos.y*32),0);
	}
}

void Teleporter::draw(SDL_Renderer* renderer)
{
	_graphicBody->draw(renderer,_tex);
}
