#include "func_lib.h"

#include <Windows.h>
#include <iostream>
#include <set>

void NS_CORE SetColor( int text, int background )
{
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}