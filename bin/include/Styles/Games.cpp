#include "Games.h"

//Games::Games() {}
	

// Add a Game to the Games List ( games arrray )
void Games::addGame(std::string directory, char* name, int steamId, SDL_Renderer* renderer, SDL_Surface* icon) {
	for (int i = 0; i < maxGameList; i++) {
		if (Games::games[i].steamId <= 0) {
			if (steamId > 0) {
				Games::games[i].steamId = steamId;
				Games::games[i].name = name;
				Games::games[i].icon = SDL_CreateTextureFromSurface(renderer, icon);
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

void Games::updateGames() {
	for (int i = 0; i < maxGameList; i++) {
		if (Games::games[i].steamId != 0 || Games::games[i].icon != nullptr) {
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
			float internBoxXSize = ImGui::GetWindowSize().x - ImGui::GetStyle().ItemSpacing.x - ImGui::GetStyle().WindowBorderSize - ImGui::GetStyle().FramePadding.x - ImGui::GetStyle().DisplaySafeAreaPadding.x;

			// GAME LIST
			ImGui::BeginChild(i + 1, ImVec2(internBoxXSize, 60), ImGuiChildFlags_Border, ImGuiWindowFlags_NoScrollbar);
			ImGui::SetCursorPosY(1);                                         // BUTTON POS
				ImGui::Button("##Game Button", ImVec2(internBoxXSize, 60 - ImGui::GetStyle().ChildBorderSize * 2));
			ImGui::SetCursorPos(ImVec2(100, 30 - ImGui::GetFontSize() / 2)); // GAME NAME POS
				ImGui::Text(Games::games[i].name.c_str());
			ImGui::SetCursorPos(ImVec2(5, 5));                               //IMAGE POS
				ImGui::Image(Games::games[i].icon, ImVec2(80, 50));
			// --

			ImGui::EndChild();
			ImGui::PopStyleVar();
		}
	}
}

void Games::cleanup() {
	for (int i = 0; i < maxGameList; i++) {
		SDL_DestroyTexture(Games::games[i].icon);
	}
}