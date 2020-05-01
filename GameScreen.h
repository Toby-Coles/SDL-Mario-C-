#pragma once
#include "SDL.h"
#include "Texture2D.h"
#include "GameScreenManager.h"

class GameScreen
{
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	SCREENS ScreenChange() { return levelChangeScreen; }

private:
	
protected:
	SDL_Renderer* mRenderer;
	//GameScreenManager* levelChange;
	SCREENS levelChangeScreen;
	int Coins;
	int coinsToCompletion;
	int enemiesToCompletion;
	int koopasKilled;
	float deathTimer;

	//GameScreenManager* changeLevel;


};

struct MapObjects
{
	SDL_Rect destRect;
	Texture2D* texture;
	

};

