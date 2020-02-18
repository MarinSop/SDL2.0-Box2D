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
	void moveBody(std::vector<Body*> dynamicBodyList);
	void relese(std::vector<Body*> dynamicBodyList);
	void activateBarriers(std::vector<Body*> barrierBodyList);
	void deactivateBarriers(std::vector<Body*> barrierBodyList);

private:
	bool areBarriersActive = false;
	



};

