#include "GUI.h"

void PackageInstaller::GUI::BrowseDirectory() { 
	ImGui::SetNextWindowPos(ImVec2(50, 80));
    ImGui::SetNextWindowSize(ImVec2(825, 280));
    ImGui::Begin("Browse Location", &closeSubWindow,
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoMove);

    ImGui::Text("Current Path: %s", currentPath.string().c_str());
    ImGui::Separator();
    ImGui::Text("Directory List: ");

    ImGui::SetCursorPos(ImVec2(750, 65));
    if (ImGui::Button("Back", ImVec2(60, 25))) {
        currentPath = currentPath.parent_path();
    }

    //Directory Iteration
    if (std::filesystem::exists(currentPath) &&
        std::filesystem::is_directory(currentPath)) {
        for (auto &directoryEntry :
             std::filesystem::directory_iterator(currentPath)) {

                fileType = directoryEntry.path().filename().string();

            if (directoryEntry.is_directory()) {
                    if (ImGui::Selectable(("D |  " + fileType).c_str(),false, ImGuiSelectableFlags_AllowDoubleClick, ImVec2(735,20))) {
                        currentPath /= fileType;
                    }
            } else if (directoryEntry.is_regular_file()) {
                ImGui::Selectable(("F |  " + fileType).c_str(), false,
                                  ImGuiSelectableFlags_AllowDoubleClick,
                                  ImVec2(735, 20));
            } else {
                ImGui::Selectable(("O |  " + fileType).c_str(), false,
                                  ImGuiSelectableFlags_AllowDoubleClick,
                                  ImVec2(735, 20));
            }
            ImGui::Separator();
        }

        ImGui::SetCursorScreenPos(ImVec2(800, 330));
        if (ImGui::Button("OK", ImVec2(60, 25))) {
            std::cout << currentPath.string().c_str() << std::endl;
            closeSubWindow = false;
        }
        ImGui::SetCursorScreenPos(ImVec2(800, 300));
        if (ImGui::Button("CANCEL", ImVec2(60, 25))) {
            std::cout << "Cancel Toggled." << std::endl;
            closeSubWindow = false;
        }

        ImGui::End();

    }


}

void PackageInstaller::GUI::CloseInstaller() { 
    if (!closeQuitWindow) {
        ImGui::Begin("Alert", &closeQuitWindow,
                     ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
                         ImGuiWindowFlags_NoResize |
                         ImGuiWindowFlags_NoTitleBar);
        ImGui::SetCursorPos(ImVec2(25, 40));
        ImGui::Text("ARE YOU SURE CLOSING THE INSTALLER.");
        ImGui::SetCursorPos(ImVec2(25, 70));
        if (ImGui::Button("YES", ImVec2(60, 25))) {
            //Do Application Quitting Job;
            Quitting = true;
        }
        ImGui::SetCursorPos(ImVec2(240, 70));
        if (ImGui::Button("NO", ImVec2(60, 25))) {
            closeQuitWindow = true;
        }
        ImGui::End();
    }
}
