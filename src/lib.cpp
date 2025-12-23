#include <WS2tcpip.h>
#include <Windows.h>
#include <winternl.h>
#include <dxgi1_2.h>
#include <Lmcons.h>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <intrin.h>
#include <cstdint>
#include <chrono>
#include "ascii.hpp"

// optional backup
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Dxgi.lib")
#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "User32.lib")

#define FRONT_SPACE "\t"
#define INSIDE_SPACE "  "

typedef LONG (WINAPI* RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);

void
getUserInfo(){
  TCHAR username[UNLEN + 1], hostname[UNLEN + 1];
  DWORD usersize = sizeof(username) / sizeof(TCHAR);
  DWORD hostsize = sizeof(hostname) / sizeof(TCHAR);

  SetColor(14);
  std::cout << "User: ";
  SetColor(7);
  if (GetUserName((TCHAR *)username, &usersize) && GetComputerName((TCHAR *)hostname, &hostsize)){
  SetColor(3);
  std::wcout << username;
  SetColor(7);
  std::cout << "@";
  SetColor(3);
  std::wcout << hostname << std::endl;
  }else{
  SetColor(4);
  std::cout << "Unknown";
  SetColor(7);
  std::cout << "@";
  SetColor(4);
  std::wcout << "Unknown" << std::endl;
  }
  SetColor(7);
};

void
findOsInfo(){
  RTL_OSVERSIONINFOW rovi;
  rovi.dwOSVersionInfoSize = sizeof(rovi);

  SetColor(14);
  std::cout << "OS: ";
  SetColor(7);

  RtlGetVersionPtr fx = (RtlGetVersionPtr)GetProcAddress(
    GetModuleHandleW(L"ntdll.dll"),
    "RtlGetVersion"
  );

  if (!fx || fx(&rovi) != 0) {
    SetColor(4);
    std::cout << "OS: Unknown"  << std::endl;
    SetColor(7);
  }

  if (rovi.dwMajorVersion == 10 && rovi.dwBuildNumber >= 22000)
    std::cout << "Windows 11"  << std::endl;
  else if (rovi.dwMajorVersion == 10)
    std::cout << "Windows 10"  << std::endl;
  else
    std::cout << "Windows " 
              << rovi.dwMajorVersion 
              << "." 
              << rovi.dwMinorVersion 
              << std::endl;
};

void
findOsBuildNo(){
  RTL_OSVERSIONINFOW rovi;
  rovi.dwOSVersionInfoSize = sizeof(rovi);

  RtlGetVersionPtr fx = (RtlGetVersionPtr)GetProcAddress(
    GetModuleHandleW(L"ntdll.dll"),
    "RtlGetVersion"
  );

  SetColor(14);
  std::cout << "Build No: ";
  SetColor(7);

  if (fx && fx(&rovi) == 0)
  std::cout << rovi.dwBuildNumber << std::endl;
  else{
    SetColor(4);
    std::cout << "Unknown" << std::endl;
    SetColor(7);
  }
};

void
getUptime(){
  auto ms = std::chrono::milliseconds(GetTickCount64());
  auto uptime = std::chrono::duration_cast<std::chrono::seconds>(ms).count();
  int days = uptime / (60 * 60 * 24);
  int hours = (uptime / (60 * 60)) % 24;
  int minutes = (uptime / 60) % 60;
  
  SetColor(14);
  std::cout << "Uptime:";
  SetColor(7);
  std::cout << " D:";
  SetColor(10);
  std::cout << days;
  SetColor(7);
  std::cout << " H:";
  SetColor(10);
  std::cout << hours;
  SetColor(7);
  std::cout << " M:";
  SetColor(10);
  std::cout << minutes << std::endl;
  SetColor(7);
};

/*
    <<<< Display >>>>
*/

