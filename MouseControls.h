#pragma once
#include "box2d/box2d.h"
#include "SDL.h"
#include <vector>
#include "Body.h"
class MouseControls
{
public:
	MouseControls();
	~MouseControls();

	bool hold = false;
	void addForceToBody(std::vector<Body*> dynamicBodyList);
	void relese(std::vector<Body*> dynamicBodyList);

private:
	
	



};

