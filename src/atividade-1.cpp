
#include "../common/winpsapi/winpsapi.h"

int main()
{
    std::vector<Process> processes = WinPsApi::getAllProcesses();
    for (Process p : processes)
    {
        std::cout << p;
    }
    return 0;
}