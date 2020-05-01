#pragma once
#include "Character.h"
#include "Texture2D.h"

//class Texture2D;

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterLuigi();

	void Update(float deltaTime, SDL_Event e) override;

	void Render() override;

	
	CHARACTERSTATES characterState;
	void SetState(CHARACTERSTATES state);

	bool displayCharacter;
	
private:
	bool isMultiplayer;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	float mFrameDelay;
	int mCurrentFrame;
	
};