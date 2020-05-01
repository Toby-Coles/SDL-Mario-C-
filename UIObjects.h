#pragma once
#ifndef UI_OBJECTS_H
#define UI_OBJECTS_H

#include "Texture2D.h"
#include "Character.h"


class UIObjects
{
public:
	UIObjects(SDL_Renderer* renderer, std::string imagePath, Vector2D position); 
	~UIObjects();

	void Render();
	void Update();
private:

	UIObjects* joinJuigi; 

	Texture2D* mTexture;
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
};

#endif