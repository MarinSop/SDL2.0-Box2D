#include "Enemy.h"

Enemy::Enemy(SDL_Renderer* renderer, b2World* world)
	: _world(world)
{
	_physicBody = new PhysicBody();
	_graphicBody = new GraphicBody();
	_physicBody->addRectBody(world, b2Vec2(500, 0), b2Vec2(32, 32), BodyType::Dynamic, false, 0.1, 2, NULL, (std::string*)"enemy");
	_physicBody->addFixtureToBody(b2Vec2(0,0),b2Vec2(34,34),true,NULL,NULL,NULL,(std::string*)"enemyFoot");
	SDL_Point size = { 32,32 };
	_graphicBody->addGraphics(renderer, size, _physicBody->getBody()->GetPosition(), size, 1);
	_graphicBody->addTexture(renderer, "textures\\enemy.png");
}

Enemy::~Enemy()
{
	delete _physicBody;
	delete _graphicBody;
}

void Enemy::update(Player* player)
{
	_graphicBody->setPhysicPosition(_physicBody->getBody()->GetPosition(), _physicBody->getBody()->GetAngle());

	detectPlayer(player);

	if (_physicBody->getBody()->GetLinearVelocity().x != 0 && _physicBody->getBody()->GetLinearVelocity().y == 0)
	{
		b2RayCastInput jumpRayInput;
		if (_physicBody->getBody()->GetLinearVelocity().x < 0)
		{
			jumpRayInput.p1 = _physicBody->getBody()->GetPosition();
			jumpRayInput.p2 = b2Vec2(_physicBody->getBody()->GetPosition().x-(50*P2M), _physicBody->getBody()->GetPosition().y);
			jumpRayInput.maxFraction = 1;
		}
		else
		{
			jumpRayInput.p1 = _physicBody->getBody()->GetPosition();
			jumpRayInput.p2 = b2Vec2(_physicBody->getBody()->GetPosition().x + (50 * P2M), _physicBody->getBody()->GetPosition().y);
			jumpRayInput.maxFraction = 1;
		}
		for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext())
		{
			for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
			{
				b2RayCastOutput jumpRayOutput;
				if (f->RayCast(&jumpRayOutput, jumpRayInput, 1))
				{
					_physicBody->getBody()->ApplyLinearImpulseToCenter(b2Vec2(0, -_jumpHeight * P2M), 1);
				}
			}
		}
	}
}

void Enemy::draw(SDL_Renderer* renderer)
{
	_graphicBody->drawWithAddedTex(renderer);
}

void Enemy::detectPlayer(Player* player)
{
	b2RayCastInput rayInput;
	rayInput.p1 = _physicBody->getBody()->GetPosition();
	rayInput.p2 = player->getBodyPosition();
	rayInput.maxFraction = 1;

	float closestFraction = 1;
	b2Vec2 interNormal(0, 0);
	const char* userdata = nullptr;
	// getting closest object hit
	for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext())
	{
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			b2RayCastOutput rayOutput;
			if (!f->RayCast(&rayOutput, rayInput, 1))
				continue;
			if (rayOutput.fraction < closestFraction)
			{
				closestFraction = rayOutput.fraction;
				interNormal = rayOutput.normal;
				userdata = static_cast<const char*>(f->GetUserData());
			}
		}
	}
	b2Vec2 intersectionPoint = _physicBody->getBody()->GetPosition() + closestFraction *
		(player->getBodyPosition() - _physicBody->getBody()->GetPosition());

	float distance = sqrt(pow((intersectionPoint.x * M2P - _physicBody->getBody()->GetPosition().x * M2P), 2)
		+ pow((intersectionPoint.y * M2P - _physicBody->getBody()->GetPosition().y * M2P), 2));
	// detecting if closest object is player
	if (userdata == "player" && distance < _playerDetectionDistance)
	{
		if (player->getBodyPosition().x < _physicBody->getBody()->GetPosition().x)
		{
			_physicBody->getBody()->ApplyLinearImpulseToCenter(b2Vec2(-_moveSpeed * P2M, 0.0f), true);
		}
		else
		{
			_physicBody->getBody()->ApplyLinearImpulseToCenter(b2Vec2(_moveSpeed * P2M, 0.0f), true);
		}
		_physicBody->getBody()->ApplyForceToCenter(b2Vec2(_physicBody->getBody()->GetLinearVelocity().x * -1 * _dragForce, 0), true);
	}
}
