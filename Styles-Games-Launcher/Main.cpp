#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_sdl2.h>
#include <ImGui/imgui_impl_sdlrenderer2.h>

#include <iostream>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <Styles/Games.h>

#define print(x) std::cout << x

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

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
    SDL_SetWindowMinimumSize(window, 800, 640);

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

    //ImGui + SDL2 Renderer
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    //Variables:----------------------------------------------------------------------{
    /* EXAMPLE OF GAME ADD TO GAME LIST -->
    - Games var;
    - SDL_Texture* cs2;
    - var.addGame(126, (char*)"Cs2", renderer, IMG_Load("../bin/resources/games/cs2.jgp"));
    - var.addGame(173, (char*)"Warzone", renderer, IMG_Load("../bin/resources/games/cs2.jgp"));
    */
    
    SDL_Surface* Background = IMG_Load("../bin/resources/gui/Background.png");
    SDL_Texture* BackgroundT = SDL_CreateTextureFromSurface(renderer, Background);
    if (Background == nullptr || BackgroundT == nullptr) print("TEXTURE LOADING ERROR");

    // Create Button to addGame()
    SDL_Surface* surface = IMG_Load("../bin/resources/games/cs2.jpg");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

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
        SDL_RenderCopy(renderer, BackgroundT, NULL, NULL);
        
        {        
            ImGuiWindowFlags flags = (ImGuiWindowFlags)(ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);
            ImGui::SetNextWindowBgAlpha(0.5f);
            ImGui::Begin("Jogos", NULL, flags);   

            int GameWindowWidth;
            int GameWindowHeight;
            SDL_GetWindowSizeInPixels(window, &GameWindowWidth, &GameWindowHeight);

            int WindowW;
            int WindowH;
            SDL_GetWindowSize(window, &WindowW, &WindowH);

            //1920 / x = 1440 / y
            // 1440 default object base position
            int WindowWidthRatio = 996;
            int resolveAspectWidth = (GameWindowWidth * WindowWidthRatio) / 1440;
            int WindowHeightRatio = 750;
            int resolveAspectHeight = (GameWindowHeight * WindowHeightRatio) / 810;

            int WindowXRatio = 30;
            int resolveAspectX = (GameWindowWidth * WindowXRatio) / 1440;
            int WindowYRatio = 30;
            int resolveAspectY = (GameWindowHeight * WindowYRatio) / 810;

            //Adjust Games Window with Backgroud.png 
            ImGui::SetWindowPos(ImVec2(resolveAspectX , resolveAspectY), 0);
            ImGui::SetWindowSize(ImVec2(GameWindowWidth - resolveAspectWidth, resolveAspectHeight), 0);

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

            float internBoxXSize = ImGui::GetWindowSize().x - ImGui::GetStyle().ItemSpacing.x - ImGui::GetStyle().WindowBorderSize - ImGui::GetStyle().FramePadding.x - ImGui::GetStyle().DisplaySafeAreaPadding.x;

            //GAME LIST
                //ImGui::BeginChild(1, ImVec2(internBoxXSize, 60), ImGuiChildFlags_Border, ImGuiWindowFlags_NoScrollbar);
                    //ImGui::ImageButton(texture, ImVec2(100, 54));
                    //ImGui::SameLine();
                    //ImGui::SetWindowFontScale(1.5);
                    //ImGui::SetCursorPos(ImVec2(120, 20));
                    //ImGui::Text("Red Dead Redemption");
                //ImGui::EndChild();
            
                
                ImGui::BeginChild(1, ImVec2(internBoxXSize, 60), ImGuiChildFlags_Border, ImGuiWindowFlags_NoScrollbar);                   
                    ImGui::SetCursorPosY(1);                                         // BUTTON POS
                        ImGui::Button("##Game Button", ImVec2(internBoxXSize, 60 - ImGui::GetStyle().ChildBorderSize * 2));
                    ImGui::SetCursorPos(ImVec2(100, 30 - ImGui::GetFontSize() / 2)); // GAME NAME POS
                        ImGui::Text("Counter-Strike 2");
                    ImGui::SetCursorPos(ImVec2(5, 5));                               //IMAGE POS
                        ImGui::Image(texture, ImVec2(80, 50));
                ImGui::EndChild();

            ImGui::PopStyleVar();
            ImGui::End();   
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
    //var.cleanup();

    //ImGui
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    //SDL2
    SDL_DestroyTexture(BackgroundT);
    SDL_DestroyTexture(texture);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}