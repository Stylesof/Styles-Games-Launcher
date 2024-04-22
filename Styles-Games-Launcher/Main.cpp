#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_sdl2.h>
#include <ImGui/imgui_impl_sdlrenderer2.h>

//#include <ImGuiFileDialog/ImGuiFileDialog.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <commdlg.h>

#include <Styles/Games.h>
#include <Styles/FileSelect.h>  

#define print(x) std::cout << x

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

Games var;
FileSelect var2;

int main(int, char**)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

    // SDL2
    SDL_DisplayMode DM;
    SDL_GetDesktopDisplayMode(0, &DM);
    auto aspect = 0.75;
    auto Width = DM.w * aspect;
    auto Height = DM.h * aspect;

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("Styles Games", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, window_flags);
    SDL_SetWindowMaximumSize(window, DM.w, DM.h);
    SDL_SetWindowMinimumSize(window, 920, 580);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    ImGui::StyleColorsDark(); //THEME
        ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(1, 0, 0, 1));
        ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(1, 0, 0, 1));
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1, 0, 0, 1));
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.25, 0, 0, 0.25));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.35, 0, 0, 0.35));

    //ImGui + SDL2 Renderer
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    //Variables:----------------------------------------------------------------------{   
    SDL_Surface* Background = IMG_Load("../bin/resources/gui/Background.png");
    SDL_Texture* BackgroundT = SDL_CreateTextureFromSurface(renderer, Background);
    if (Background == nullptr || BackgroundT == nullptr) print("TEXTURE LOADING ERROR");

    SDL_Surface* AddGameButton = IMG_Load("../bin/resources/gui/AddGameButton.png");
    SDL_Texture* AddGameButtonT = SDL_CreateTextureFromSurface(renderer, AddGameButton);

    bool AddGameMenu = false;
    char gameDirectoryBuffer[516] = "";
    char gameNameBuffer[516] = "";
    char gameIconBuffer[516] = "";
    int gameSteamIDBuffer = 0;

    // ADD GAME TO THE GAME LIST
    // -============
        var.addGame(163, (char*)"Counter-Strike 2", renderer, IMG_Load("../bin/resources/games/cs2.jpg"));
    // -============
    //Variables:----------------------------------------------------------------------}

    // Main loop
    while (true){
        SDL_Event event;
        SDL_PollEvent(&event);
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT) goto Cleanup;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window)) goto Cleanup;

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        SDL_RenderClear(renderer);

        //Codigo--------------------------------------------------------------------------{
        int GameWindowWidth;
        int GameWindowHeight;
        SDL_GetWindowSizeInPixels(window, &GameWindowWidth, &GameWindowHeight);

        SDL_Rect BackgroundVec;
            BackgroundVec.x = 0;
            BackgroundVec.y = 0;
            BackgroundVec.w = GameWindowWidth;
            BackgroundVec.h = GameWindowHeight - 50;

        SDL_Rect AddGameButtonVec;
            AddGameButtonVec.x = 0;
            AddGameButtonVec.y = 0;
            AddGameButtonVec.w = 0;
            AddGameButtonVec.h = 0;
        
        SDL_RenderCopy(renderer, BackgroundT, NULL, &BackgroundVec); // Background   

        {
            ImGuiWindowFlags gamelistWindowFlags = (ImGuiWindowFlags)(ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove); //ImGuiWindowFlags_NoBackground
            ImGui::SetNextWindowBgAlpha(0.0f);
            ImGui::Begin("Games", NULL, gamelistWindowFlags);             

            int WindowW;
            int WindowH;
            SDL_GetWindowSize(window, &WindowW, &WindowH);

            //1920 / x = 1440 / y
            // 1440/810 default object base position
            int WindowWidthRatio = 996;
            int resolveAspectWidth = (GameWindowWidth * WindowWidthRatio) / 1440;
            int WindowHeightRatio = 750;
            int resolveAspectHeight = (WindowHeightRatio * BackgroundVec.h) / 810;

            int WindowXRatio = 30;
            int resolveAspectX = (GameWindowWidth * WindowXRatio) / 1440;
            int WindowYRatio = 30;
            int resolveAspectY = (GameWindowHeight * WindowYRatio) / 810;

            //Adjust Games Window with Backgroud.png 
            ImGui::SetWindowPos(ImVec2(resolveAspectX , resolveAspectY), 0);
            ImGui::SetWindowSize(ImVec2(GameWindowWidth - resolveAspectWidth, resolveAspectHeight), 0);

            //Show Games in the Game list
            // -=======================//
                var.updateGames();     // MAIN OBJECTIVE 50% :-D
            // -=======================//

            ImGui::End();

            // Add Game Button
            // -++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            {
                ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(.20, 0, 0, .20));
                    ImGui::SetNextWindowPos(ImVec2(0, BackgroundVec.h));
                    ImGui::SetNextWindowSize(ImVec2(GameWindowWidth, GameWindowHeight - BackgroundVec.h));
                ImGui::Begin("Styles Games Launcher Bar", NULL, ImGuiWindowFlags_NoDecoration);
                    // Center the Button
                    float addGameWindowYCenter = ImGui::GetWindowSize().y - ImGui::GetStyle().ItemSpacing.y - ImGui::GetStyle().WindowBorderSize * 2 - ImGui::GetStyle().FramePadding.y - ImGui::GetStyle().DisplaySafeAreaPadding.y;
                    ImGui::SetCursorPosY(addGameWindowYCenter  - 32);
                    if (ImGui::ImageButton(AddGameButtonT, ImVec2(32, 32))) AddGameMenu = !AddGameMenu;
                ImGui::End();
                ImGui::PopStyleColor();
            }
            // -++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            
            // ADD GAME MENU
            // -##############################
            {
                if (AddGameMenu) {
                    ImGui::SetNextWindowSizeConstraints(ImVec2(640, 400), ImVec2(860, 668));

                    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
                    ImGui::Begin("Add Game Menu", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);

                        //Game Directory-==================================================================
                        ImGui::InputText("##Game Exe Directory", gameDirectoryBuffer, sizeof(gameDirectoryBuffer));
                        ImGui::SameLine();
                            if (ImGui::Button("X", ImVec2(20, 20))) var2.FileSelectMenu(L".Exe\0*.exe\0", gameDirectoryBuffer);
                        ImGui::SameLine();
                        ImGui::Text("Select Game Executable");         
                        //Game Name-=======================================================================
                        ImGui::InputText("Insert the Game Name", gameNameBuffer, sizeof(gameNameBuffer));            
                        //Game SteamID-====================================================================
                        ImGui::InputInt("Game SteamID (Can be any value)", &gameSteamIDBuffer);
                        //Game ICON-=======================================================================
                        ImGui::InputText("##Game Icon", gameIconBuffer, sizeof(gameIconBuffer));
                        ImGui::SameLine();                       
                            if (ImGui::Button("->", ImVec2(20, 20))) var2.FileSelectMenu(L"Imagem\0*.jpg;*.png\0", gameIconBuffer);           
                        ImGui::SameLine();
                        ImGui::Text("Select Game Icon/Image Directory");

                        ImGui::SetCursorPos(ImVec2(0, ImGui::GetWindowHeight() - 70));
                            if (ImGui::Button("Cancel", ImVec2(120, 60)))AddGameMenu = !AddGameMenu;
                        ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() - 120, ImGui::GetWindowHeight() - 70));
                            if (ImGui::Button("Confirm", ImVec2(120, 60))) {
                                var.addGame(gameDirectoryBuffer, gameNameBuffer, gameSteamIDBuffer, renderer, IMG_Load(gameIconBuffer));
                                AddGameMenu = !AddGameMenu;
                            }
                    ImGui::PopStyleVar();
                    ImGui::End();
                }
            }
            // -##############################
        }


        //*
        //Codigo--------------------------------------------------------------------------}

        // Rendering
        ImGui::Render();
        SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

        SDL_RenderPresent(renderer);
    }

Cleanup:
    //Styles Game list
    // - Delete All Surfaces from addGame()
    var.cleanup();

    //ImGui
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    //SDL2
    SDL_DestroyTexture(BackgroundT);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}