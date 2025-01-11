#ifndef MODIFY_H
#define MODIFY_H

#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
// 定义青色宏
#define FOREGROUND_CYAN (FOREGROUND_GREEN | FOREGROUND_BLUE)
// 定义黄色宏
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
// 定义白色宏
#define FOREGROUND_WHITE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
//品红色
#define FOREGROUND_MAGENTA (FOREGROUND_RED | FOREGROUND_BLUE)
//highlight White
#define FOREGROUND_HBLUE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)
//gold
#define FOREGROUND_GOLD ( FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN)
void PrintSeparator() ;
void PrintDecorativeLine();
void PrintBottomSeparator();
void PrintFish();
#endif
