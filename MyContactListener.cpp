#include "MyContactListener.h"

void MyContactListener::BeginContact(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	if (static_cast<char const*>(fixtureA->GetUserData()) == "foot")
	{
		isOnGround = true;
	}
	if (static_cast<char const*>(fixtureB->GetUserData()) == "foot")
	{
		isOnGround = true;
	}

}

void MyContactListener::EndContact(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	if (static_cast<char const*>(fixtureA->GetUserData()) == "foot")
	{
		isOnGround = false;
	}
	if (static_cast<char const*>(fixtureB->GetUserData()) == "foot")
	{
		isOnGround = false;
	}
}
