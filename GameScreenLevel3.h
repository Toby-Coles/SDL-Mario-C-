#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "LevelMap.h"
#include "Collisions.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
#include <vector>
#include "CharacterCoin.h"
#include "SoundEffects.h"
#include "UIObjects.h"
//#include "GameSCreenManager.h"

#include <SDL_ttf.h>


class Texture2D;
class Character;
class PowBlock;


class GameScreenLevel3 : GameScreen
{
public:
	GameScreenLevel3(SDL_Renderer* renderer);
	~GameScreenLevel3();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void UpdatePOWBlock();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void UpdateCoins();
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateCoins(Vector2D position);
	bool marioCancelJumpSound;
	bool luigiCancelJumpSound;
private:

	PowBlock* mPowBlock;

	//Character* myCharacter;

	CharacterMario* Mario;
	CharacterLuigi* Luigi;

	//KoopaEnemy* Koopa;
	//CoinObject* Coin;
	int coinIndexToDelete;

	int koopasAlive;

	std::vector<KoopaEnemy*> mEnemies;
	std::vector<CoinObject*> mCoins;

	SoundEffects* bgm;
	SoundEffects* soundEffect;
	Mix_Chunk* coinSound;
	Mix_Chunk* jumpSound;

	//std::vector<SoundEffects*> soundEffects;

	Texture2D* mBackgroundTexture;
	bool SetUpLevel3();

	void SetLevelMap();
	LevelMap* mLevelMap;
	UIObjects* luigiStartIcon;

	//Screen shake functionalit
	float mWobble;
	bool mScreenShake;
	float mScreenShakeTime;
	float mBackgroundYPos;

	void DoScreenShake();


	// GameText
	//TTF_Font* multiplayerFont = TTF_OpenFont("arial.ttf", 25);
	//SDL_Color fontColor;
};



