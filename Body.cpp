#include "Body.h"

Body::Body(b2World* world, SDL_Renderer* renderer, b2Vec2 pos, b2Vec2 size, BodyType type, bool isSensor,
	float friction, float density, float restitution, std::string* userData, float id,const char* texPath)
{
	_ID = id;
	_type = type;
	_startingPos = pos;
	_size = size;
	_physicBody = new PhysicBody();
	_freezeTimer = new SDL_Rect();
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
	SDL_Point tileSize = { 32,32 };
	_graphicBody->addGraphics(renderer,SDLsize,_physicBody->getBody()->GetPosition(),tileSize,id);

	_freezeTimer->w = size.x;
	_startFreezeTimerWidth = size.x;
	_freezeTimer->h = 10;
	_freezeTimer->x = pos.x;
	_freezeTimer->y = pos.y;
	}

}

Body::~Body()
{
	delete _graphicBody;
	delete _physicBody;
	SDL_DestroyTexture(_bodyTexture);
	_bodyTexture = nullptr;
	delete _freezeTimer;
}

void Body::update()
{
	if (isFrozen == true)
	{
		_physicBody->getBody()->SetLinearVelocity(b2Vec2(0,0));
		if (_timerStart == false)
		{
			_timerStartPos = SDL_GetTicks() + 5000;
			_timerStart = true;
		}
		float current = SDL_GetTicks();
		_freezeTimer->w = abs(current - _timerStartPos) / _timerStartPos * _startFreezeTimerWidth;
	//	std::cout << abs(current - _timerStartPos) / _timerStartPos * _startFreezeTimerWidth << std::endl;
		
		_physicBody->getBody()->SetType(b2_staticBody);
		if (current > _timerStartPos)
		{
			_physicBody->getBody()->SetType(b2_dynamicBody);
			isFrozen = false;
			used = true;
		}
	}
	else if (held == true && isFrozen == false)
	{
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		b2Vec2 mouse(mouseX,mouseY);
		mouse -= (M2P*_physicBody->getBody()->GetWorldCenter());
		_physicBody->getBody()->SetFixedRotation(true);
		_physicBody->getBody()->SetLinearVelocity(mouse);
	}
	//	std::cout << _physicBody->getBody()->GetLinearVelocity().x << "   " << _physicBody->getBody()->GetLinearVelocity().y << std::endl;
	_graphicBody->setPhysicPosition(_physicBody->getBody()->GetPosition(),_physicBody->getBody()->GetAngle());
	if (isFrozen == true)
	{
		_freezeTimer->x = _graphicBody->getGamePos()->x;
		_freezeTimer->y = _graphicBody->getGamePos()->y - 15;
	}
}

void Body::draw(SDL_Renderer* renderer)
{
	_graphicBody->draw(renderer,_bodyTexture);
	if (isFrozen == true)
	{
		SDL_SetRenderDrawColor(renderer, 126, 192, 238, 255);
		SDL_RenderFillRect(renderer,_freezeTimer);
	}
}

void Body::reset()
{
	_physicBody->getBody()->SetTransform(b2Vec2(_startingPos.x*P2M+(_size.x/2)*P2M,
		_startingPos.y*P2M),0);
	used = false;
	held = false;
	isFrozen = false;
	_timerStart = false;
	_physicBody->getBody()->SetType(b2_dynamicBody);
	_physicBody->getBody()->SetFixedRotation(false);

}

SDL_Rect* Body::getGraphicsBodyPosition()
{
	return _graphicBody->getGamePos();
}

PhysicBody* Body::getPhysicBody()
{
	return _physicBody;
}
