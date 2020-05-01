#pragma once
#include "SDL_mixer.h"
#include <string>

class SoundEffects
{
public:
	SoundEffects();
	~SoundEffects();

	void LoadAndPlayMusic(std::string path);
	Mix_Chunk* LoadSoundEffect(std::string path);
	void PlaySoundEffect(Mix_Chunk* sound);

private:

protected:
	Mix_Music* gMusic;
	Mix_Chunk* gSoundEffect;
};

