#include "lib.hpp"
#include "ascii.hpp"
#include <iostream>
using namespace std;

#define FRONT_SPACE "\t"
#define INSIDE_SPACE "  "

// const char *tl = "╭";
// const char *tr = "╮";
// const char *bl = "╰";
// const char *br = "╯";
// const char *h  = "─";
const char *v  = "│";
const char *top  =   "╭─────────";
const char *bottom = "╰─────────";

int 
main(){
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
  
  winLogo();
  cout << FRONT_SPACE << top << endl;
  cout << FRONT_SPACE << v << INSIDE_SPACE; getUserInfo();
  cout << FRONT_SPACE << v << INSIDE_SPACE; findOsInfo();
  cout << FRONT_SPACE << v << INSIDE_SPACE; findOsBuildNo();
  cout << FRONT_SPACE << v << INSIDE_SPACE; getUptime();
  cout << FRONT_SPACE << v << INSIDE_SPACE; getDisplayInfo();
  cout << FRONT_SPACE << v << INSIDE_SPACE; getCpuVendor();
  cout << FRONT_SPACE << v << INSIDE_SPACE; getCpuArchitecture();
  cout << FRONT_SPACE << v << INSIDE_SPACE; getCpuInfo();
  cout << FRONT_SPACE << v << INSIDE_SPACE; getMemoryInfo();
  ListGpus();
  cout << FRONT_SPACE << v << INSIDE_SPACE; getRenderEngine();
  getDriveInfo();
  cout << FRONT_SPACE << v << INSIDE_SPACE; getPowerInfo();
  cout << FRONT_SPACE << v << INSIDE_SPACE; getBatteryStatus();
  cout << FRONT_SPACE << v << INSIDE_SPACE; getLocalIP();
  cout << FRONT_SPACE << v << INSIDE_SPACE; getLanguageLocale();
  cout << FRONT_SPACE << bottom << endl;
  colourBoxes();

  return 0;
};


















