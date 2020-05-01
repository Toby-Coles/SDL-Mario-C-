#pragma once
#ifndef COIN_H
#define COIN_H
#include "Character.h"
#include "Texture2D.h"

class CoinObject : public Character
{
public:
	CoinObject (SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D startPosition);
	~CoinObject ();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;


private:

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	float mFrameDelay;
	float mCurrentFrame;



};

#endif