void
getDisplayInfo(){
  DEVMODEW dm;
  dm.dmSize = sizeof(dm);
  SetColor(14);
  std::cout << "Display: ";
  SetColor(7);

  if (!EnumDisplaySettingsW(NULL, ENUM_CURRENT_SETTINGS, &dm)) {
    SetColor(4);
    std::cout << "Failed to get display info" << std::endl;
    SetColor(7);
  }else{
    std::cout << dm.dmPelsWidth << "x" << dm.dmPelsHeight << " @ ";
    SetColor(5);
    std::cout << dm.dmDisplayFrequency;
    SetColor(7);
    std::cout << "Hz" << std::endl;
  }
};

/* 
    <<<< CPU >>>>
*/

void
getCpuVendor(){
  int cpuInfo[4] = { 0 };
  __cpuid(cpuInfo, 0);

  char vendor[13];
  memcpy(vendor + 0, &cpuInfo[1], 4);  // EBX
  memcpy(vendor + 4, &cpuInfo[3], 4);  // EDX
  memcpy(vendor + 8, &cpuInfo[2], 4);  // ECX
  vendor[12] = '\0';

  SetColor(14);
  std::cout << "CPU Vendor: ";
  SetColor(7);
  std::cout << vendor << std::endl;
};

void
getCpuArchitecture(){
  SYSTEM_INFO si;
  GetNativeSystemInfo(&si);

  SetColor(14);
  std::cout << "CPU Architecture: ";
  SetColor(7);
  if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) std::cout << "x86_64" << std::endl;
  else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL) std::cout << "x86" << std::endl;
  else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM64) std::cout << "ARM64" << std::endl;
  else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM) std::cout << "ARM" << std::endl;
  else{ 
    SetColor(4);
    std::cout << "Unknown" << std::endl;
  }
};

void
getCpuInfo(){
  SYSTEM_INFO si;
  DWORD len = 0;
  int cpuInfo[4];
  char brand[49];
  int physicalCores = 0;
  GetNativeSystemInfo(&si);
  GetLogicalProcessorInformation(nullptr, &len);

  std::vector<uint8_t> buffer(len);
  PSYSTEM_LOGICAL_PROCESSOR_INFORMATION info = reinterpret_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION>(buffer.data());
  GetLogicalProcessorInformation(info, &len);
  DWORD count = len / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
  for (DWORD i = 0; i < count; i++) {
  if (info[i].Relationship == RelationProcessorCore)
  physicalCores++;
  }

  __cpuid(cpuInfo, 0x80000002);
  memcpy(brand, cpuInfo, sizeof(cpuInfo));

  __cpuid(cpuInfo, 0x80000003);
  memcpy(brand + 16, cpuInfo, sizeof(cpuInfo));

  __cpuid(cpuInfo, 0x80000004);
  memcpy(brand + 32, cpuInfo, sizeof(cpuInfo));

  brand[48] = '\0';

  SetColor(14);
  std::cout << "CPU Model: ";
  SetColor(7);
  std::cout << brand << " (";
  SetColor(10);
  std::cout << physicalCores;
  SetColor(7);
  std::cout << ":";
  SetColor(10);
  std::cout << si.dwNumberOfProcessors;
  SetColor(7);
  std::cout << ")" << std::endl;

};

/*
    <<<< RAM >>>>
*/

void
getMemoryInfo(){
  MEMORYSTATUSEX mem;
  std::ostringstream oss;
  mem.dwLength = sizeof(mem);
  GlobalMemoryStatusEx(&mem);

  SetColor(14);
  std::cout << "Memory: ";
  SetColor(7);
  std::cout <<((mem.ullTotalPhys-mem.ullAvailPhys)/(1024 * 1024)) << " MiB / "
            << (mem.ullTotalPhys/(1024 * 1024 * 1024)) <<" GiB (";
  SetColor(10);
  std::cout <<  mem.dwMemoryLoad << "%";
  SetColor(7);
  std::cout << ")" << std::endl;
  
};

/*
        <<<<< GPU >>>>>
*/

/* Get gpu vram */
std::string 
MemToString(UINT64 bytes) {
  std::ostringstream oss;
  double mib = bytes / (1024.0 * 1024.0);
  if (mib >= 1024) 
  oss << std::round(mib / 1024.0) << " GiB";
  else
  oss << std::round(mib) << " MiB";

  return oss.str();
};

