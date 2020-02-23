#include "Player.h"

Player::Player(b2World* world,SDL_Renderer* renderer,char const* texPath, b2Vec2 startingPos)
	:_world(world)
{
	//creating texture
	SDL_Surface* surface = IMG_Load(texPath);
	_playerTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	//creating player
	SDL_Point size = { 32.0f,32.0f };
	SDL_Color color = { 0,0,255,255 };
	_physicBody = new PhysicBody();
	_graphicsBody = new GraphicBody();
	_physicBody->addRectBody(world, b2Vec2(startingPos.x*32.0f, startingPos.y*32.0f), b2Vec2(size.x, size.y), BodyType::Dynamic, false, 0.1, 2, NULL,(std::string*)"player");
	_physicBody->getBody()->SetFixedRotation(true);
	_graphicsBody->addGraphics(renderer,size, _physicBody->getBody()->GetPosition(),size,1);
	//creating foot sensor
	_physicBody->addFixtureToBody(b2Vec2(0.0f,16.0f),b2Vec2(size.x-6,16),true,NULL,NULL,NULL,(std::string*)"foot");
	rect.w = size.x+3;
	rect.h = size.y+3;
}

Player::~Player()
{
	delete _playerTexture;
	
}

void Player::update()
{
	//applying drag force to the player
	_physicBody->getBody()->ApplyForceToCenter(b2Vec2(_physicBody->getBody()->GetLinearVelocity().x* -1*_dragForce,0.0f),true);
}

void Player::draw(SDL_Renderer* render)
{
	//drawing player body
	_graphicsBody->setPhysicPosition(_physicBody->getBody()->GetPosition(),_physicBody->getBody()->GetAngle());
	/*rect.x = _physicBody.getBody()->GetPosition().x * M2P - rect.w / 2.0f;
	rect.y = _physicBody.getBody()->GetPosition().y * M2P - rect.h / 2.0f;
	SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
	SDL_RenderFillRect(render, &rect);*/
	_graphicsBody->draw(render,_playerTexture);
}

void Player::inputHandler()
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_A])
	{
		_physicBody->getBody()->ApplyLinearImpulseToCenter(b2Vec2(-_moveSpeed*P2M,0.0f),true);
	}
	if (keystate[SDL_SCANCODE_D])
	{
		_physicBody->getBody()->ApplyLinearImpulseToCenter(b2Vec2(_moveSpeed * P2M, 0.0f), true);
	}
}

void Player::jump()
{
	_physicBody->getBody()->ApplyLinearImpulseToCenter(b2Vec2(0.0f * P2M, -_jumpHeight * P2M), true);
}

void Player::freeze()
{
	_physicBody->getBody()->SetType(b2_staticBody);
}

void Player::unFreeze()
{
	_physicBody->getBody()->SetType(b2_dynamicBody);
}

void Player::setPosition(b2Vec2 pos, float angle)
{
	_physicBody->getBody()->SetTransform(b2Vec2(pos.x*P2M,pos.y*P2M),angle);
}

b2Vec2 Player::getPosition()
{
	return b2Vec2(_graphicsBody->getGamePos()->x,_graphicsBody->getGamePos()->y);
}


