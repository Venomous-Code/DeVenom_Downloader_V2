#include "Windowing.h"

PackageInstaller::Windowing::Windowing() {
    SDL_Init(SDL_INIT_VIDEO);

    CreateApplicationWindow("SDL3_WINDOW");


    TextBoxMessage = "WELCOME TO 'DEVENOM RESOURCE DOWNLOADER'.";
    const char* NextToBrowseButton = "NEXT";
    short int ToggleCounter = 0;
    const char* QuitToInstall = "QUIT";

    while (!isWindowClosed) {
        SDL_Event event;


        if (isWindowClosed) {
            SDL_DestroyWindow(mainWindow);
            SDL_DestroyRenderer(mainRenderer);
            SDL_DestroySurface(mainSurface);
            SDL_DestroyTexture(mainTexture);

            ImGui_ImplSDLRenderer3_Shutdown();
            ImGui_ImplSDL3_Shutdown();
            ImGui::DestroyContext();

            SDL_Quit();
            break;

        }


        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT) {
                isWindowClosed = true;
            }
        }

        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        SDL_RenderClear(mainRenderer);
        SDL_RenderTexture(mainRenderer, mainTexture, NULL, NULL);
        
        // Build your GUI

        ImGui::SetNextWindowPos(ImVec2(5, 430));
        ImGui::SetNextWindowSize(ImVec2(910, 45));
        ImGui::Begin("###Title", 0,
                     ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                         ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);
        ImGui::Text(TextBoxMessage);
        ImGui::SetCursorPos(ImVec2(840, 10));


        if (ToggleCounter >= 2) {
            nGui.BrowseDirectory();
            if (ToggleCounter >= 4) ToggleCounter = 2;
        }

        if (ImGui::Button(NextToBrowseButton, ImVec2(65, 25))) {
            TextBoxMessage =
                "PLEASE CLICK ON 'BROWSE' TO CHOOSE INSTALLATION DIRECTORY.";
            NextToBrowseButton = "BROWSE";
            QuitToInstall = "INSTALL";
            nGui.QuitCheck = false;
            ToggleCounter++;
        }

        if (!nGui.closeSubWindow) {
            ToggleCounter = 1;
        }

        ImGui::SetCursorPos(ImVec2(770, 10));
        if (ImGui::Button(QuitToInstall, ImVec2(65, 25))) {
            if (!nGui.QuitCheck) {
                //Do The Installation Job.
                std::cout << "I Should Do The Installation Job." << std::endl;
                arch.ArchiverInit("AppData\\Binaries\\DeVenom_Downloader.tar", AE_IFREG);
                QuitToInstall = "FINISH";
                count++;
                if (count == 2) {
                    QuitJob = true;
                }
            } else {
                //Do The Quit Job.
               /* std::cout << "I Should Do The Quit Job." << std::endl;*/
                QuitJob = true;
            }
        }

        ImGui::End();

        if (QuitJob) {
            nGui.CloseInstaller();
        }

        if (nGui.Quitting) {
            instantClose();
        }


        ImGui::Render();
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(),mainRenderer);
        SDL_RenderPresent(mainRenderer);
    
    }



    SDL_Quit();
}

PackageInstaller::Windowing::~Windowing() { 
    SDL_DestroyWindow(mainWindow); 
    SDL_DestroyRenderer(mainRenderer);
    SDL_DestroySurface(mainSurface);
    SDL_DestroyTexture(mainTexture);

    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_Quit();
}

int PackageInstaller::Windowing::CreateApplicationWindow(
    const char* WindowsName) { 

    mainWindow =
        SDL_CreateWindow(WindowsName, 920, 480,
                         SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_BORDERLESS);

    if (mainWindow == NULL) {
        Log.CustomLogger(
            "SDL FAILED TO CREATE WINDOW. AN UNEXPECTED ERROR OCCURED WHILE "
            "IINITIALIZING WINDOW.",
            spdlog::level::critical);
        return 1;
    }

    SDL_Rect PictureFrame = Div(420, 910, 5, 5);

    mainRenderer = SDL_CreateRenderer(mainWindow, NULL);

    mainSurface = SDL_LoadBMP("Images\\Cover3.bmp");

    mainTexture = SDL_CreateTextureFromSurface(mainRenderer, mainSurface);

    SDL_SetRenderViewport(mainRenderer, &PictureFrame);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(mainWindow, mainRenderer);
    ImGui_ImplSDLRenderer3_Init(mainRenderer);
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.Fonts->AddFontFromFileTTF("Fonts/Gidole-Regular.ttf", 20);

    return 0;
}

SDL_Rect PackageInstaller::Windowing::Div(int RectHeight, int RectWidth,
                                          int RectXPos, int RectYPos) { 

    SDL_Rect TextureRectangle;
    TextureRectangle.h = RectHeight;
    TextureRectangle.w = RectWidth;
    TextureRectangle.x = RectXPos;
    TextureRectangle.y = RectYPos;

    return TextureRectangle;

}

void PackageInstaller::Windowing::instantClose() {

    isWindowClosed = true;
}
