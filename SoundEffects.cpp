#pragma once
#include "SoundEffects.h"
#include <iostream>

void SoundEffects::LoadAndPlayMusic(std::string path) {
	
	gMusic = NULL;

	gMusic = Mix_LoadMUS(path.c_str());
	if (gMusic == NULL)
	{
		std::cout << "Error loading background music, error: " << Mix_GetError() << std::endl;
	}
	else
	{
		std::cout << "Background music loaded successfully" << std::endl;
	}

	if (!Mix_PlayingMusic())
	{
		Mix_PlayMusic(gMusic, -1);
	}


}

Mix_Chunk* SoundEffects::LoadSoundEffect(std::string path)
{
	gSoundEffect = NULL;

	Mix_Chunk* gSoundEffect = Mix_LoadWAV(path.c_str());

	if (gSoundEffect == NULL)
	{
		std::cout << "Error loading sound effect, error: " << Mix_GetError() << std::endl;
	
	}
	else
	{
		std::cout << "Sound effect loaded successfully" << std::endl;
	}

	return gSoundEffect;
}

void SoundEffects::PlaySoundEffect(Mix_Chunk* sound)
{
	Mix_PlayChannel(-1, sound, 0);

}



SoundEffects::SoundEffects()
{
	gMusic = NULL;
	gSoundEffect = NULL;
}

SoundEffects::~SoundEffects()
{
	Mix_FreeMusic(gMusic);
	gMusic = NULL;
}