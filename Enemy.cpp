#include "Enemy.h"

Enemy::Enemy(SDL_Renderer* renderer, b2World* world)
	: _world(world)
{
	_physicBody = new PhysicBody();
	_graphicBody = new GraphicBody();
	_physicBody->addRectBody(world, b2Vec2(500, 0), b2Vec2(32, 32), BodyType::Dynamic, false, 0.1, 2, NULL, (std::string*)"enemy");
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
			if (!f->RayCast(&rayOutput, rayInput,1))
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
	// detecting if closest object is player
	if (userdata == "player")
		std::cout << "player detected" << std::endl;
}

void Enemy::draw(SDL_Renderer* renderer)
{
	_graphicBody->drawWithAddedTex(renderer);
}
