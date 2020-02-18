#include "PhysicBody.h"

PhysicBody::PhysicBody()
{
}

PhysicBody::~PhysicBody()
{
	_world->DestroyBody(_body);
}

b2Body* PhysicBody::addRectBody(b2World* world, b2Vec2 pos, b2Vec2 size, BodyType type, bool isSensor,
	float friction, float density, float restitution, std::string* userData)
{
	_world = world;
	//creating bodyDef
	switch (type)
	{
	case Dynamic:
		_bodyDef.type = b2_dynamicBody;
		break;
	case Kinematic:
		_bodyDef.type = b2_kinematicBody;
		break;
	case Static:
		_bodyDef.type = b2_staticBody;
		break;
	default:
		break;
	}
	_bodyDef.position.Set(pos.x*P2M+(size.x/2)*P2M,pos.y*P2M+(size.y/2)*P2M);
	//creating body
	_body = _world->CreateBody(&_bodyDef);
	//creating shape
	_polygonShape.SetAsBox((size.x/2.0f)*P2M,(size.y/2.0f)*P2M);
	//creatin fixture
	_fixtureDef.shape = &_polygonShape;
	if (isSensor)
		_fixtureDef.isSensor = true;
	if (friction != NULL)
		_fixtureDef.friction = friction;
	if (density != NULL)
		_fixtureDef.density = density;
	if (restitution != NULL)
		_fixtureDef.restitution = restitution;
	if (userData != NULL)
		_fixtureDef.userData = const_cast<char*>((char*)userData);
	_body->CreateFixture(&_fixtureDef);
	return _body;
}

b2FixtureDef* PhysicBody::addFixtureToBody(b2Vec2 pos, b2Vec2 size, bool isSensor,
	float friction, float density, float restitution, std::string* userData)
{
	b2PolygonShape newShape;
	newShape.SetAsBox((size.x / 2.0f) * P2M, (size.y / 2.0f) * P2M, b2Vec2(pos.x*P2M,pos.y * P2M), 0);
	b2FixtureDef newFixture;
	newFixture.shape = &newShape;
	if (isSensor)
		newFixture.isSensor = true;
	if (friction != NULL)
		newFixture.friction = friction;
	if (density != NULL)
		newFixture.density = density;
	if (restitution != NULL)
		newFixture.restitution = restitution;
	if(userData != NULL)
		newFixture.userData = const_cast<char*>((char*)userData);
	_body->CreateFixture(&newFixture);
	return &newFixture;
}

b2Body* PhysicBody::getBody()
{
	return _body;
}

b2BodyDef* PhysicBody::getBodyDef()
{
	return &_bodyDef;
}

b2FixtureDef* PhysicBody::getFixtureDef()
{
	return &_fixtureDef;
}
