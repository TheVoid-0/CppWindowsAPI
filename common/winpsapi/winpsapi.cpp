#include "winpsapi.h"

std::vector<DWORD> WinPsApi::getProcessIdList(DWORD *processCount)
{
    std::vector<DWORD> processes;
    processes.resize(1024);
    DWORD bytesNeeded;
    size_t bProcessesSize = processes.size() * sizeof(processes[0]);
    EnumProcesses(&processes[0], bProcessesSize, &bytesNeeded);

    *processCount = bytesNeeded / sizeof(DWORD);

    return processes;
}

void WinPsApi::getProcessIdList(DWORD *processes, DWORD bProcessesSize, DWORD &processCount)
{
    DWORD bytesNeeded;
    DWORD *pProcessCount = &processCount;

    EnumProcesses(processes, bProcessesSize, &bytesNeeded);

    *pProcessCount = bytesNeeded / sizeof(DWORD);
}

std::string WinPsApi::getProcessName(DWORD processID)
{
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    // Get a handle to the process.

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
                                      PROCESS_VM_READ,
                                  FALSE, processID);

    // Get the process name.

    if (NULL != hProcess)
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
                               &cbNeeded))
        {
            GetModuleBaseName(hProcess, hMod, szProcessName,
                              sizeof(szProcessName) / sizeof(TCHAR));
        }
    }

    // Release the handle to the process.

    CloseHandle(hProcess);

    std::string processName = szProcessName;

    return processName;
}

void WinPsApi::printAllProcesses()
{
    DWORD processes[1024], processCount;
    WinPsApi::getProcessIdList(processes, sizeof(processes), processCount);
    for (unsigned long i = 0; i < processCount; i++)
    {
        if (processes[i] != 0)
        {
            WinPsApi::getProcessName(processes[i]);
        }
    }
}

void WinPsApi::printProcess(DWORD processId, TCHAR *processName)
{
    printf(TEXT("%s  (PID: %u)\n"), processName, processId);
}

void WinPsApi::printProcess(DWORD processId, std::string processName)
{
    printf(TEXT("%s  (PID: %u)\n"), processName.c_str(), processId);
}

void WinPsApi::printProcesses(DWORD *processes, DWORD processCount)
{
    for (unsigned long i = 0; i < processCount; i++, processes++)
    {
        if (*processes != 0)
        {
            WinPsApi::printProcess(*processes, WinPsApi::getProcessName(*processes));
        }
    }
}

std::vector<Process> WinPsApi::getAllProcesses()
{
    std::vector<Process> processes;
    DWORD processCount;
    std::vector<DWORD> processesIds = WinPsApi::getProcessIdList(&processCount);

    for (DWORD pId : processesIds)
    {
        if (pId != 0)
        {
            Process process(pId, WinPsApi::getProcessName(pId));
            processes.push_back(process);
        }
    }

    return processes;
}