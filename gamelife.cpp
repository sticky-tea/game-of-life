#include <iostream>
#include <algorithm>
#include <vector>
#include <SDL2/SDL.h>

#include "life.hpp"

const int SS = 20;

const int W = SS*M, H = SS*M;

void exiterr()
{
	std::cout << "[SDL]: " << SDL_GetError() << "\n";
	exit(-1);
}


void showField(int field[M][M])
{
	for(int i = 0; i < M; i++)
	{
		for(int j = 0; j < M; j++)
			std::cout << field[i][j] << " ";
		std::cout << "\n";
	}
}


int main()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
		exiterr();

	SDL_DisplayMode display;
	SDL_GetDesktopDisplayMode(0, &display);

	SDL_Window* win = SDL_CreateWindow("", 50, 70, W, H, SDL_WINDOW_SHOWN);
	if(win == nullptr)
		exiterr();

	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if(ren == nullptr)
		exiterr();

	SDL_Event event;

	bool quit = false;

	int rw = W/M;
	int rh = H/M;

	life game;
	int field[M][M];
	bool isStarted = false;

	for(int i(0); i < M; i++)
		for(int j(0); j < M; j++)
			field[i][j] = 0;

	std::vector<std::pair<int, int>> black;

	int del = 400;

	while(true)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				quit = true;
			else if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				int x = event.motion.x;
				int y = event.motion.y;

				int r = x/rw;
				int c = y/rh;

				if(field[r][c] == 1)
				{
					field[r][c] = 0;
					black.erase(std::remove(black.begin(), black.end(), std::pair<int, int>{r,c}), black.end());
				}

				else
				{
					field[r][c] = 1;
					black.push_back({r, c});
				}		
			}

			else if(event.type == SDL_KEYDOWN)
			{
				if(event.key.keysym.sym == SDLK_SPACE)
				{
					if(isStarted)
					{
						isStarted = false;

						for(int i(0); i < M; i++)
							for(int j(0); j < M; j++)
								field[i][j] = 0;
						for(auto i : black)
							field[i.first][i.second] = 1;

						continue;
					}

					game.firstGeneration(field);
					isStarted = true;
				}

				else if(event.key.keysym.sym == SDLK_EQUALS)
				{
					if(del > 0)
						del -= 100;
				}

				else if(event.key.keysym.sym == SDLK_MINUS)
					del += 100;
			}
		}

		if(quit)
			break;

		SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(ren);
		SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);

		for(int i(0); i < W; i++)
		{
			for(int j(0); j < H; j++)
			{
				SDL_Rect rect1 = {i, j, rw, rh};
				SDL_RenderDrawRect(ren, &rect1);

				j += rh-1;
			}

			i += rw-1;
		}

		if(isStarted)
		{
			game.nextGeneration();
			auto f = game.getField();

			for(int i(0); i < M; i++)
			{
				for(int j(0); j < M; j++)
				{
					if(f[i][j] == 1)
						black.push_back({i, j});
					else
						black.erase(std::remove(black.begin(), black.end(), std::pair<int, int>{i,j}), black.end());			
				}
			}
		}

		for(auto i : black)
		{
			SDL_Rect rect1 = {i.first*rw, i.second*rh, rw, rh};
			SDL_RenderFillRect(ren, &rect1);			
		}

		SDL_RenderPresent(ren);
		
		if(isStarted)
			SDL_Delay(del);

		SDL_Delay(50);
	}

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}