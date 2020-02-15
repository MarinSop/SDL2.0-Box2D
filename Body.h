#pragma once
#include "GraphicBody.h"
#include "PhysicBody.h"
class Body
{
public:
	Body(b2World* world,SDL_Renderer* renderer, b2Vec2 pos, b2Vec2 size, BodyType type, bool isSensor,
		float friction, float density, float restitution, std::string* userData, float id, const char* texPath);
	~Body();

	void update();
	void draw(SDL_Renderer* renderer);

private:
	float _ID;
	BodyType _type;
	PhysicBody* _physicBody;
	GraphicBody* _graphicBody;
	SDL_Texture* _bodyTexture;
};

