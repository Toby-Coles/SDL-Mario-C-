#include "CharacterKoopa.h"




KoopaEnemy::KoopaEnemy(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing, float movementSpeed)
    : Character(renderer, imagePath, startPosition, map)
{
    mFacingDirection = startFacing;
    mMovementSpeed = movementSpeed;

    mPosition = startPosition;
    mInjured = false;
    numberOfFrames = 4;
    mSingleSpriteWidth = mTexture->GetWidth() / numberOfFrames;
    mSingleSpriteHeight = mTexture->GetHeight();
    mFacingDirection = startFacing;
    mCurrentFrame = 0;
}

KoopaEnemy::~KoopaEnemy()
{
}



void KoopaEnemy::Jump()
{
    if (!mJumping)
    {
        mJumpForce = INITIAL_JUMP_FORCE_SMALL;
        mJumping = true;
        mCanJump = false;

    }
}

void KoopaEnemy::Render()
{
    //Holds the position of the left sprite
    

    //if injured, move the left positon to be the left position of the second image of the spritesheet
    if (mInjured)
    {
        int left = 0.0f;
    }
    int left = mSingleSpriteWidth * mCurrentFrame;

    SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

    //Determine where you want it to be drawn
    SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

    // then draw it facing the right direction
    if (mFacingDirection == FACING_RIGHT)
    {
        mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
    }
    else
    {
        mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_HORIZONTAL);
    }
    
}

void KoopaEnemy::Update(float deltaTime, SDL_Event e)
{
    if (!mInjured)
    {
        mFrameDelay -= deltaTime;
        if (mFrameDelay <= 0.0f)
        {
            mFrameDelay = ANIMATION_DELAY;

            mCurrentFrame++;
            if (mCurrentFrame > 2)
            {
                mCurrentFrame = 0;
            }

        }
    }
    
    Character::Update(deltaTime, e);


    float newPositionX = GetPosition().x;
    float newPositionY = GetPosition().y;

    int leftPosition = (int)newPositionX / TILE_WIDTH;
    int rightPosition = (int)(newPositionX + (mTexture->GetWidth() / numberOfFrames)) / TILE_WIDTH;
    int footPosition = (int)(newPositionY + mTexture->GetHeight()) / TILE_HEIGHT;
    int headPosition = (int)newPositionY / TILE_HEIGHT;



    int topLeftTile = mCurrentLevelMap->GetTileAt(headPosition, leftPosition);
    int topRightTile = mCurrentLevelMap->GetTileAt(headPosition, rightPosition);
    int midLeftTile = mCurrentLevelMap->GetTileAt(footPosition - 1, leftPosition);
    int midRightTile = mCurrentLevelMap->GetTileAt(footPosition - 1, rightPosition);
    int bottomLeftTile = mCurrentLevelMap->GetTileAt(footPosition, leftPosition);
    int bottomrightTile = mCurrentLevelMap->GetTileAt(footPosition, rightPosition);

 
    if (midRightTile == 5 && mMovingRight == true)
    {
        std::cout << "Koopa Collision Detected " << std::endl;
        ChangeDirection();
    }
    else if (midLeftTile == 5 && mMovingLeft == true)
    {
        ChangeDirection();
    }


 

    //Deals with if the koopa is injured or not
    if (!mInjured)
    {
        if (mFacingDirection == FACING_LEFT)
        {
            mMovingLeft = true;
            //MoveLeft(deltaTime);
            mMovingRight = false;

        }
        else if (mFacingDirection == FACING_RIGHT)
        {
            mMovingRight = true;
           // MoveRight(deltaTime);
            mMovingLeft = false;

        }

    }
    else
    {
        enemyState = FLIPPED;
        mMovingRight = false;
        mMovingLeft = false;
        mCurrentFrame = 3;
        mInjuredTime -= deltaTime;
        if (mInjuredTime <= 0.0)
        {
            enemyState = ALIVE;
            FlipRightWayUp();
        }
    }
   
}

void KoopaEnemy::SetAlive(bool lifeState)
{
    if (lifeState == false)
    {
        enemyState = DEAD;
    }
    else
    {
        enemyState = ALIVE;
    }
}

bool KoopaEnemy::GetAlive()
{
    if (enemyState == DEAD)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void KoopaEnemy::ChangeDirection()
{
    if (mMovingRight == true)
    {
        mFacingDirection = FACING_LEFT;
        mMovingLeft = true;
    }
    else if (mMovingLeft == true)
    {
        mFacingDirection = FACING_RIGHT;
        mMovingRight = true;
    }
    
}

void KoopaEnemy::TakeDamage()
{
    mInjured = true;
    mInjuredTime = INJURED_TIME;
    
    Jump();

}

void KoopaEnemy::FlipRightWayUp()
{
    mFacingDirection = FACING_UP;
    mInjured = false;
    Jump();

    int restartDirection;

    restartDirection = rand() % 2;
    std::cout << restartDirection << std::endl;
    
    if (restartDirection == 0)
    {
        mFacingDirection = FACING_LEFT;
    }
    else if (restartDirection == 1)
    {
        mFacingDirection = FACING_RIGHT;
    }
}
