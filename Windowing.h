#pragma once
#include <iostream>
#include <string>
#include <SDL3\SDL.h>
#include "Logging.h"
#include "Archiver.h"
#include "GUI.h"
#include "imgui.h"
#include "backends\imgui_impl_sdl3.h"
#include "backends\imgui_impl_sdlrenderer3.h"

namespace PackageInstaller {
    class Windowing {
       public:

        Windowing();
        ~Windowing();

        int CreateApplicationWindow(const char* WindowsName);

        SDL_Rect Div(int RectHeight, int RectWidth, int RectXPos, int RectYPos);

        void instantClose();

       private:
        Logging Log;
        GUI nGui;
        Archiver arch;
        SDL_Window* mainWindow;
        SDL_Renderer* mainRenderer;
        SDL_Surface* mainSurface;
        SDL_Texture* mainTexture;
        const char* TextBoxMessage;

        //Variables
        bool QuitJob = false;
        bool isWindowClosed = false;
        int count = 0;
    };
}