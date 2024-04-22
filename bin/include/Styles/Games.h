#pragma once

#ifndef GAMES_H
#define GAMES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <ImGui/imgui.h>

#include <iostream>

#define jumpL std::cout << "\n"
#define maxGameList 500

class Games{
public: 

	//Games();

	struct Game {
		std::string directory = "null";
		std::string name = "null";
		int steamId = 0;
		SDL_Texture* icon = nullptr;
	};

	Game games[maxGameList];

	void addGame(std::string directory, char* name, int steamId, SDL_Renderer* renderer,SDL_Surface* icon);
	void updateGames();
	void cleanup();
};

#endif // !GAMES_H