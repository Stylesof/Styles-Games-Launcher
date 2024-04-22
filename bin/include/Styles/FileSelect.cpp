#include "FileSelect.h"

bool FileSelect::FileSelectMenu(LPCWSTR fileFilter, char* filePath) {

    TCHAR szFile[260] = { 0 };

	ZeroMemory(&ofn, sizeof(&ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = fileFilter;
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

    GetOpenFileName(&ofn);
    std::wstring ws(ofn.lpstrFile);
    std::string filename(ws.begin(), ws.end());
    for (int i = 0; i < filename.length(); i++) {
        if (filename[i] == '\\') {
            filePath[i] = '/';
        }
        else {
            filePath[i] = filename[i];
        }
    }
    return true;
 
}