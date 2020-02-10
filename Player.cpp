#include "Player.h"

Player::Player(b2World* world)
{
	//creating player
	SDL_Point size = { 30.0f,30.0f };
	SDL_Color color = { 0,0,255,255 };
	_physicBody.addRectBody(world, b2Vec2(500.0f, 0.0f), b2Vec2(size.x, size.y), BodyType::Dynamic, false, NULL, NULL, NULL,NULL);
	_graphicsBody.addGraphics(size, _physicBody.getBody()->GetPosition(), color);
	_physicBody.getFixtureDef()->friction = 0.0f;
	//creating foot sensor
	_physicBody.addFixtureToBody(b2Vec2(size.x,10.0f),b2Vec2(30.0f,10.0f),true,NULL,NULL,NULL,(std::string*)"foot");
	rect.w = size.x;
	rect.h = 10.0f;
}

Player::~Player()
{
}

void Player::update()
{
	//applying drag force to the player
	_physicBody.getBody()->ApplyForceToCenter(b2Vec2(_physicBody.getBody()->GetLinearVelocity().x* -1*dragForce,0.0f),true);
}

void Player::draw(SDL_Renderer* render)
{
	//drawing player body
	_graphicsBody.setPhysicPosition(_physicBody.getBody()->GetPosition());
	rect.x = _physicBody.getBody()->GetPosition().x * M2P - rect.w / 2.0f;
	rect.y = _physicBody.getBody()->GetPosition().y * M2P - rect.h / 2.0f+30/2.0f;
	_graphicsBody.draw(render);
	SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
	SDL_RenderFillRect(render, &rect);
}

void Player::inputHandler()
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_A])
	{
		_physicBody.getBody()->ApplyLinearImpulseToCenter(b2Vec2(-0.5f*P2M,0.0f),true);
	}
	if (keystate[SDL_SCANCODE_D])
	{
		_physicBody.getBody()->ApplyLinearImpulseToCenter(b2Vec2(0.5f * P2M, 0.0f), true);
	}
}

void Player::jump()
{
	_physicBody.getBody()->ApplyLinearImpulseToCenter(b2Vec2(0.0f * P2M, -100.0f * P2M), true);
}


