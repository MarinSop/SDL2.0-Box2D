#include "MyContactListener.h"

void MyContactListener::BeginContact(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	if (static_cast<char const*>(fixtureA->GetUserData()) == "foot")
	{
		++numFootContact;
	//	std::cout << numFootContact << " A" << std::endl;
	}
	if (static_cast<char const*>(fixtureB->GetUserData()) == "foot")
	{
		++numFootContact;
	//	std::cout << numFootContact << " B " << std::endl;
	
	}

}

void MyContactListener::EndContact(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	if (static_cast<char const*>(fixtureA->GetUserData()) == "foot")
	{
		--numFootContact;
	//	std::cout << numFootContact << " A" << std::endl;
	}
	if (static_cast<char const*>(fixtureB->GetUserData()) == "foot")
	{
		--numFootContact;
	//	std::cout << numFootContact << " B " << std::endl;
	}
}