/* Get Type */
std::string
getGpuType(DXGI_ADAPTER_DESC1* desc) {
  if (desc->Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
  return "Software";

  // VendorId: Intel = integrated, NVIDIA/AMD = discrete
  switch (desc->VendorId) {
  case 0x8086: return "Integrated"; // Intel
  case 0x10DE: return "Discrete";   // NVIDIA
  case 0x1002: return "Discrete";   // AMD
  default: return "Unknown";
  }
};

/* List gpu */
void
ListGpus(){
  UINT index = 0;
  IDXGIAdapter1* adapter = nullptr;
  IDXGIFactory2* factory = nullptr;
  const char *v  = "│";

  if (FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory2), (void**)&factory))) {
    SetColor(4);
    std::cout << "Unknown" << std::endl;
    SetColor(7);
  }

  while (factory->EnumAdapters1(index, &adapter) != DXGI_ERROR_NOT_FOUND) {
  DXGI_ADAPTER_DESC1 desc;
  adapter->GetDesc1(&desc);

  std::wstring wname(desc.Description);
  std::string name(wname.begin(), wname.end());

  std::string type = getGpuType(&desc);
  std::string vram = MemToString(desc.DedicatedVideoMemory);
  std::cout << FRONT_SPACE << v << INSIDE_SPACE;
  SetColor(14);
  std::cout << "GPU " << (index+1) << ": ";
  SetColor(7);
  std::cout << name << " (";
  SetColor(5);
  std::cout << vram;
  SetColor(7);
  std::cout << ") [";
  SetColor(1);
  std::cout << type;
  SetColor(7);
  std::cout << "]" << std::endl;

  adapter->Release();
  index++;
  }
  factory->Release();
};

// This is for fun :(
void
getRenderEngine(){
  SetColor(14);
  std::cout << "Render Engine: ";
  SetColor(7);
  std::cout << "Microsoft DirectX" << std::endl;
};
/*
        <<<<< DRIVE >>>>>
*/

void 
getDriveInfo(){  
  DWORD drives = GetLogicalDrives();
  const char *v  = "│";
  if (!drives){
    SetColor(4);
    std::cout << "Failed to get drives" << std::endl;
    SetColor(7);
  };

  wchar_t rootPath[] = L"A:\\";

  for (int i = 0; i < 26; i++) {
    if (drives & (1 << i)) {
      rootPath[0] = L'A' + i;

      ULARGE_INTEGER freeCaller, totalBytes, freeBytes;

      if (GetDiskFreeSpaceExW(rootPath, &freeCaller, &totalBytes, &freeBytes)) {

          ULONGLONG total  = totalBytes.QuadPart;
          ULONGLONG free   = freeBytes.QuadPart;
          ULONGLONG used   = total - free;

          double percentUsed = std::round((double)used / total * 100.0);
          std::cout << FRONT_SPACE << v << INSIDE_SPACE;
          SetColor(14);
          std::wcout <<"Drive "<< rootPath << " ";
          SetColor(7);
          std::cout<<(double)(free)/(1024 * 1024 * 1024) << " GiB / "
                    <<(double)(total)/(1024 * 1024 * 1024) << " GiB (";
          SetColor(10);
          std::cout<<percentUsed<<"%";
          SetColor(7);
          std::cout << ")" << std::endl;
      }
    }
  }
};


/*
        <<<<< Power >>>>>
*/
void 
getPowerInfo(){
  SYSTEM_POWER_STATUS ps;

  if (!GetSystemPowerStatus(&ps)) {
    SetColor(4);
    std::cout << "Failed to get Ac Info" << std::endl;
    SetColor(7);
  }

  SetColor(14);
  std::cout << "Power Status: ";
  SetColor(7);

  if (ps.ACLineStatus == 0) std::cout << "Unplugged "<< std::endl;
  else if (ps.ACLineStatus == 1) std::cout << "PlugedIn "<< std::endl;
  else{
    SetColor(4);
    std::cout << "Unknown " << std::endl;
    SetColor(7);
  }
};

