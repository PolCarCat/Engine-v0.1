#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL_gamecontroller.h"

#define MAX_KEYS 300
#define MAX_CONTROLLERS 16

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

struct Button {
	KEY_STATE state = KEY_IDLE;

	void setState(bool input) {
		switch (state) {
		case KEY_IDLE:
			state = input ? KEY_DOWN : state;
			break;
		case KEY_DOWN:
			state = input ? KEY_REPEAT : state;
			break;
		case KEY_REPEAT:
			state = input ? state : KEY_UP;
			break;
		case KEY_UP:
			state = input ? KEY_DOWN : KEY_IDLE;
			break;
		}
	}
};

struct GamePad {
	bool active = false;	//Wether the controller is connected or not
	SDL_GameController* controller = nullptr;	//The controller's associated SDL_GameController pointer

	p2Point<float> left_joystick;
	p2Point<float> right_joystick;

	float left_trigger,
		right_trigger;

	float left_joystick_deadzone = 0.0f,
		right_joystick_deadzone = 0.0f,
		left_trigger_deadzone = 0.0f,
		right_trigger_deadzone = 0.0f;

	Button back,
		start,
		left_bumper,
		right_bumper,
		y_button,
		x_button,
		a_button,
		b_button;

	struct D_Pad {
		Button up,
			down,
			left,
			right;
	} d_pad;
};


class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

	int num_gamepads;

public:
	GamePad gamepads[MAX_CONTROLLERS];
	KEY_STATE keyboard[MAX_KEYS];
};

#endif // __ModuleInput_H__