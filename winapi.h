#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "Position.h"

class winapi
{
public:
    static std::string desktop_path;
    static HWND desktop;
    static HANDLE desktop_process;
    static std::unordered_map<std::string, int> indexes;

    // File
    static std::string getDesktopPath();
    static std::vector<std::string> getFiles(std::string path);

    // Index based
    static int getIndexOf(std::string fileName);
    static int getIndex(std::string fileName);
    static void loadIndexes();
    static int getIcons();
    static std::string getIconText(int index);
    static Position getPosition(int index);
    static void setPosition(int index, int posX, int posY);

    // filename based
    static void createFile(std::string name, int type);
    static void deleteFile(std::string name);
    static void rename(std::string oldName, std::string newName);

private:
    static HWND desk();
    static HANDLE getDesktopProcess();
};
