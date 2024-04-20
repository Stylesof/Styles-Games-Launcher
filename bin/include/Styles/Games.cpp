#include "Games.h"

//Games::Games() {}

// Add a Game to the Games List ( games arrray )
void Games::addGame(int steamId, char* name, SDL_Renderer* renderer, SDL_Surface* icon) {
	for (int i = 0; i < maxGameList; i++) {
		if (Games::games[i].steamId <= 0) {
			if (steamId > 0) {
				Games::games[i].steamId = steamId;
				Games::games[i].name = name;

				icons[i] = SDL_CreateTextureFromSurface(renderer, icon);
			}
			/*
			jumpL (Jump Line) --> VERIFY GAME LIST
				#jumpL;
				#std::cout << Games::games[i].name;
				#jumpL;
				#std::cout << i;
			*/
			break;
		}
	}
}

void Games::updateGames(SDL_Renderer* renderer) {
	for (int i = 0; i < maxGameList; i++) {
		SDL_RenderCopy(renderer, icons[i], nullptr, nullptr);
	}
}

void Games::cleanup() {
	for (int i = 0; i < maxGameList; i++) {
		SDL_DestroyTexture(icons[i]);
	}
}