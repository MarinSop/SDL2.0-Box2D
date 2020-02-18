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
	delete _graphicBody;
	delete _physicBody;
	delete _bodyTexture;
}

void Body::update()
{
	if (held == true && isFrozen == false)
	{
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		b2Vec2 mouse(mouseX,mouseY);
		mouse -= (M2P*_physicBody->getBody()->GetWorldCenter());
		_physicBody->getBody()->SetFixedRotation(true);
		_physicBody->getBody()->SetLinearVelocity(mouse);
	}
	if (isFrozen == true)
	{

		if (_timerStart == false)
		{
			_timerStartPos = SDL_GetTicks();
			_timerStart = true;
		}
		int current = SDL_GetTicks();
		_physicBody->getBody()->SetType(b2_staticBody);
		if (current > _timerStartPos + 5000)
		{
			_physicBody->getBody()->SetType(b2_dynamicBody);
			isFrozen = false;
			used = true;
		}
	}
	_graphicBody->setPhysicPosition(_physicBody->getBody()->GetPosition(),_physicBody->getBody()->GetAngle());
}

void Body::draw(SDL_Renderer* renderer)
{
	_graphicBody->draw(renderer,_bodyTexture);
}

SDL_Rect* Body::getGraphicsBodyPosition()
{
	return _graphicBody->getGamePos();
}

PhysicBody* Body::getPhysicBody()
{
	return _physicBody;
}
