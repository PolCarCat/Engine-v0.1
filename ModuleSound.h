#ifndef __ModuleSound_H__
#define __ModuleSound_H__

#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "SDL_mixer\include\SDL_mixer.h"

#define MAX_SOUNDS 20
#define MAX_MUSICS 5

class ModuleSound :
	public Module
{
public:
	Mix_Chunk* sounds[MAX_SOUNDS];
	Mix_Music* music[MAX_MUSICS];

	bool Init();
	Mix_Chunk* LoadSound(const char* path);
	Mix_Music* LoadMusic(const char* path);
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool PlayMusic(Mix_Music* music, int loops = -1);
	void StopMusic(bool pause = false);
	void StopAll();
	bool PlaySound(Mix_Chunk* sound, int loops = 0);
	bool isPlayingMusic();
	bool CleanUp();
	void ExecuteOnMusicEnd(void(*function)(void));

	ModuleSound();
	~ModuleSound();
};

void PlayMainMusic();

#endif // __ModuleSound_H__