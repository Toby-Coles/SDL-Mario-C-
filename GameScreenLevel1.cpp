#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"



GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) {
	coinIndexToDelete = -1;
	koopasAlive = 0;
	Coins = 0;
	coinsToCompletion = 8;
	koopasKilled = 0;
	enemiesToCompletion = 2;
	//levelChangeScreen = SCREEN_LEVEL2;
	deathTimer = 0;
	SetUpLevel();
}

GameScreenLevel1 :: ~GameScreenLevel1()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	delete Mario;
	delete Luigi;
	delete soundEffect;

	Mario = NULL;

	mEnemies.clear();
	delete mPowBlock;
	mPowBlock = NULL;
	mLevelMap = NULL;

	//TTF_CloseFont(multiplayerFont);
}

bool GameScreenLevel1::SetUpLevel()
{
	bgm = new SoundEffects();
	bgm->LoadAndPlayMusic("Audio/MarioUnderworld.mp3");

	soundEffect = new SoundEffects();
	//levelChange = new GameScreenManager();
	//changeLevel = new GameScreenManager(mRenderer, levelChangeScreen);
	

	coinSound = soundEffect->LoadSoundEffect("Audio/coin.wav");
	jumpSound = soundEffect->LoadSoundEffect("Audio/Jump.wav");

	//setup the player character
	SetLevelMap();
	Mario = new CharacterMario(mRenderer, "Images/MarioAnimated.png", Vector2D(64, 330), mLevelMap);
	Luigi = new CharacterLuigi(mRenderer, "Images/LuigiAnimated.png", Vector2D(64, 330), mLevelMap);
	luigiStartIcon = new UIObjects(mRenderer, "Images/mForLuigi.png", Vector2D(200, 20));

	//Set up POW block
	mPowBlock = new PowBlock(mRenderer, mLevelMap, 0, 0);

	//Set Up 2 Enemies
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

	//Set up the coins 

	//Top Left
	CreateCoins(Vector2D(80, 30));
	CreateCoins(Vector2D(110, 30));
	CreateCoins(Vector2D(140, 30));
	CreateCoins(Vector2D(170, 30));

	//Top Right
	CreateCoins(Vector2D(330, 30));
	CreateCoins(Vector2D(360, 30));
	CreateCoins(Vector2D(390, 30));
	CreateCoins(Vector2D(420, 30));

	mScreenShake = false;
	mBackgroundYPos = 0.0f;


	//Load the background Texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture";
		return false;
	}
	return false;
}

void GameScreenLevel1::Render()
{
	mBackgroundTexture->Render(Vector2D(0.0, mBackgroundYPos), SDL_FLIP_NONE);
	mPowBlock->Render();

	Mario->CharacterMario::Render();
	if (Luigi->displayCharacter == false)
	{
		luigiStartIcon->Render();
	}

	if (Luigi->displayCharacter == true)
	{
		Luigi->Render();
	}
	else
	{
		luigiStartIcon->Render();
	}

	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render();
	}

	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Render();
	}
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	if (mScreenShake)
	{
		mScreenShakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

	}
	//End the screen shake after the duration
	if (mScreenShakeTime <= 0.0f)
	{
		mScreenShake = false;
		mBackgroundYPos = 0.0f;

	}

	Mario->Update(deltaTime, e);
	Luigi->Update(deltaTime, e);
	

	UpdatePOWBlock();
	UpdateEnemies(deltaTime, e);

	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Update(deltaTime, e);
		
	}

	UpdateCoins();
	
	if (Mario->mJumping == false)
	{
		marioCancelJumpSound = false;
	}

	if (Mario->mJumping && marioCancelJumpSound == false)
	{
		soundEffect->PlaySoundEffect(jumpSound);
		marioCancelJumpSound = true;
	}

	if (Luigi->mJumping == false)
	{
		luigiCancelJumpSound = false;
	}

	if (Luigi->mJumping && luigiCancelJumpSound == false)
	{

		soundEffect->PlaySoundEffect(jumpSound);
		luigiCancelJumpSound = true;
	}



	//Text on the screen
	
	if (Coins == coinsToCompletion && koopasKilled == enemiesToCompletion)
	{
		Coins = 0;
		koopasKilled = 0;

		levelChangeScreen = SCREEN_LEVEL2;
		//changeLevel->ChangeScreen(levelChangeScreen);
	}

	if (Mario->characterState == CHARACTER_STATE_PLAYER_DEAD)
	{
	

		deathTimer += 0.0017;
		
		if (deathTimer >= 6)
		{
			std::cout << "Death timer met" << std::endl;
			deathTimer = 0;
			levelChangeScreen = SCREEN_LEVEL1;
		}
	}

}

