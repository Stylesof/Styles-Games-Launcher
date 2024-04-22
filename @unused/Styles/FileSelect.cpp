#include "FileSelect.h"

void FileSelect::registerFileSelect(const std::string varName, char* varPathLocationStore) {
    if (ImGuiFileDialog::Instance()->Display(varName)) {
        if (ImGuiFileDialog::Instance()->IsOk()) {
            // Add icon file path to the gameIconBuffer
            std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
            for (int i = 0; i < filePath.length(); i++) {
                if (filePath[i] == '\\') {
                    varPathLocationStore[i] = '/';
                }
                else {
                    varPathLocationStore[i] = filePath[i];
                }
            }
            ImGuiFileDialog::Instance()->Close();
        }
        else {
            ImGuiFileDialog::Instance()->Close();
        }
    }
}