#include "MouseControls.h"

MouseControls::MouseControls()
{
	
}

MouseControls::~MouseControls()
{
}

void MouseControls::moveBody(std::vector<Body*> dynamicBodyList)
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
				b->getGraphicsBodyPosition()->y + b->getGraphicsBodyPosition()->h > mousePosY && b->used == false)
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
		if(b->held == true)
		{
			b->held = false;
			b->getPhysicBody()->getBody()->SetFixedRotation(false);
			b->isFrozen = true;

		}
	}
}

void MouseControls::activateBarriers(std::vector<Body*> barrierBodyList)
{
	if (areBarriersActive == false)
	{
		for (auto b : barrierBodyList)
		{
			areBarriersActive = true;
			b->getPhysicBody()->getBody()->SetActive(true);
		}
	}
}

void MouseControls::deactivateBarriers(std::vector<Body*> barrierBodyList)
{
	if (areBarriersActive == true)
	{
		for (auto b : barrierBodyList)
		{
			areBarriersActive = false;
			b->getPhysicBody()->getBody()->SetActive(false);
		}
	}
}

