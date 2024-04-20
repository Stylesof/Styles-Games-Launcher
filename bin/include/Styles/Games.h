#pragma once

#ifndef GAMES_H
#define GAMES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#define jumpL std::cout << "\n"
#define maxGameList 500

class Games{
public: 

	//Games();

	struct Game {
		int steamId = 0;
		std::string name = "null";
		SDL_Surface* icon;
	};

	Game games[maxGameList];
	SDL_Texture* icons[maxGameList];

	void addGame(int steamId, char* name, SDL_Renderer* renderer,SDL_Surface* icon);
	void updateGames(SDL_Renderer* renderer);
	void cleanup();
};

#endif // !GAMES_H