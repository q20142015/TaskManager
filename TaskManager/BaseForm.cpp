#include "BaseForm.h"
#pragma managed(push, off)
#include <boost/beast.hpp>
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
#include <nlohmann/json.hpp>
//#include <curl/curl.h>
#pragma comment(lib, "winhttp.lib")
#include <boost/asio.hpp>
//#include <boost/json.hpp>
#pragma managed(pop)
//#include "restclient-cpp/connection.h"
//#include "restclient-cpp/restclient.h"
//#include <curl/curl.h>

using namespace std;

using namespace TaskManager;
using namespace System::Diagnostics;
using tcp = boost::asio::ip::tcp;

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

    std::string data = mapGrid[iPID];
    data.erase(data.size()-1, 1);
    time_t start_time;
    start_time = time(NULL);
    data +=" "+ std::to_string(start_time);
    data=Crypto::encryptDecrypt(data, key);
    //data = Crypto::encryptDecrypt(data, key);
    std::string datareq;

    for (int i = 0; i < data.size(); i++)
    {
        int iMyAsciiValue = static_cast<int>(data[i]);
        datareq += std::to_string(iMyAsciiValue)+" ";
    }



    sPID = "{ \"cmd\": 1, \"rid\" : \""+mapUid[iPID]+"\", \"data\" : \" "+ datareq + "\"  }";
    std::string sMessageReq=postData(sPID);
    messageBox(msclr::interop::marshal_as<String^>("Send!"));
}
void BaseForm::getDataFromNum(std::string sPID, std::string s1)
{
    int iPID=std::stoi(sPID);
    sPID="{ \"cmd\": 2, \"rid\" : \"" + mapUid[iPID] + "\"}";

    std::string sMessageReq = postData(sPID);

    stringstream ss(sMessageReq);
    if (sMessageReq.find('data') != sMessageReq.npos) {
        std::string sName;
        int numDel = sMessageReq.find("\"data\"");
        sMessageReq.erase(0, numDel + 9);
        if (sMessageReq == "}"){ messageBox(msclr::interop::marshal_as<String^>("Empty"));}
        else {
            numDel = sMessageReq.find("\"");
            sMessageReq.erase(numDel, 2);
        }
    }
    std::vector<std::string> stringvector;

    ss.clear();
    ss.str(sMessageReq);
    std::string item;
    while (std::getline(ss, item, ' ')) {
        stringvector.push_back(item);
    }
    sMessageReq = "";
    for (int i = 0; i < stringvector.size();i++)
    {
        sMessageReq.push_back((char)std::stoi(stringvector[i]));
    }

    sMessageReq = Crypto::encryptDecrypt(sMessageReq, key);
    
    stringvector.clear();

    ss.clear();
    ss.str(sMessageReq);
    while (std::getline(ss, item, ' ')) {
        stringvector.push_back(item);
    }
    if (stringvector.size() <= 3) { sMessageReq = "Empty"; }
    else {
        sMessageReq = "";
        for (int i = 2; i < stringvector.size()-1; i++)
        {
            sMessageReq+=stringvector[i]+" ";
        }    
    }

    messageBox(msclr::interop::marshal_as<String^>(sMessageReq));
}

std::string send_request(const std::string& host1, const std::string& port1, boost::beast::http::verb method, const std::string& target, const std::string& body = "") {
    try {
        std::string host = host1;
        auto const  port = "80";
        auto const  text = body;
        int version = 11;
        boost::asio::io_context ioc;

        // These objects perform our I/O
        tcp::resolver resolver{ ioc };
        boost::beast::tcp_stream stream(ioc);

        auto const results = resolver.resolve(host, port);

        stream.connect(results);

        boost::beast::http::request< boost::beast::http::string_body> req{ boost::beast::http::verb::post, target, version };
        req.set(boost::beast::http::field::host, host);
        //req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
           // Content - Type: text / plain; charset = utf - 8\r\n
        req.set(boost::beast::http::field::content_type, "text/plain; charset=utf-8");
        req.set(boost::beast::http::field::accept, "application/json");
        req.set(boost::beast::http::field::connection, "Keep-Alive");
        req.set(boost::beast::http::field::expect, "100-continue");
        req.body() = text;
        req.prepare_payload();
        boost::beast::error_code ec;

        boost::beast::http::write(stream, req);

        // This buffer is used for reading and must be persisted
        boost::beast::flat_buffer buffer;

        // Declare a container to hold the response
        boost::beast::http::response<boost::beast::http::dynamic_body> res;

        // Receive the HTTP response
       // boost::beast::http::read(stream, buffer, res);  

        //boost::beast::http::basic_parser<false, boost::beast::http::string_body> response_parser;
       // boost::beast::http::read_some(stream, buffer, res);
        std::string strRes;
        for (boost::beast::http::response<boost::beast::http::string_body> res; !ec && read(stream, buffer, res, ec); res.clear()) {
            strRes=res.body();
        }


        // Gracefully close the socket
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);
      
         return strRes;
    }
    catch (std::exception& e) {
        return std::string("Client error: ") + e.what();
    }
}
std::string BaseForm::postData(std::string sPostData)
{
    std::string post = "POST / HTTP/1.1\r\nHost: http://172.245.127.93/p/applicants.php\r\n\r\n";
    post += "{ \"cmd\": 1, \"rid\" : \" % ”Õ» ¿À‹Õ€…_»ƒ≈Õ“»‘» ¿“Œ–% \", \"data\" : \" % ÿ»‘–Œ¬¿ÕÕ¿ﬂ_—“–Œ ¿% \" }\r\n\r\n";//ÚÛÚ ÒÓ‰ÂÊËÏÓÂ Á‡ÔÓÒ‡, ÔÓ‰ÒÚ‡‚ËÚ¸ ÔÓ ‚ÍÛÒÛ
    post += "Content-Type", "application/json";
    std::string host = "172.245.127.93";
    std::string port = "80";
    std::string response = send_request(host, port, boost::beast::http::verb::post,  "/p/applicants.php", sPostData);
        
    int pause = 0;
    return response;
}

void BaseForm::gridRefreshThread()
{
    while (true)
    {
    gridRefresh();
    System::Threading::Thread::Sleep(10000);
    }
}
void BaseForm::gridRefresh()
{    
        mapList.clear();
        std::string s11 = Crypto::getUid();
        std::string s12 = Crypto::encryptDecrypt(s11, key);
        std::string s13 = Crypto::encryptDecrypt(s12, key);
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
                    mapUid[p.first] = Crypto::getUid();
                }
                else
                {
                    std::string s = mapGrid[p.first];
                    if (mapGrid[p.first] !=p.second)
                    {
                        rowschange(msclr::interop::marshal_as<String^>(std::to_string(p.first)), msclr::interop::marshal_as<String^>(getNameFromMap(p.second)), i);
                        mapGrid[p.first] = p.second;
                        mapUid[p.first] = Crypto::getUid();
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
    //if (s.find('[') != s.npos) {
    //    std::string sNameAfter;
    //   std::getline(ss, sNameAfter, ' ');
    //    sName += sNameAfter;
    //}
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
        s = std::to_string(peProcessEntry.th32ProcessID)+" " + str +
        PrintModuleList(hStdOut, peProcessEntry.th32ProcessID) + "\n";
        stringstream ss(s);
        std::string sPID;
        std::getline(ss, sPID, ' ');
        if (s.find('[') != s.npos) {
            std::string sName;
            int numDel = s.find(' ');
            std::getline(ss, sName, ']');
            numDel += sName.rfind(' ');
            s.erase(numDel+1, 1);
            std::string sNameAfter;
        }
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
