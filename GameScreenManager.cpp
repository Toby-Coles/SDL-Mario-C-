#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameScreenLevel3.h"
#include "GameScreenStart.h"
#include "GameScreenManager.h"
#include "SDL.h"
#include "GameLevelComplete.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	mRenderer = renderer;
	mCurrentScreen = NULL;
	//Ensure the start screen is set up
	ChangeScreen(startScreen);


}



GameScreenManager::~GameScreenManager()
{
	mRenderer = NULL;
	delete mCurrentScreen;
	mCurrentScreen = NULL;

}

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);

	if (mCurrentScreen->ScreenChange() != NULL)
	{
		ChangeScreen(mCurrentScreen->ScreenChange());
	}
}

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}
	
	GameScreenStart* tempScreenStart;
	GameScreenLevel1* tempScreen;
	GameScreenLevel2* tempScreen2;
	GameScreenLevel3* tempScreen3;
	GameScreenComplete* tempScreenEnd;

	switch (newScreen)
	{
	case SCREEN_INTRO:
		break;
	case SCREEN_MENU:
		tempScreenStart = new GameScreenStart(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreenStart;
		tempScreenStart = NULL;
		break;
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen;
		//tempScreen2 = new GameScreenLevel2(mRenderer);
		//mCurrentScreen = (GameScreen*)tempScreen2;
		tempScreen = NULL;

		break;
	case SCREEN_LEVEL2:
		
		tempScreen2 = new GameScreenLevel2(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen2;
		std::cout << "Level 2 Loading" << std::endl;
		tempScreen2 = NULL;
		break;
	case SCREEN_LEVEL3:
			tempScreen3 = new GameScreenLevel3(mRenderer);
			mCurrentScreen = (GameScreen*)tempScreen3;
			tempScreen3 = NULL;
			break;

	case SCREEN_GAMEOVER:
		tempScreenEnd = new GameScreenComplete(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreenEnd;
		tempScreenEnd = NULL;
		break;
	case SCREEN_HIGHSCORES:
		break;
	default:
		break;
	}
}

