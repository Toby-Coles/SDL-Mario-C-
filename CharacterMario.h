#pragma once

#ifndef CHARACTER_MARIO_H
#define CHARACTER_MARIO_H


#include "Character.h"
#include "Texture2D.h"


//class Texture2D;

class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterMario();

	void Render() override;

	void Update(float deltaTime, SDL_Event e) override;

	
	bool levelComplete;

	void SetState(CHARACTERSTATES state);

private:

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	float mFrameDelay;
	int mCurrentFrame;

};

#endif // !CHARACTER_MARIO_H
