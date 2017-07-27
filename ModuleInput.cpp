#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput() : Module()
{
	for(uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;
}

// Destructor
ModuleInput::~ModuleInput()
{
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0)
	{
		LOG("SDL_GAMECONTROLLER could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	int joy = SDL_NumJoysticks();
	num_gamepads = SDL_NumJoysticks() / 2;
	if (num_gamepads < 1)
	{
		LOG("No gamepads connected!\n");
	}
	else {
		for (uint i = 0; i < num_gamepads; i++) {
			gamepads[i].controller = SDL_GameControllerOpen(i);
			if (gamepads[i].controller == nullptr)
			{
				LOG("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
				LOG("Two or more regular joysticks might be plugged in\n");
			}
			else gamepads[i].active = true;
		}
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	//SDL_PumpEvents();
	SDL_Event current_event;

	while (SDL_PollEvent(&current_event)) {
		switch ((SDL_EventType)current_event.type)
		{
		case SDL_JOYDEVICEADDED:
			for (uint i = 0; i < MAX_CONTROLLERS; i++) {
				if (!gamepads[i].active) {
					gamepads[i].controller = SDL_GameControllerOpen(i);
					if (gamepads[i].controller == nullptr)
					{
						LOG("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
					}
					else gamepads[i].active = true;
				}
			}
			break;
		case SDL_JOYDEVICEREMOVED:
			for (uint i = 0; i < MAX_CONTROLLERS; i++) {
				if (gamepads[i].active && !SDL_GameControllerGetAttached(gamepads[i].controller)) {
					gamepads[i].active = false;
					SDL_GameControllerClose(gamepads[i].controller);
					gamepads[i].controller = nullptr;
				}
			}
			break;
		default:
			break;
		}
	}

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for(int i = 0; i < MAX_KEYS; ++i)
	{
		if(keys[i] == 1)
		{
			if(keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if(keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	if(keyboard[SDL_SCANCODE_ESCAPE])
		return update_status::UPDATE_STOP;


	for (uint i = 0; i < MAX_CONTROLLERS; i++) {
		if (!gamepads[i].active) continue;

		SDL_GameController* controller = gamepads[i].controller;

		gamepads[i].left_joystick.x = (float)(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX) / 32767);
		gamepads[i].left_joystick.y = (float)(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY) / 32767);
		gamepads[i].right_joystick.x = (float)(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX) / 32767);
		gamepads[i].right_joystick.y = (float)(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY) / 32767);
		gamepads[i].left_trigger = (float)(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT) / 32767);
		gamepads[i].right_trigger = (float)(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) / 32767);

		gamepads[i].left_bumper.setState((bool)SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER));
		gamepads[i].right_bumper.setState((bool)SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER));

		gamepads[i].start.setState((bool)SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START));
		gamepads[i].back.setState((bool)SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_BACK));

		gamepads[i].y_button.setState((bool)SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y));
		gamepads[i].x_button.setState((bool)SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X));
		gamepads[i].a_button.setState((bool)SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A));
		gamepads[i].b_button.setState((bool)SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B));

		gamepads[i].d_pad.up.setState((bool)SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP));
		gamepads[i].d_pad.down.setState((bool)SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN));
		gamepads[i].d_pad.left.setState((bool)SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT));
		gamepads[i].d_pad.right.setState((bool)SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT));
	}
	
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	for (uint i = 0; i < num_gamepads; i++) {
		gamepads[i].active = false;
		SDL_GameControllerClose(gamepads[i].controller);
		gamepads[i].controller = nullptr;
	}
	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
	return true;
}