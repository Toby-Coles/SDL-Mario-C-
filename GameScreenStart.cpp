#include "GameScreenStart.h"

GameScreenStart::GameScreenStart(SDL_Renderer* renderer) : GameScreen(renderer)
{
	coinIndexToDelete = -1;
	
	Coins = 0;
	coinsToCompletion = 1;

	
	
	SetUpStartScreen();
}

GameScreenStart::~GameScreenStart()
{

}


bool GameScreenStart::SetUpStartScreen()
{
	bgm = new SoundEffects();
	bgm->LoadAndPlayMusic("Audio/MarioUnderworld.mp3");

	soundEffect = new SoundEffects();
	coinSound = soundEffect->LoadSoundEffect("Audio/coin.wav");
	jumpSound = soundEffect->LoadSoundEffect("Audio/Jump.wav");

	SetLevelMap();
	Mario = new CharacterMario(mRenderer, "Images/MarioAnimated.png", Vector2D(64, 330), mLevelMap);
	Luigi = new CharacterLuigi(mRenderer, "Images/LuigiAnimated.png", Vector2D(64, 330), mLevelMap);

	CreateCoins(Vector2D(420, 340));

	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/StartScreen.png"))
	{
		std::cout << "Failed to load background texture";
		return false;
	}
	mBackgroundYPos = 0.0f;

	return false;
}

void GameScreenStart::Render()
{
	mBackgroundTexture->Render(Vector2D(0.0, mBackgroundYPos), SDL_FLIP_NONE);
	

	Mario->CharacterMario::Render();
	

	


	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Render();
	}
}

void GameScreenStart::Update(float deltaTime, SDL_Event e)
{
	Mario->Update(deltaTime, e);
	Luigi->Update(deltaTime, e);

	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Update(deltaTime, e);

	}

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
	UpdateCoins();

	if (Coins == coinsToCompletion)
	{
		Coins = 0;
		levelChangeScreen = SCREEN_LEVEL1;
	}


}

void GameScreenStart::UpdateCoins()
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
			std::cout << "Coins = " << Coins;
		}
	}
}

void GameScreenStart::CreateCoins(Vector2D position)
{
	Coin = new CoinObject(mRenderer, "Images/Coin.png", mLevelMap, Vector2D(position.x, position.y));

	mCoins.push_back(Coin);
}



void GameScreenStart::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,5,0,0,0,0,0,0,0,0,5,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
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
