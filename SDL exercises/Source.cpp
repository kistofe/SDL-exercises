#include <stdlib.h>
#include <stdio.h>
#include "SDL/include/SDL.h"
#include "SDL Image/include/SDL_image.h"

#pragma comment( lib, "SDL/libx86/SDL2.lib")
#pragma comment( lib, "SDL/libx86/SDL2main.lib")
#pragma comment( lib, "SDL image/libx86/SDL2_image.lib")

#define MAX_BULLET_AMOUNT 10

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_Window *window;
	SDL_Renderer *renderer;

	window = SDL_CreateWindow("MyWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	SDL_Surface* Spaceship = IMG_Load("images/spritesheet.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, Spaceship);

	SDL_Surface* Shot = SDL_LoadBMP("images/shot.bmp");
	SDL_Texture* shottexture = SDL_CreateTextureFromSurface(renderer, Shot);

	SDL_Surface* background = SDL_LoadBMP("images/background.bmp");
	SDL_Texture* background_texture = SDL_CreateTextureFromSurface(renderer, background);

	int bullets = MAX_BULLET_AMOUNT;
	
	SDL_Rect background_1;
	background_1.h = 480;
	background_1.w = 1020;
	background_1.x = 0;
	background_1.y = 0;

	SDL_Rect background_2;
	background_2.h = 480;
	background_2.w = 1020;
	background_2.x = 1020;
	background_2.y = 0;

	SDL_Rect texture_rect;
	texture_rect.x = 279;
	texture_rect.y = 190;
	texture_rect.w = 50;
	texture_rect.h = 46;

	SDL_Rect spriterect;
	spriterect.x = 37;
	spriterect.y = 0;
	spriterect.w = 37;
	spriterect.h = 27;
	
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
		spriterect.x = 37;

		for (int i = 0; i < MAX_BULLET_AMOUNT; i++)
		{
			shot[i].x += 15;
		}
		
		
		if (left == true)
		{
			if (texture_rect.x > 0)
			{
				texture_rect.x -= 10;
			}
	
		}
		
		if (right == true)
		{
			if (texture_rect.x < 590)
			{
				texture_rect.x += 10;
			}
		}

		if (up == true)
		{
			if (texture_rect.y > 0)
			{
				texture_rect.y -= 10;
				spriterect.x = 74;
			}
		}

		if (down == true)
		{
			if (texture_rect.y < 430)
			{
				texture_rect.y += 10;
				spriterect.x = 0;
			}
		}

		if (shooting == true)
		{
			if (bullets > 0)
			{
				for (int i = 0; i < MAX_BULLET_AMOUNT; i++)
				{
					shot[i].x = texture_rect.x + 50;
					shot[i].y = texture_rect.y + 20;
				}
				bullets--;
			}
		}

		background_1.x -= 5;
		background_2.x -= 5;

		if (background_1.x <= -1020)
		{
			background_1.x = 1020;
		}

		if (background_2.x <= -1020)
		{
			background_2.x = 1020;
		}

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, background_texture, NULL, &background_1);
		SDL_RenderCopy(renderer, background_texture, NULL, &background_2);
		SDL_RenderCopy(renderer, texture, &spriterect, &texture_rect);
		SDL_RenderCopy(renderer, shottexture, NULL, shot);
		SDL_RenderPresent(renderer);

	}


	SDL_Quit();
	return(0);
}