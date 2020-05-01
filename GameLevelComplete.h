#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "LevelMap.h"
#include "Collisions.h"
#include "CharacterMario.h"




#include "SoundEffects.h"


class Texture2D;
class Character;

class GameScreenComplete : GameScreen
{
public:
	GameScreenComplete(SDL_Renderer* renderer);
	~GameScreenComplete();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:


	CharacterMario* Mario;
	SoundEffects* bgm;
	SoundEffects* soundEffect;
	Mix_Chunk* jumpSound;
	float mBackgroundYPos;

	Texture2D* mBackgroundTexture;
	bool SetUpEndScreen();
	LevelMap* mLevelMap;
	void SetLevelMap();




};

