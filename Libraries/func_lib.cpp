#include "func_lib.h"

#include <Windows.h>
#include <iostream>
#include <set>


bool NS_CORE next_combination_repetition(std::vector<int>&v1, int max_value, int min_value){
	int k = static_cast<int>(v1.size());
	for (int i = k - 1; i >= 0; --i)
		if (v1[i] != min_value-1)
			if (v1[i] < max_value)
			{
				++v1[i];
				return true;
			}
			else
			{
				v1[i] = min_value;
			}
	return false;
}	//генерирует следующее сочетание с повторением
	
void NS_CORE SetColor( int text, int background )
{
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

int NS_CORE factorial( int a )
{
	if (a == 0) return 0;
	int ans = 1;
	for (int i = 2; i < a; i++)
		ans *= i;
	return ans;
}

int NS_CORE C_n_k( int n, int k )
{
	return NS_CORE factorial( n ) / ( NS_CORE factorial( k )*NS_CORE factorial( n - k ) );
}	//количество сочетаний из n по k;