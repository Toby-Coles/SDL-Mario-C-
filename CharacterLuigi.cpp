#include "CharacterLuigi.h"
#include "Constants.h"
//#include "SDL_ttf.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{
	numberOfFrames = 5;
	//TTF_OpenFont("Test", 22);
	displayCharacter = false;
	isMultiplayer = false;
	characterState = CHARACTERSTATE_PLAYER_ALIVE;
	mSingleSpriteWidth = mTexture->GetWidth() / numberOfFrames;
	mSingleSpriteHeight = mTexture->GetHeight();
	mCurrentFrame = 0;
}

CharacterLuigi::~CharacterLuigi()
{
}

void CharacterLuigi::Render() {

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

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	if (characterState != CHARACTER_STATE_PLAYER_DEAD)
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_m:
				if (isMultiplayer == false)
				{
					isMultiplayer = true;
					std::cout << "Multiplayer state: " << isMultiplayer << std::endl;
				}

				break;

			case SDLK_k:
				if (isMultiplayer == true)
				{
					isMultiplayer = false;
					std::cout << "Multiplayer state: " << isMultiplayer << std::endl;
				}

				break;

			default:
				break;
			}
		default:
			break;
		}

		if (isMultiplayer == true)
		{
			displayCharacter = true;
		}
		else
		{
			displayCharacter = false;
		}

		if (displayCharacter == true)
		{
			switch (e.type)
			{
			case SDL_KEYDOWN:

				switch (e.key.keysym.sym)
				{
				case SDLK_LEFT:
					mMovingLeft = true;

					break;
				case SDLK_RIGHT:
					mMovingRight = true;

					break;
				case SDLK_UP:
					Jump();

				default:
					break;
				}
				break;

			case SDL_KEYUP:
				switch (e.key.keysym.sym)
				{
				case SDLK_LEFT:
					mMovingLeft = false;
					break;
				case SDLK_RIGHT:
					mMovingRight = false;

				default:
					break;
				}
			default:
				break;
			}
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

void CharacterLuigi::SetState(CHARACTERSTATES state)
{
	characterState = state;
}

