#include "Texture2D.h"
#include <SDL_image.h>
#include <iostream>


Texture2D::Texture2D(SDL_Renderer* renderer)
{
	mWidth = 0;
	mHeight = 0;
	mRenderer = renderer;
}

Texture2D::~Texture2D()
{
	Free();
	mRenderer = NULL;
}



bool Texture2D::LoadFromFile(std::string path) {
	Free();

	//Set the dimensions

	// Load the image
	SDL_Surface* pSurface = IMG_Load(path.c_str());

	if (pSurface != NULL)
	{
		mWidth = pSurface->w;
		mHeight = pSurface->h;

		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);


		if (mTexture == NULL)
		{
			std::cout << "Unable to create texture from surface. Error: " << SDL_GetError() << std::endl;

		}
		SDL_FreeSurface(pSurface);

	}

	//Create the texture from the pixels on the surface

	else
	{
		std::cout << "Unable to create texture from surface. Error" << IMG_GetError() << std::endl;

	}

	return mTexture != NULL;

}

void Texture2D::Free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle)
{
	//Set where to render the texture
	SDL_Rect renderLocation = { newPosition.x, newPosition.y, mWidth, mHeight};
	//Render to the screen
	
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, 0, NULL, flip);


}

void Texture2D::Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle)
{
	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, angle, NULL, flip);
}


