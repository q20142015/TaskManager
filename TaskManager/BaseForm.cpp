#include "BaseForm.h"
#include "Crypto.h"

#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <string>
#include <tlhelp32.h>
#include <msclr\marshal_cppstd.h>

using namespace TaskManager;
using namespace System::Diagnostics;

std::string key = "Crypto";

void MutexDenied(LPCSTR mutexName);
std::string PrintProcessNameAndID(DWORD processID);
std::string PrintProcessList(HANDLE CONST hStdOut);
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    MutexDenied(mutexName);
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew BaseForm);
    return 0;
}
void BaseForm::endFromNum(std::string s)
{
    std::string ss1 = "";
}
void BaseForm::sendDataFromNum(std::string s, std::string s1)
{
    std::string ss1 = "";
}
void BaseForm::getDataFromNum(std::string s, std::string s1)
{
    std::string ss1 = "";
    messageBox(msclr::interop::marshal_as<String^>(ss1));
}
void BaseForm::gridRefreshThread()
{
    while (true)
    {
    gridRefresh();
    }
}
void BaseForm::gridRefresh()
{    
        std::string s11=Crypto::getUid();
        std::string s12 = Crypto::encryptDecrypt(s11, key);
        std::string s13 = Crypto::encryptDecrypt(s12, key);
        System::Threading::Thread::Sleep(10000);
        HANDLE CONST hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD aProcesses[1024], cbNeeded, cProcesses;
        unsigned int i;

        if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
        {
           return;
        }

        cProcesses = cbNeeded / sizeof(DWORD);
        int p = 0;
        std::string s1 = "", s2 = "", s3 = "";

        for (i = 0; i < cProcesses; i++)
        {
            if (aProcesses[i] != 0)
            {
                s1 += PrintProcessNameAndID(aProcesses[i]) + "\n";
                p++;
            }
        }

        s2 += PrintProcessList(hStdOut);

        p = 0;
        s1 = "1"; s2 = "2";
        rowsadd(msclr::interop::marshal_as<String^>(s1), msclr::interop::marshal_as<String^>(s2));
        rowschange(msclr::interop::marshal_as<String^>(s1), msclr::interop::marshal_as<String^>(s2),0);
        //rowsdel(0);
}
std::string PrintModuleList(HANDLE CONST hStdOut, DWORD CONST dwProcessId) {
    MODULEENTRY32 meModuleEntry;
    TCHAR szBuff[1024];
    DWORD dwTemp;
    HANDLE CONST hSnapshot = CreateToolhelp32Snapshot(
        TH32CS_SNAPMODULE, dwProcessId);
    if (INVALID_HANDLE_VALUE == hSnapshot) {
        return "";
    }

    meModuleEntry.dwSize = sizeof(MODULEENTRY32);
    Module32First(hSnapshot, &meModuleEntry);
    std::string s = " ";
    do {
        //wsprintf(szBuff, L"  ba: %08X, bs: %08X, %s\r\n",
        //   meModuleEntry.modBaseAddr, meModuleEntry.modBaseSize,
        //    meModuleEntry.szModule);
       // WriteConsole(hStdOut, szBuff, lstrlen(szBuff), &dwTemp, NULL);
        std::wstring ws(meModuleEntry.szModule);
        // your new String
        std::string str(ws.begin(), ws.end());
        s += str +" ";
    } while (Module32Next(hSnapshot, &meModuleEntry));

    CloseHandle(hSnapshot);
    return s;
}
std::string PrintProcessList(HANDLE CONST hStdOut) {
    PROCESSENTRY32 peProcessEntry;
    TCHAR szBuff[1024];
    DWORD dwTemp;
    HANDLE CONST hSnapshot = CreateToolhelp32Snapshot(
        TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hSnapshot) {
        return "";
    }

    peProcessEntry.dwSize = sizeof(PROCESSENTRY32);
    Process32First(hSnapshot, &peProcessEntry);
    std::string s = "";
    int p = 0;
    do {
        //wsprintf(szBuff, L"=== %08X %s ===\r\n",
         //   peProcessEntry.th32ProcessID, peProcessEntry.szExeFile);
        //WriteConsole(hStdOut, szBuff, lstrlen(szBuff), &dwTemp, NULL);
        std::wstring ws(peProcessEntry.szExeFile);
        std::string str(ws.begin(), ws.end());
        s +=  std::to_string (peProcessEntry.th32ProcessID)+" "+str +
        PrintModuleList(hStdOut, peProcessEntry.th32ProcessID) + "\n";
        p++;
    } while (Process32Next(hSnapshot, &peProcessEntry));

    CloseHandle(hSnapshot);

    return s;
}
std::string PrintProcessNameAndID(DWORD processID)
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

    std::string s;
    #ifndef UNICODE
    s = szProcessName;
    #else
    std::wstring wStr = szProcessName;
    s = std::string(wStr.begin(), wStr.end());
    #endif
    if (s != "<unknown>") {
        int p = 0;
    }
    //std::string str =  s + processID;

    // Release the handle to the process.

    CloseHandle(hProcess);
    return s;
}
void MutexDenied(LPCSTR mutexName) {
    hMutex = OpenMutexA(MUTEX_ALL_ACCESS, 0, mutexName);

    if (!hMutex)
        hMutex = CreateMutexA(0, 0, mutexName);
    else
    {
        CloseHandle(hMutex);
        exit(-1); 
    }
}
