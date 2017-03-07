#include <stdlib.h>
#include <stdio.h>
#include "SDL/include/SDL.h"

#pragma comment( lib, "SDL/libx86/SDL2.lib")
#pragma comment( lib, "SDL/libx86/SDL2main.lib")

#define MAX_BULLET_AMOUNT 10

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *window;
	SDL_Renderer *renderer;

	window = SDL_CreateWindow("MyWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	SDL_Surface* Spaceship = SDL_LoadBMP("images/spaceship.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, Spaceship);
	SDL_Surface* Shot = SDL_LoadBMP("images/shot.bmp");
	SDL_Texture* shottexture = SDL_CreateTextureFromSurface(renderer, Shot);
	SDL_Surface* background = SDL_LoadBMP("images/background.bmp");
	SDL_Texture* background_texture = SDL_CreateTextureFromSurface(renderer, background);

	
	SDL_Rect background_1;
	background_1.h = 480;
	background_1.w = 510;
	background_1.x = 0;
	background_1.y = 0;

	SDL_Rect background_2;
	background_2.h = 480;
	background_2.w = 510;
	background_2.x = 511;
	background_2.y = 0;

	SDL_Rect texture_rect;
	texture_rect.x = 279;
	texture_rect.y = 190;
	texture_rect.w = 50;
	texture_rect.h = 50;


	SDL_Rect shot[MAX_BULLET_AMOUNT];
	for (int i = 0; i < MAX_BULLET_AMOUNT; i++)
	{
		shot[i].h = 11;
		shot[i].w = 25;
		shot[i].x = 511;
		shot[i].y = 481;
	}
	

	bool shooting = false;
	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;

	bool exit = false;

	while (!exit)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYUP)
			{
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_LEFT: left = false;		break;
				case SDL_SCANCODE_RIGHT: right = false;		break;
				case SDL_SCANCODE_UP: up = false;			break;
				case SDL_SCANCODE_DOWN: down = false;		break;
				case SDL_SCANCODE_SPACE: shooting = false;	break;
				}
			}

			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE: exit = true;		break;
				case SDL_SCANCODE_LEFT: left = true;		break;
				case SDL_SCANCODE_RIGHT: right = true;		break;
				case SDL_SCANCODE_UP: up = true;			break;
				case SDL_SCANCODE_DOWN: down = true;		break;
				case SDL_SCANCODE_SPACE: shooting = true;	break;
				}
			}

		}

		for (int i = 0; i < MAX_BULLET_AMOUNT; i++)
		{
			shot[i].x += 10;
		}
		
		if (left == true)
		{
			texture_rect.x -= 10;
		}

		if (right == true)
		{
			texture_rect.x += 10;
		}

		if (up == true)
		{
			texture_rect.y -= 10;
		}

		if (down == true)
		{
			texture_rect.y += 10;
		}

		if (shooting == true)
		{
			for (int i = 0; i < MAX_BULLET_AMOUNT; i++)
			{
				shot[i].x = texture_rect.x + 50;
				shot[i].y = texture_rect.y + 20;
			}
			
		}

		background_1.x -= 5;
		background_2.x -= 5;

		if (background_1.x <= -510)
		{
			background_1.x = 510;
		}

		if (background_2.x <= -510)
		{
			background_2.x = 510;
		}

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, background_texture, NULL, &background_1);
		SDL_RenderCopy(renderer, background_texture, NULL, &background_2);
		SDL_RenderCopy(renderer, texture, NULL, &texture_rect);
		SDL_RenderCopy(renderer, shottexture, NULL, shot);
		SDL_RenderPresent(renderer);

	}


	SDL_Quit();
	return(0);
}