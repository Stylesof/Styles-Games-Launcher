#pragma once

#ifndef FILESELECT_H
#define FILESELECT_H

#include <iostream>
#include <string.h>

#include <ImGuiFileDialog/ImGuiFileDialog.h>

class FileSelect {
public:

	void registerFileSelect(const std::string varName, char* varPathLocationStore);
};

#endif