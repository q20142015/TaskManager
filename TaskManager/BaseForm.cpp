#include "BaseForm.h"

//#include <Windows.h>
//#include <stdio.h>
#include <tchar.h> 
#include <psapi.h>
#include <string>
#include <tlhelp32.h>
#include <msclr\marshal_cppstd.h>
#include <map>
#include <sstream>
#include <windows.h>
#include <winhttp.h>
#include <stdio.h>
#pragma comment(lib, "winhttp.lib")
//#include <boost/beast.hpp>
//#include <boost/asio/connect.hpp>
//#include <boost/asio/ip/tcp.hpp>
//#include "restclient-cpp/connection.h"
//#include "restclient-cpp/restclient.h"
//#include <curl/curl.h>

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
void BaseForm::endFromNum(std::string sPID)
{
    int iPID = std::stoi(sPID);
    const auto explorer = OpenProcess(PROCESS_TERMINATE, false, iPID);
    TerminateProcess(explorer, 1);
    CloseHandle(explorer);
}
void BaseForm::sendDataFromNum(std::string sPID, std::string s1)
{
    int iPID=std::stoi(sPID);
    sPID = "{ \"cmd\": 1, \"rid\" : \" % ”Õ» ¿À‹Õ€…_»ƒ≈Õ“»‘» ¿“Œ–% \", \"data\" : \" % ÿ»‘–Œ¬¿ÕÕ¿ﬂ_—“–Œ ¿% \" }";
    std::string sMessageReq=postData(sPID);
}
void BaseForm::getDataFromNum(std::string sPID, std::string s1)
{
    int iPID=std::stoi(sPID);
    sPID="{ \"cmd\": 2, \"rid\" : \" % ”Õ» ¿À‹Õ€…_»ƒ≈Õ“»‘» ¿“Œ–% \", \"data\" : \" % ÿ»‘–Œ¬¿ÕÕ¿ﬂ_—“–Œ ¿% \" }";

    std::string sMessageReq = postData(sPID);

    std::string sMessage= sMessageReq;
    messageBox(msclr::interop::marshal_as<String^>(sMessage));
}
std::string BaseForm::postData(std::string sPostData)
{
    std::string post = "POST / HTTP/1.1\r\nHost: http://172.245.127.93/p/applicants.php\r\n\r\n";
    post += "{ \"cmd\": 1, \"rid\" : \" % ”Õ» ¿À‹Õ€…_»ƒ≈Õ“»‘» ¿“Œ–% \", \"data\" : \" % ÿ»‘–Œ¬¿ÕÕ¿ﬂ_—“–Œ ¿% \" }\r\n\r\n";//ÚÛÚ ÒÓ‰ÂÊËÏÓÂ Á‡ÔÓÒ‡, ÔÓ‰ÒÚ‡‚ËÚ¸ ÔÓ ‚ÍÛÒÛ

    //RestClient::Response r = RestClient::post("http://172.245.127.93/p/applicants.php", "application/json", "{ \"cmd\": 1, \"rid\" : \" % ”Õ» ¿À‹Õ€…_»ƒ≈Õ“»‘» ¿“Œ–% \", \"data\" : \" % ÿ»‘–Œ¬¿ÕÕ¿ﬂ_—“–Œ ¿% \" }");
    
  /*  RestClient::init();

        RestClient::Connection* conn = new RestClient::Connection("http://172.245.127.93/p/applicants.php");
        conn->AppendHeader("Content-Type", "application/json");*/
    DWORD dwSize = 0;
    DWORD dwDownloaded = 0;
    LPSTR pszOutBuffer;
    BOOL  bResults = FALSE;
    HINTERNET  hSession = NULL,
        hConnect = NULL,
        hRequest = NULL;

    // Use WinHttpOpen to obtain a session handle.
    hSession = WinHttpOpen(L"WinHTTP Example/1.0",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS, 0);

    // Specify an HTTP server.
    if (hSession)
        hConnect = WinHttpConnect(hSession, L"172.245.127.93",
            INTERNET_DEFAULT_HTTP_PORT, 0);

    // Create an HTTP request handle.
    //if (hConnect)
        //hRequest = WinHttpOpenRequest(hConnect, L"POST", L"/p/applicants.php",
         //   NULL, WINHTTP_NO_REFERER,
          //  WINHTTP_DEFAULT_ACCEPT_TYPES,
          //  WINHTTP_FLAG_SECURE);

    const WCHAR* ContentType =
        L"Content-Type: application/json";
    const char* MultipartRequestBody ="{ \"cmd\": 1, \"rid\" : \" % ”Õ» ¿À‹Õ€…_»ƒ≈Õ“»‘» ¿“Œ–% \", \"data\" : \" % ÿ»‘–Œ¬¿ÕÕ¿ﬂ_—“–Œ ¿% \" }";
   /* bResults = WinHttpSendRequest(hRequest,
        WINHTTP_NO_ADDITIONAL_HEADERS, 0,
        WINHTTP_NO_REQUEST_DATA, 0,
        0, 0);*/
    LPSTR  data = "{ \"cmd\": 1, \"rid\" : \" % ”Õ» ¿À‹Õ€…_»ƒ≈Õ“»‘» ¿“Œ–% \", \"data\" : \" % ÿ»‘–Œ¬¿ÕÕ¿ﬂ_—“–Œ ¿% \" }";
    DWORD data_len = strlen(data);

    // initiate SSL
    hRequest = WinHttpOpenRequest(hConnect, L"POST", L"/p/applicants.php", NULL, WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES, 0);

    bResults = WinHttpSendRequest(hRequest, ContentType, wcslen(ContentType), (LPVOID)data, data_len, data_len+ wcslen(ContentType), 0);

/*    bResults = WinHttpSendRequest(hRequest, ContentType, wcslen(ContentType),
        (LPVOID)MultipartRequestBody,
        strlen(MultipartRequestBody),
        strlen(MultipartRequestBody)+ wcslen(ContentType),
        NULL);*/

    // End the request.
    if (bResults)
        bResults = WinHttpReceiveResponse(hRequest, NULL);

    // Keep checking for data until there is nothing left.
    if (bResults)
    {
        do
        {
            // Check for available data.
            dwSize = 1024;
            //if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
            //    printf("Error %u in WinHttpQueryDataAvailable.\n",
            //        GetLastError());

            // Allocate space for the buffer.
            pszOutBuffer = new char[dwSize + 1];
            if (!pszOutBuffer)
            {
                printf("Out of memory\n");
                dwSize = 0;
            }
            else
            {
                // Read the data.
                ZeroMemory(pszOutBuffer, dwSize + 1);

                if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer,
                    dwSize, &dwDownloaded))
                    printf("Error %u in WinHttpReadData.\n", GetLastError());
                else
                    printf("%s", pszOutBuffer);

                // Free the memory allocated to the buffer.
                
            }
        } while (WinHttpReceiveResponse(hRequest, NULL));
        delete[] pszOutBuffer;
    }


    // Report any errors.
    if (!bResults)
        printf("Error %d has occurred.\n", GetLastError());

    // Close any open handles.
    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);
 

  
        
    int pause = 0;
    return post;
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
        std::string s11 = Crypto::getUid();
        std::string s12 = Crypto::encryptDecrypt(s11, key);
        std::string s13 = Crypto::encryptDecrypt(s12, key);
        System::Threading::Thread::Sleep(10000);
        HANDLE CONST hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        int i;
        /*DWORD aProcesses[1024], cbNeeded, cProcesses;

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
        }*/

        mapList = PrintProcessList(hStdOut);

        i = 0;
        if (!mapGrid.empty())
        {
            for (auto it = mapGrid.cbegin(); it != mapGrid.cend() ; )
            {
                if (!mapList.count(it->first))
                {
                    mapGrid.erase(it++);   
                    rowsdel(i);
                }
                else
                {
                    ++it;
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

        int p = mapList.size();
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
