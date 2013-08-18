#include "stdafx.h"
#include "winapi.h"
#include "Object.h"

HWND        winapi::desktop         = desk();
std::string winapi::desktop_path    = winapi::getDesktopPath();
HANDLE      winapi::desktop_process = winapi::getDesktopProcess();
std::unordered_map<std::string, int> winapi::indexes = std::unordered_map<std::string, int>();


int winapi::getIcons()
{
    return ListView_GetItemCount(desktop);
}

std::string winapi::getIconText(int index)
{
    const int allocSize = sizeof(LVITEM);
    void *pointer = VirtualAllocEx(desktop_process, NULL, allocSize, MEM_COMMIT, PAGE_READWRITE);

    char buffer[128] = {50};
    LVITEM item;
    ZeroMemory(&item, sizeof(LVITEM));
    item.cchTextMax = 128;
    item.pszText = reinterpret_cast<LPTSTR>(pointer) + sizeof(LVITEM);

    size_t written, read;
    WriteProcessMemory(desktop_process, pointer, &item, sizeof(LVITEM), &written);
    SendMessage(desktop, LVM_GETITEMTEXT, index, reinterpret_cast<LPARAM>(pointer));
    ReadProcessMemory(desktop_process, item.pszText, buffer, 128 * sizeof(TCHAR), &read);

    VirtualFree(pointer, allocSize, MEM_RELEASE);

    return std::string(buffer);
}


int winapi::getIndex(std::string fileName)
{
    auto it = indexes.find(fileName);
    if(it != indexes.end())
        return indexes.at(fileName);
    std::cout << "not found! " << fileName << "\n";
    throw(":<");
    //return -1;
}


int winapi::getIndexOf(std::string fileName)
{
    int icons = ListView_GetItemCount(desktop);
    for (int i = 0; i < icons; i++)
    {
        int index = i;
        std::string name = getIconText(index);
        if(name == fileName)
            return index;
    }
    std::cout << "Not found " << fileName << "\n";
    return 0;
}


void winapi::loadIndexes()
{
    indexes.clear();

    int icons = ListView_GetItemCount(desktop);
    for (int i = 0; i < icons; i++)
    {
        int index = i;
        std::string name = getIconText(index);
        //std::cout << "found: \"" << name << "\"\n";
        indexes.emplace(std::make_pair(name, index));
    }
}


Position winapi::getPosition(int index)
{
    SIZE_T numread = 0;
    POINT *p = new POINT;
    p->x = p->y = 0;

    void *pointer = VirtualAllocEx(desktop_process, NULL, sizeof(POINT), MEM_COMMIT, PAGE_READWRITE);
    ListView_GetItemPosition(desktop, index, pointer);
    ReadProcessMemory(desktop_process, pointer, p, sizeof(POINT), &numread);

    Position pos(p->x, p->y);
    VirtualFree(pointer, sizeof(POINT), MEM_RELEASE);
    return pos;
}


HANDLE winapi::getDesktopProcess()
{
    DWORD pid;
    GetWindowThreadProcessId(desktop, &pid);
    HANDLE process = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, false, pid);
    return process;
}


void winapi::setPosition(int index, int posX, int posY)
{
    ListView_SetItemPosition(desktop, index, posX, posY);
}


void winapi::createFile(std::string name, int type)
{
    std::string copy;

    typedef Object::TYPES::Type obj;
    switch(type)
    {
        default: std::cout << "BAD NAME WHILE CREATING FILE: " << name << "\n";
        case obj::BOX:      copy = "box"; break;
        case obj::HEALTH:   copy = "heart"; break;
        case obj::NPC:
        case obj::PLAYER:   copy = "man"; break;
        case obj::SPIKES:   copy = "spikes"; break;
        case obj::EXIT:     copy = "exit"; break;
        case obj::POISONING_CLOUD: copy = "cloud"; break;
    }

    std::string from = desktop_path + "cExample\\ico\\" + copy + ".ico";
    std::string to   = desktop_path + name + ".ico";

    CopyFile(from.c_str(), to.c_str(), true);
    //MoveFile(from.c_str(), to.c_str());
    //CreateFile(path.c_str(), 0, 0, 0, OPEN_ALWAYS, FILE_FLAG_DELETE_ON_CLOSE, 0);
}


void winapi::deleteFile(std::string name)
{
    name = desktop_path + name;
    DeleteFile(name.c_str());
}


HWND winapi::desk()
{
    std::string mgr = "Progman";
	HWND mgrWindow = FindWindow(mgr.c_str(), NULL);

	std::string shell = "SHELLDLL_DefView";
	HWND fatherWindow = FindWindowEx(mgrWindow, NULL, shell.c_str(), NULL);

	std::string syslist = "SysListView32";
	HWND desktop = FindWindowEx(fatherWindow, NULL, syslist.c_str(), NULL);

    return desktop;
}


std::string winapi::getDesktopPath()
{
    std::string path(getenv("USERPROFILE"));
    path += "\\desktop\\";
    return path;
}


void winapi::rename(std::string oldName, std::string newName)
{
    oldName = desktop_path + oldName;
    newName = desktop_path + newName;
    MoveFileExA(oldName.c_str(), newName.c_str(), 0);

    loadIndexes(); // refresh
}


std::vector<std::string> winapi::getFiles(std::string targetDir)
{
    std::vector<std::string> files;
    WIN32_FIND_DATA ffd;
    HANDLE hFind = INVALID_HANDLE_VALUE;

    TCHAR szDir[MAX_PATH] = {0};
    targetDir += "*";

    char *p = (char*)&szDir;
    targetDir.copy(p, targetDir.length(), 0);

    hFind = FindFirstFile(szDir, &ffd);

    do
    {
        std::string f = ffd.cFileName;
        if(f != "." && f != "..")
            files.push_back(f);
    }
    while (FindNextFile(hFind, &ffd) != 0);

    FindClose(hFind);
    return files;
}
