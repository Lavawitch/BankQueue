#ifndef MODIFY_H
#define MODIFY_H

#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
// ������ɫ��
#define FOREGROUND_CYAN (FOREGROUND_GREEN | FOREGROUND_BLUE)
// �����ɫ��
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
// �����ɫ��
#define FOREGROUND_WHITE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
//Ʒ��ɫ
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
