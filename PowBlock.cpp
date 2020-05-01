#include "PowBlock.h"
#include <iostream>

PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* levelMap, int startPositionX, int startPositionY)
{
	std::string imagePath = "Images/PowBlock.png";
	mTexture = new Texture2D(renderer);
	if (!mTexture ->LoadFromFile(imagePath.c_str()) )
	{
		std::cout << "Failed to load texture" << imagePath << std::endl;
		return;
	}
	mLevelMap = levelMap;
	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();
	mNumberOfHitsLeft = 3;
	if (startPositionX == 0 && startPositionY == 0)
	{
		mPosition = Vector2D((SCREEN_WIDTH * 0.5f) - mSingleSpriteWidth * 0.5f, 260);
	}
	else
	{
		mPosition.x = startPositionX;
		mPosition.y = startPositionY;
	}
	
}

PowBlock::~PowBlock()
{
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;
	mLevelMap = NULL;
}

void PowBlock::Render()
{
	if (mNumberOfHitsLeft > 0)
	{
		//Get the portion of the spritesheet you want to draw
		int left = mSingleSpriteWidth * (mNumberOfHitsLeft - 1);

		// positions
		SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

		//Determine where you want it drawn
		SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

		//Draw
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
	}
}

Rect2D PowBlock::GetCollisionBox()
{
	return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mTexture->GetHeight());
}

void PowBlock::TakeAHit()
{
	mNumberOfHitsLeft -= 1;

	if (mNumberOfHitsLeft <= 0)
	{
		mNumberOfHitsLeft = 0;

		mLevelMap->ChangeTileAt(7, 7, 0);
		mLevelMap->ChangeTileAt(8, 7, 0);

		mPosition.x = 999;
		mPosition.y = 999;
	}
}
