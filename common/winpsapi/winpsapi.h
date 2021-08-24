#pragma once
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#pragma comment(lib, "Psapi.lib") /* for system running processes list*/
#include <vector>

#include "../../src/process/process.h"

class WinPsApi
{
    private:
    static void printProcess(DWORD processId, TCHAR *processName);
    static void printProcess(DWORD processId, std::string processName);

public:
    static std::vector<DWORD> getProcessIdList(DWORD *processCount);
    static void getProcessIdList(DWORD *processes, DWORD cb, DWORD &processCount);
    static void getProcessInfo(DWORD *processes, DWORD processCount);
    static std::string getProcessName(DWORD processID);
    static void printAllProcesses();
    static void printProcesses(DWORD *processes, DWORD processCount);
    static std::vector<Process> getAllProcesses();
};
