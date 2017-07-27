#ifndef __Camera_H__
#define __Camera_H__

#include "Globals.h"
#include "p2Point.h"
#include "SDL\include\SDL_mouse.h"

class Camera
{
private:
	iPoint screen_position;
	iPoint pivot;

public:
	Camera();
	~Camera();

	iPoint getWorldPosition();
};

#endif