void GameScreenLevel1::UpdatePOWBlock()
{
	
	if (Collisions::Instance()->Box(mPowBlock->GetCollisionBox(), Mario->GetCollisionBox()) || Collisions::Instance()->Box(mPowBlock->GetCollisionBox(), Luigi->GetCollisionBox()))
	{
		std::cout << "Pow Collision Registered" << std::endl;
		if (Mario->mJumping == true)
		{
			DoScreenShake();
			mPowBlock->TakeAHit();
			Mario->CancelJump();
		}
		else if (Luigi->mJumping == true)
		{
			DoScreenShake();
			mPowBlock->TakeAHit();
			Luigi->CancelJump();
		}
	}

}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	int enemyIndexToDelete = -1;
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		if (mEnemies[i]->GetPosition().x <(float)(-mEnemies[i]->GetCollisionBox().width*0.5f) || mEnemies[i]->GetPosition().x > SCREEN_WIDTH-(float)(mEnemies[i]->GetCollisionBox().width*0.55f))
		{
			mEnemies[i]->SetAlive(false);
			std::cout << "Enemy detected off screen" << std::endl;
			koopasAlive = koopasAlive - 1;

		}

		//do the update
		mEnemies[i]->Update(deltaTime, e);

		//Checks if the enemy collides with the player
		if ((mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f) && (mEnemies[i]->GetPosition().x < 64.0f || mEnemies[i] ->GetPosition().x > SCREEN_WIDTH-96.0f))
		{
			
			
		}

		else
		{
		
			if (Collisions::Instance()->Circle(mEnemies[i], Mario) && Mario->characterState == CHARACTERSTATE_PLAYER_ALIVE && mEnemies[i]->enemyState == 0)
			{
				std::cout << "MARIO INJURED" << std::endl;
				Mario->SetState(CHARACTER_STATE_PLAYER_DEAD);
				
			}
			if (Collisions::Instance()->Circle(mEnemies[i], Luigi) && Luigi->characterState == CHARACTERSTATE_PLAYER_ALIVE && mEnemies[i]->enemyState == 0)
			{
				std::cout << "LUIGI INJURED" << std::endl;
				Luigi->SetState(CHARACTER_STATE_PLAYER_DEAD);

			}

			if (Collisions::Instance()->Circle(mEnemies[i], Mario) && mEnemies[i]->enemyState == 2 || Collisions::Instance()->Circle(mEnemies[i], Luigi) && mEnemies[i]->enemyState == 2)
			{
			
				if (mEnemies[i]->GetAlive())
				{
					mEnemies[i]->SetAlive(false);
					
				}
				
			}
		}
		
		

		//if the enemy is no longer alive, then schedule it for deletion
		if (!mEnemies[i]->GetAlive())
		{
			enemyIndexToDelete = i;
		}
	}

	if (enemyIndexToDelete != -1)
	{
		koopasKilled++;
		mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
	}

	
}



void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	Koopa = new KoopaEnemy(mRenderer, "Images/Koopa.png", mLevelMap, Vector2D(position.x, position.y), direction, speed );
	koopasAlive++; 
	mEnemies.push_back(Koopa);

}

void GameScreenLevel1::CreateCoins(Vector2D position)
{
	Coin = new CoinObject(mRenderer, "Images/Coin.png", mLevelMap, Vector2D(position.x, position.y));
	
	mCoins.push_back(Coin);
}

void GameScreenLevel1::UpdateCoins()
{
	if (coinIndexToDelete !=-1)
	{
		mCoins.erase(mCoins.begin() + coinIndexToDelete);
		coinIndexToDelete = -1;
	}
	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		
		if (Collisions::Instance()->Box(mCoins[i]->GetCollisionBox(), Mario->GetCollisionBox()) || Collisions::Instance()->Box(mCoins[i]->GetCollisionBox(), Luigi->GetCollisionBox()))
		{
			std::cout << "Coin Collision";
			
			
			soundEffect->PlaySoundEffect(coinSound);

			coinIndexToDelete = i;
			Coins++;
			std::cout << "Coins = "  << Coins;
		}
	}


}
void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,5,0,0,0,0,0,0,0,0,5,0,0,0},
		{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	
//Clear up any old map
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}

	//Set up the new one
	mLevelMap = new LevelMap(map);
}

void GameScreenLevel1::DoScreenShake()
{
	mScreenShake = true;
	mScreenShakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;

	for (int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->TakeDamage();
	}
}
