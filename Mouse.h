#ifndef __Mouse_H__
#define __Mouse_H__

#include "Globals.h"
#include "p2Point.h"

class Mouse
{
private:
	iPoint screen_position;

public:
	iPoint getWorldPosition() {
		return iPoint{ screen_position.x, screen_position.y };
	}

	Mouse();
	~Mouse();
};
#endif