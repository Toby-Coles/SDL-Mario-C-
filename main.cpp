#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
//#include <SDL_ttf.h>

#include "Constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"
//#include <SDL_ttf.h>

GameScreenManager* gameScreenManager;
Uint32 gOldTime;

using namespace::std;
SDL_Renderer* gRenderer = NULL;


bool InitSDL();
void CloseSDL();
bool update();

//Rendering Functions
void Render();

//Globals
SDL_Window* gWindow = NULL;


int main(int argc, char* args[]) {

	//Checks if SDL was set up correctly
	bool quit = false;
	InitSDL();

	while (!quit)
	{
		Render();
		quit = update();
	}
	//Close window and free resources
	CloseSDL();

	return 0;
}

bool update() {
	//Get the new time
	Uint32 newTime = SDL_GetTicks();
	//Event handler
	SDL_Event e;

	//Get the events
	SDL_PollEvent(&e);

	switch (e.type)
	{
		//Click the 'X' to quit
		case SDL_QUIT:
		return true;
		break;
	}
	
	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);
	gOldTime = newTime;
	return false;
}

bool InitSDL() {

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		cout << "SDL did not initialise: Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//initialise audio
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			std::cout << "Error initialising audio: " << Mix_GetError() << std::endl;
		}

		//As all is well, an attempt can be made to create the window
		gWindow = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		
		
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);


		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_MENU);
		gOldTime = SDL_GetTicks();
		//TTF_Init();

		//Did the window get created?
		if (gWindow == NULL)
		{
			//Nope
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}

		else
		{
		
			return true;
		}
	
	}

	if (gRenderer != NULL)
	{
		//initialise PNG Loading
		int imageFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imageFlags) & imageFlags))
		{
			cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
		}
		else
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}
	}
	
	

}

void CloseSDL() {
	//Release the window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	delete gameScreenManager;
	gameScreenManager = NULL;

	//Release the renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	//TTF_Quit();
	IMG_Quit();
	SDL_Quit();

}

void Render() {
	//Clear the screen
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);
	gameScreenManager->Render();

	
	//update the screen
	SDL_RenderPresent(gRenderer);
	
}



