#include "CharacterMario.h"
#include "Constants.h"
//#include "SDL_ttf.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{
	//TTF_OpenFont("Test", 22);
	numberOfFrames = 5;

	characterState = CHARACTERSTATE_PLAYER_ALIVE;
	mSingleSpriteWidth = mTexture->GetWidth() / numberOfFrames; 
	mSingleSpriteHeight = mTexture->GetHeight();
	mCurrentFrame = 0;
	
}

CharacterMario::~CharacterMario()
{
}

void CharacterMario::Render() {

	int left = mSingleSpriteWidth * mCurrentFrame;

	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);

	}
	else
	{
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_HORIZONTAL);

	}
}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	//Keyboard Inputs
	if (characterState != CHARACTER_STATE_PLAYER_DEAD)
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:

			switch (e.key.keysym.sym)
			{
			case SDLK_a:
				mMovingLeft = true;

				break;
			case SDLK_d:
				mMovingRight = true;

				break;
			case SDLK_SPACE:
				Jump();
				break;
			case SDLK_x:
				SDL_Quit();
			default:
				break;
			}
			break;

		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
			case SDLK_a:
				mMovingLeft = false;
				break;
			case SDLK_d:
				mMovingRight = false;

			default:
				break;
			}
		default:
			break;
		}
	}

		if (mMovingLeft || mMovingRight && characterState == CHARACTERSTATE_PLAYER_ALIVE)
		{
			mFrameDelay -= deltaTime;
			if (mFrameDelay <= 0)
			{
				mFrameDelay = ANIMATION_DELAY;

				mCurrentFrame++;
				if (mCurrentFrame > 2)
				{
					mCurrentFrame = 0;
				}

			}
		}
		else
		{
			mCurrentFrame = 0;
		}

		if (characterState == CHARACTER_STATE_PLAYER_DEAD)
		{
			mCurrentFrame = 4;

		}
		
	
	
	
	Character::Update(deltaTime, e);
}

void CharacterMario::SetState(CHARACTERSTATES state)
{
	characterState = state;
}

