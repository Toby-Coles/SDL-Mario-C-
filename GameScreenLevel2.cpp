#include "GameScreenLevel2.h"

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer) : GameScreen(renderer)
{
	coinIndexToDelete = -1;
	koopasAlive = 0;
	Coins = 0;
	coinsToCompletion = 8;
	koopasKilled = 0;
	enemiesToCompletion = 2;
	//levelChangeScreen = SCREEN_LEVEL2;
	deathTimer = 0;
	SetUpLevel2();
}

GameScreenLevel2::~GameScreenLevel2()
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
}

bool GameScreenLevel2::SetUpLevel2()
{
	bgm = new SoundEffects();
	bgm->LoadAndPlayMusic("Audio/MarioUnderworld.mp3");

	soundEffect = new SoundEffects();

	coinSound = soundEffect->LoadSoundEffect("Audio/coin.wav");
	jumpSound = soundEffect->LoadSoundEffect("Audio/Jump.wav");


	SetLevelMap();

	//setup the player character
	Mario = new CharacterMario(mRenderer, "Images/MarioAnimated.png", Vector2D(64, 330), mLevelMap);
	Luigi = new CharacterLuigi(mRenderer, "Images/LuigiAnimated.png", Vector2D(64, 330), mLevelMap);
	
	luigiStartIcon = new UIObjects(mRenderer, "Images/mForLuigi.png", Vector2D(200, 20));

	//Setup POW Block
	mPowBlock = new PowBlock(mRenderer, mLevelMap, 180, 250);
	 

	// Set up Enemy
	CreateKoopa(Vector2D(70, 40), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(400, 330), FACING_LEFT, KOOPA_SPEED);

	//Set up coins
	CreateCoins(Vector2D(100, 60));
	CreateCoins(Vector2D(70, 60));
	CreateCoins(Vector2D(40, 60));

	CreateCoins(Vector2D(200, 40));
	CreateCoins(Vector2D(325, 35));
	CreateCoins(Vector2D(355, 35));
	CreateCoins(Vector2D(385, 35));
	CreateCoins(Vector2D(415, 35));

	mScreenShake = false;
	mBackgroundYPos = 0.0f;

	//Load the background texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundLevel2.png"))
	{
		std::cout << " Failed to load background Texture" << std::endl;
		return false;
	}

	return false;
}

void GameScreenLevel2::Render()
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

	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render();
	}

	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Render();
	}
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
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


	if (Coins == coinsToCompletion && koopasKilled == enemiesToCompletion)
	{
		Coins = 0;
		koopasKilled = 0;

		levelChangeScreen = SCREEN_LEVEL3;
		//changeLevel->ChangeScreen(levelChangeScreen);
	}


	if (Mario->characterState == CHARACTER_STATE_PLAYER_DEAD)
	{


	
		std::cout << deathTimer << std::endl;
		if (deathTimer >= 6)
		{
			std::cout << "Death timer met" << std::endl;
			deathTimer = 0;
			levelChangeScreen = SCREEN_LEVEL2;
		}
	}




}

void GameScreenLevel2::UpdatePOWBlock()
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

void GameScreenLevel2::UpdateEnemies(float deltaTime, SDL_Event e)
{

	int enemyIndexToDelete = -1;
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		if (mEnemies[i]->GetPosition().x <(float)(-mEnemies[i]->GetCollisionBox().width * 0.5f) || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().width * 0.55f))
		{
			mEnemies[i]->SetAlive(false);
			std::cout << "Enemy detected off screen" << std::endl;
			koopasAlive = koopasAlive - 1;

		}

		//do the update
		mEnemies[i]->Update(deltaTime, e);

		//Checks if the enemy collides with the player
		if ((mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f) && (mEnemies[i]->GetPosition().x < 64.0f || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
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

void GameScreenLevel2::UpdateCoins()
{
	if (coinIndexToDelete != -1)
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
		}
	}
}

void GameScreenLevel2::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	KoopaEnemy* Koopa = new KoopaEnemy(mRenderer, "Images/Koopa.png", mLevelMap, Vector2D(position.x, position.y), direction, speed);
	koopasAlive++;
	mEnemies.push_back(Koopa);
}

void GameScreenLevel2::CreateCoins(Vector2D position)
{
	CoinObject* Coin = new CoinObject(mRenderer, "Images/Coin.png", mLevelMap, Vector2D(position.x, position.y));

	mCoins.push_back(Coin);
}



void GameScreenLevel2::SetLevelMap()
{

	int map[MAP_HEIGHT][MAP_WIDTH] = {
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{5,0,0,0,5,0,0,0,0,0,1,1,1,1,1,1},
		{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,1,0,0,0,0,1,1,1,1},
		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,1,0,0,0,0,0,5,1,1},
		{1,1,0,0,0,0,0,1,5,0,0,0,0,5,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}

	//Set up the new one
	mLevelMap = new LevelMap(map);
}

void GameScreenLevel2::DoScreenShake()
{
	mScreenShake = true;
	mScreenShakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;

	for (int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->TakeDamage();
	}
}
