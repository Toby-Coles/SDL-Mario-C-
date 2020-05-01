#include "UIObjects.h"

UIObjects::UIObjects(SDL_Renderer* renderer, std::string imagePath, Vector2D position) 
{
	
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	mPosition = position;
	if (!mTexture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load UI texture" << std::endl;
	}
}

UIObjects::~UIObjects()
{
}

void UIObjects::Render()
{
	SDL_Rect portionOfSpriteSheet = { 0,0, mTexture->GetWidth(), mTexture->GetHeight() };
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mTexture->GetWidth(), mTexture->GetHeight()};

	mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE); 
	
}

void UIObjects::Update()
{
}
