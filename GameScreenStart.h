#pragma once
#ifndef GAME_SCREEN_START_H
#define GAME_SCREEN_START_H

#include "GameScreen.h"
#include <vector>
#include "CharacterMario.h"
#include "CharacterLuigi.h"

#include <vector>
#include "CharacterCoin.h"
#include "SoundEffects.h"

class Texture2D;
class Character;

class GameScreenStart : GameScreen
{
public:
	GameScreenStart(SDL_Renderer* renderer);
	~GameScreenStart();


	void Render();
	void Update(float deltaTime, SDL_Event e);
	void UpdateCoins();
	void CreateCoins(Vector2D position);

	bool marioCancelJumpSound;
	bool luigiCancelJumpSound;

private:

	CharacterMario* Mario;
	CharacterLuigi* Luigi;

	CoinObject* Coin;
	std::vector<CoinObject*> mCoins;

	Mix_Chunk* jumpSound;
	SoundEffects* bgm;
	SoundEffects* soundEffect;

	Mix_Chunk* coinSound;

	Texture2D* mBackgroundTexture;
	bool SetUpStartScreen();

	void SetLevelMap();
	LevelMap* mLevelMap;
	int coinIndexToDelete;

	float mBackgroundYPos;
	
};






#endif