void 
getBatteryStatus(){
  SYSTEM_POWER_STATUS ps;

  if (!GetSystemPowerStatus(&ps)) {
    SetColor(4);
    std::cout << "Failed to get Ac Info" << std::endl;
    SetColor(7);
  }

  SetColor(14);
  std::cout << "Battery Percentage: ";
  SetColor(7);

  if (ps.BatteryLifePercent == 255){
    SetColor(4);
    std::cout << "Unknown" << std::endl;
    SetColor(7);
  }else{
    SetColor(10);
    std::wcout << (ps.BatteryLifePercent) << "%" << std::endl;
    SetColor(7);
  }

};

/*
        <<<<< Locale >>>>>
*/
void 
getLocalIP() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        SetColor(4);
        std::cout << "Unknown IP" << std::endl;
        SetColor(7);
        return;
    }

    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        WSACleanup();
        SetColor(4);
        std::cout << "Unknown IP" << std::endl;
        SetColor(7);
        return;
    }

    addrinfo hints = {};
    hints.ai_family   = AF_INET;     // IPv4
    hints.ai_socktype = SOCK_STREAM; // Required for many systems
    hints.ai_protocol = IPPROTO_TCP;

    addrinfo* result = nullptr;
    if (getaddrinfo(hostname, nullptr, &hints, &result) != 0 || result == nullptr) {
        WSACleanup();
        SetColor(4);
        std::cout << "Unknown IP" << std::endl;
        SetColor(7);
        return;
    }

    // Extract IPv4 address
    sockaddr_in* addr = reinterpret_cast<sockaddr_in*>(result->ai_addr);

    char ipStr[50] = {0};
    if (!InetNtopA(AF_INET, &(addr->sin_addr), ipStr, sizeof(ipStr))) {
        freeaddrinfo(result);
        WSACleanup();
        SetColor(4);
        std::cout << "Unknown IP" << std::endl;
        SetColor(7);
        return;
    }

    freeaddrinfo(result);
    WSACleanup();

    SetColor(14);
    std::cout << "Local IP: ";
    SetColor(7);
    std::cout << ipStr << std::endl;
}

// void
// getLocalIP(){
//   WSADATA wsaData;
//   WSAStartup(MAKEWORD(2, 2), &wsaData);

//   char hostname[256];
//   if (gethostname(hostname, sizeof(hostname)) != 0) {
//     WSACleanup();
//   }

//   addrinfo hints;
//   hints.ai_family = AF_INET; // IPv4 only

//   addrinfo* result = nullptr;
//   if (getaddrinfo(hostname, nullptr, &hints, &result) != 0) {
//     WSACleanup();
//     SetColor(4);
//     std::cout << "Unknown IP" << std::endl;
//     SetColor(7);
//   }

//   // Convert binary IP → string
//   char ipStr[50];
//   sockaddr_in* addr = (sockaddr_in*)result->ai_addr;

//   InetNtopA(AF_INET, &(addr->sin_addr), ipStr, sizeof(ipStr));

//   // Free only result (DO NOT free addr)
//   freeaddrinfo(result);
//   WSACleanup();

//   SetColor(14);
//   std::cout << "Local IP: ";
//   SetColor(7);
//   std::cout << ipStr << std::endl;
// };

void
getLanguageLocale(){
  wchar_t localeName[LOCALE_NAME_MAX_LENGTH];

  if (GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH)) {      
    // Convert wide → UTF-8
  int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, localeName, -1, nullptr, 0, nullptr, nullptr);
        
  std::string utf8(sizeNeeded, 0);

  WideCharToMultiByte(CP_UTF8, 0, localeName, -1, &utf8[0], sizeNeeded, nullptr, nullptr);

  SetColor(14);
  std::cout << "Locale: ";
  SetColor(7);
  // Remove trailing null character
  if (!utf8.empty() && utf8.back() == '\0')
    utf8.pop_back();
    std::cout << utf8 << std::endl;
  }else{
  SetColor(4);
  std::cout << "Unknown Locale Language" << std::endl;
  SetColor(7);
  }
};


