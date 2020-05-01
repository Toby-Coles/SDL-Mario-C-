#pragma once
#ifndef _POW_BLOCK_H
#define _POW_BLOCK_H
#include <SDL.h>

#include "LevelMap.h"
//#include "Commons.h"
#include "Texture2D.h"
#include "Collisions.h"
class Texture2D;
class LevelMap;


class PowBlock
{
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* levelMap, int startPositionX, int startPositionY);
	~PowBlock();

	void Render();
	Rect2D GetCollisionBox();
	void TakeAHit();

	//bool IsAvailable() {
	//	return mNumberOfHitsLeft > 0;
	//}
	//	
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

private:

	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mLevelMap;



	int mNumberOfHitsLeft;

};

#endif