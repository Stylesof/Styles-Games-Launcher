#pragma once

#ifndef GAMES_H
#define GAMES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Games {
public: 
	Games();

	struct Game {
		int steamId;
		char* name;
		SDL_Texture* icon;
	};
};

#endif // !GAMES_H