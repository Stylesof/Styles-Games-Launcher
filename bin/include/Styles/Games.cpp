#include "Games.h"

Games::Games() {
	//SOLVE THIS

	SDL_Surface* icon = IMG_Load("../bin/resources/games/cs2.jpg");
	
	Game test;
	test.name = (char*)"trye";
	test.icon = SDL_CreateTextureFromSurface(nullptr, icon);
};

