#include <dxgi1_2.h>
#include <iostream>
#include <vector>
#define FRONT_SPACE "\t"
#define LOGO_SPACE "\t\t"

#pragma comment(lib, "Dxgi.lib")

/*
Console Color Codes for SetConsoleTextAttribute
Code 	Color
0	Black
1	Blue
2	Green
3	Aqua/Cyan
4	Red
5	Purple/Magenta
6	Yellow/Brown
7	White/Light Gray
8	Gray/Dark Gray
9	Bright Blue/Light Blue
10	Bright Green/Lime
11	Bright Aqua/Light Cyan
12	Bright Red/Light Red
13	Bright Purple/Light Magenta
14	Bright Yellow
15	Bright White
*/

void 
SetColor(WORD color){
  HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(h, color);
};


void 
winLogo(){
  SetColor(2);
  std::cout <<LOGO_SPACE<< "__        ___           _" << std::endl;
  std::cout <<LOGO_SPACE<< "\\ \\      / (_)_ __   __| | _____      _____" << std::endl;
  SetColor(6);
  std::cout <<LOGO_SPACE<< " \\ \\ /\\ / /| | '_ \\ / _` |/ _ \\ \\ /\\ / / __|" << std::endl; 
  SetColor(9);
  std::cout <<LOGO_SPACE<< "  \\ V  V / | | | | | (_| | (_) \\ V  V /\\__ \\_" << std::endl; 
  SetColor(5);
  std::cout <<LOGO_SPACE<< "   \\_/\\_/  |_|_| |_|\\__,_|\\___/ \\_/\\_/ |___(_)" << std::endl; 
  SetColor(7);
};



void 
colourBoxes(){
  const char* row1 = "╭╮";
  const char* row2 = "╰╯";

  // Row 1
  std::cout << FRONT_SPACE;
  SetColor(8);
  std::cout << row1;
  SetColor(12);
  std::cout << row1;
  SetColor(10);
  std::cout << row1;
  SetColor(14);
  std::cout << row1;
  SetColor(1);
  std::cout << row1;
  SetColor(13);
  std::cout << row1;
  SetColor(9);
  std::cout << row1;
  SetColor(7);
  std::cout << row1 << std::endl;

  // Row 2
  std::cout << FRONT_SPACE;
  SetColor(8);
  std::cout << row2;
  SetColor(12);
  std::cout << row2;
  SetColor(10);
  std::cout << row2;
  SetColor(14);
  std::cout << row2;
  SetColor(1);
  std::cout << row2;
  SetColor(13);
  std::cout << row2;
  SetColor(9);
  std::cout << row2;
  SetColor(7);
  std::cout << row2 << std::endl;
};




