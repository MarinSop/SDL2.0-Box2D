#include "Body.h"

Body::Body(b2World* world, b2Vec2 pos, b2Vec2 size, BodyType type, bool isSensor,
	float friction, float density, float restitution, std::string* userData, float id)
{
	_ID = id;
	_type = type;
	_physicBody = new PhysicBody();
	//if (type == BodyType::Dynamic) _graphicBody = new GraphicBody();
	//else _graphicBody = nullptr;
	_graphicBody = new GraphicBody();
	_physicBody->addRectBody(world,pos,size,type,isSensor,friction,density,restitution,userData);
	if (_graphicBody != nullptr)
	{
	SDL_Point SDLsize = { size.x,size.y};
	SDL_Color SDLcolor = { 0,0,255,255 };
	_graphicBody->addGraphics(SDLsize,_physicBody->getBody()->GetPosition(),SDLcolor);
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
	_graphicBody->draw(renderer);
}
