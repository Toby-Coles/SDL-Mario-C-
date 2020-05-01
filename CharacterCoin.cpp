#include "CharacterCoin.h"

CoinObject::CoinObject(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D startPosition) : Character(renderer, imagePath, startPosition, map)
{
    numberOfFrames = 3;
	mPosition = startPosition;
    mFrameDelay = 0.25f;
    mCurrentFrame = 0;
	mSingleSpriteWidth = mTexture->GetWidth() / numberOfFrames;
	mSingleSpriteHeight = mTexture->GetHeight();
}

CoinObject::~CoinObject()
{
}

void CoinObject::Render()
{
   

    //Holds the position of the left sprite
    int left = 0.0f;
    SDL_Rect portionOfSpriteSheet = { mSingleSpriteWidth * mCurrentFrame, 0, mSingleSpriteWidth, mSingleSpriteHeight };

   
    
    //SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

    //Determine where you want it to be drawn
    SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

    mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
}

void CoinObject::Update(float deltaTime, SDL_Event e)
{
    //Character::Update(deltaTime, e);

    mFrameDelay -= deltaTime;
    if (mFrameDelay <= 0.0f)
    {
        mFrameDelay = ANIMATION_DELAY;

        mCurrentFrame++;
        if (mCurrentFrame > 2)
        {
            mCurrentFrame = 0;
        }
    }

   

}

