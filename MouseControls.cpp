#include "MouseControls.h"

MouseControls::MouseControls()
{
	
}

MouseControls::~MouseControls()
{
}

void MouseControls::addForceToBody(std::vector<Body*> dynamicBodyList)
{
	if (hold == true)
	{
		int mousePosX, mousePosY;
		SDL_GetMouseState(&mousePosX, &mousePosY);
		for (auto b : dynamicBodyList)
		{
			if (b->getGraphicsBodyPosition()->x < mousePosX &&
				b->getGraphicsBodyPosition()->x + b->getGraphicsBodyPosition()->w > mousePosX &&
				b->getGraphicsBodyPosition()->y < mousePosY &&
				b->getGraphicsBodyPosition()->y + b->getGraphicsBodyPosition()->h > mousePosY)
			{
				b->held = true;
			}
		}

	}

}

void MouseControls::relese(std::vector<Body*> dynamicBodyList)
{
	for (auto b : dynamicBodyList)
	{
		b->held = false;
	}
}

