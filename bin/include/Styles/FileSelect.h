#pragma once

#ifndef FILESELECT_H
#define FILESELECT_H

#include <Windows.h>
#include <string>
#include <iostream>

#include <SDL2/SDL.h>

class FileSelect {
public:

	OPENFILENAME ofn;

	bool FileSelectMenu(LPCWSTR fileFilter, char* filePath);
};

#endif