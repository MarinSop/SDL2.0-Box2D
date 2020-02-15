#include "Body.h"

Body::Body(b2World* world, SDL_Renderer* renderer, b2Vec2 pos, b2Vec2 size, BodyType type, bool isSensor,
	float friction, float density, float restitution, std::string* userData, float id,const char* texPath)
{
	_ID = id;
	_type = type;
	_physicBody = new PhysicBody();
	if (texPath != NULL)
	{
	SDL_Surface* surface = IMG_Load(texPath);
	_bodyTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	}
	else
	{
		delete _bodyTexture;
	}
	if (type == BodyType::Dynamic) _graphicBody = new GraphicBody();
	else _graphicBody = nullptr;
	_physicBody->addRectBody(world,pos,size,type,isSensor,friction,density,restitution,userData);
	if (_graphicBody != nullptr)
	{
	SDL_Point SDLsize = { size.x,size.y};
	_graphicBody->addGraphics(renderer,SDLsize,_physicBody->getBody()->GetPosition(),SDLsize,id);
	}

}

Body::~Body()
{
}

void Body::update()
{
	_graphicBody->setPhysicPosition(_physicBody->getBody()->GetPosition());
}

void Body::draw(SDL_Renderer* renderer)
{
	_graphicBody->draw(renderer,_bodyTexture);
}
