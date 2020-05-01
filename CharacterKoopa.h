#pragma once

#ifndef KOOPA_ENEMY_H
#define KOOPA_ENEM_H

#include "Character.h"
#include "Texture2D.h"

class KoopaEnemy : public Character
{
public:
	KoopaEnemy(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing, float movementSpeed);
	~KoopaEnemy();
	
	void TakeDamage();
	void Jump();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void SetAlive(bool lifeState);
	bool GetAlive();
	void ChangeDirection();

	enum EnemyStates
	{
		ALIVE = 0,
		DEAD = 1,
		FLIPPED
	}; 

	EnemyStates enemyState;
private:
	

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	//void MoveLeft(float deltaTime) override;
	//void MoveRight(float deltaTime) override;

	bool mInjured;
	float mInjuredTime;

	float mFrameDelay;
	int mCurrentFrame;


	void FlipRightWayUp();
protected:
	float mMovementSpeed;
};

#endif
