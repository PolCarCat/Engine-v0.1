#include "ModuleSound.h"
#include "SDL_mixer/include/SDL_mixer.h"

#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )


ModuleSound::ModuleSound()
{
	for (uint i = 0; i < MAX_SOUNDS; i++)
		sounds[i] = nullptr;

	for (uint i = 0; i < MAX_MUSICS; i++)
		music[i] = nullptr;
}


ModuleSound::~ModuleSound()
{
}

bool ModuleSound::Init() {
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) < 0)
	{
		LOG("Could not initialize Sound lib. Mix_Init: %s", Mix_GetError());
		return false;
	}
	return true;
}

update_status ModuleSound::PreUpdate() {
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleSound::Update() {
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleSound::PostUpdate() {
	return update_status::UPDATE_CONTINUE;
}

bool ModuleSound::CleanUp() {
	LOG("Freeing sounds and Sound library");

	for (int i = 0; i < MIX_DEFAULT_CHANNELS; i++) {
		Mix_HaltChannel(i);
	}

	for (int i = 0; i < MAX_SOUNDS; i++)
	{
		if (sounds[i] != nullptr) {
			Mix_FreeChunk(sounds[i]);
			sounds[i] = nullptr;
		}
	}
	if (isPlayingMusic())
		Mix_HaltMusic();

	for (uint i = 0; i < MAX_MUSICS; i++) {
		if (music[i] != nullptr) {
			Mix_FreeMusic(music[i]);
			music[i] = nullptr;
		}
	}

	Mix_Quit();
	return true;
}

void ModuleSound::StopAll() {
	for (int i = 0; i < MIX_DEFAULT_CHANNELS; i++) {
		Mix_HaltChannel(i);
	}

	for (int i = 0; i < MAX_SOUNDS; i++)
	{
		if (sounds[i] != nullptr) {
			Mix_FreeChunk(sounds[i]);
			sounds[i] = nullptr;
		}
	}

	if (isPlayingMusic())
		Mix_HaltMusic();

	for (uint i = 0; i < MAX_MUSICS; i++) {
		if (music[i] != nullptr) {
			Mix_FreeMusic(music[i]);
			music[i] = nullptr;
		}
	}
}

void ModuleSound::StopMusic(bool pause) {
	if (isPlayingMusic()) {
		pause ? Mix_PauseMusic() : Mix_HaltMusic();
	}
}

bool ModuleSound::PlayMusic(Mix_Music* music, int loops) {
	bool ret = true;

	if (Mix_PlayMusic(music, loops) < 0)
		ret = false;

	return ret;
}

bool ModuleSound::PlaySound(Mix_Chunk* sound, int loops) {
	bool ret = true;

	if (IsEnabled())
		if (Mix_PlayChannel(-1, sound, loops) < 0)
			ret = false;

	return ret;
}

Mix_Chunk* ModuleSound::LoadSound(const char* path) {
	Mix_Chunk* sound = Mix_LoadWAV(path);
	if (sound == nullptr)
	{
		LOG("\nCould not load sound correctly! MIX_Error: %s", Mix_GetError());
		return nullptr;
	}
	
	for (int i = 0; i < MAX_SOUNDS; i++) {
		if (sounds[i] != nullptr)
			continue;
		else {
			sounds[i] = sound;
			break;
		}
	}
	
	return sound;
}

Mix_Music* ModuleSound::LoadMusic(const char* path) {
	Mix_Music* mus = Mix_LoadMUS(path);
	
	if (mus == nullptr)
	{
		LOG("\nCould not load music correctly! MIX_Error: %s", Mix_GetError());
		return nullptr;
	}

	for (int i = 0; i < MAX_MUSICS; i++) {
		if (music[i] != nullptr)
			continue;
		else {
			music[i] = mus;
			break;
		}
	}

	return mus;
}

bool ModuleSound::isPlayingMusic() {
	
	return Mix_PlayingMusic() != 0;
}

void ModuleSound::ExecuteOnMusicEnd(void(*func)(void)) {
	Mix_HookMusicFinished(func);
}

void PlayMainMusic() {
	//App->sound->PlayMusic(((ModuleSceneGame*)App->current_scene)->music);
	Mix_HookMusicFinished(nullptr);
};