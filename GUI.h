#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include "imgui.h"
#include "backends\imgui_impl_sdl3.h"
#include "backends\imgui_impl_sdlrenderer3.h"

namespace PackageInstaller {
class GUI {
   public:
    void BrowseDirectory();

    void CloseInstaller();

    // Closes ImGui::Begins
    bool closeSubWindow = true;
    bool QuitCheck = true;
    
    bool Quitting = false;

   private:
    std::filesystem::path currentPath = std::filesystem::current_path();

    std::string fileType;
    bool closeQuitWindow = false;
    };
}  // namespace PackageInstaller