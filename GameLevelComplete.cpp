#include "GameLevelComplete.h"



GameScreenComplete::GameScreenComplete(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpEndScreen();
}

GameScreenComplete::~GameScreenComplete()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	delete Mario;

	delete soundEffect;

	Mario = NULL;


	mLevelMap = NULL;
}

bool GameScreenComplete::SetUpEndScreen()
{
	bgm = new SoundEffects();
	bgm->LoadAndPlayMusic("Audio/MarioUnderworld.mp3");

	soundEffect = new SoundEffects();
	
	SetLevelMap();
	Mario = new CharacterMario(mRenderer, "Images/MarioAnimated.png", Vector2D(64, 330), mLevelMap);

	mBackgroundYPos = 0.0f;
	jumpSound = soundEffect->LoadSoundEffect("Audio/Jump.wav");

	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/EndScreen.png"))
	{
		std::cout << "Failed to load background texture";
		return false;
	}
	return false;
}

void GameScreenComplete::Render()
{
	mBackgroundTexture->Render(Vector2D(0.0, mBackgroundYPos), SDL_FLIP_NONE);


	Mario->CharacterMario::Render();
}

void GameScreenComplete::Update(float deltaTime, SDL_Event e)
{
	Mario->Update(deltaTime, e);
}



void GameScreenComplete::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
