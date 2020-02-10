#pragma once
#include <iostream>
#include "box2d/box2d.h"
class MyContactListener : public b2ContactListener
{
public:
	bool isOnGround = false;
	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);



};

