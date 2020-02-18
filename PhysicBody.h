#pragma once
#include "box2d/box2d.h"
#include "string"

#define M2P 30.0f
#define P2M 1/M2P

enum BodyType
{
	Dynamic,
	Kinematic,
	Static
};

class PhysicBody
{
public:
	PhysicBody();
	~PhysicBody();
	b2Body* addRectBody(b2World* world,b2Vec2 pos,b2Vec2 size,BodyType type, bool isSensor,
		float friction, float density, float restitution, std::string* userData);
	b2FixtureDef* addFixtureToBody(b2Vec2 pos,b2Vec2 size,bool isSensor
		,float friction,float density,float restitution, std::string* userData);

	b2Body* getBody();
	b2BodyDef* getBodyDef();
	b2FixtureDef* getFixtureDef();

private:
	b2World* _world;
	b2Body* _body;
	b2BodyDef _bodyDef;
	b2PolygonShape _polygonShape;
	b2FixtureDef _fixtureDef;
};

