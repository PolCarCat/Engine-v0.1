#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 11

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleFadeToBlack;
class ModuleSound;
class ModuleCollision;
class ModuleParticles;
class ModuleEnemies;
class ModuleFonts;
class Module;
class ModuleInterface;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleFadeToBlack* fade;
	ModuleSound* sound;
	ModuleCollision* collision;
	ModuleParticles* particles;
	ModuleEnemies* enemies;
	ModuleFonts* fonts;
	Module* current_scene;
	ModuleInterface* interfac;


public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();
	int level = 1;

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__