#pragma once
#include "func_lib.h"
#include <Windows.h>
#include <iostream>

#include <set>

int pss::code_2_pos(int code)
{
	if (code/10 > 3)
		return -1;
	else
		return (code % 10 - 1) * 3 + code / 10 - 1;
}

int pss::pos_2_code(int pos)
{
	if (pos < 0)
		return -1;
	else
		return (pos % 3 + 1) * 10 + (pos / 3 + 1);
}

bool pss::next_combination_repetition(std::vector<int>&v1, int max_value, int min_value){
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
	
bool pss::next_combination(std::vector<int>&v1, int max_value)
{
	if (v1.size() == 0)  return false;
	std::vector<int>tmp;
	int m = v1.size();
	tmp = v1;
	int x = 1;
	if (tmp[m-1] < max_value)
		tmp[m-1]++;
	else{ 
		if (m == 1) return false;
		for (int i = 1; i < m; i++)
			if (tmp[i] > i+max_value-m){
				x = i;
				break;
			}
		tmp[x-1]++;
		for (int i = x; i < m; i++)
			tmp[i] = tmp[i-1] + 1;
	}
	if (tmp[0] > max_value-m+1){
		return false;
	}	
	v1 = tmp;
	return true;
}	//генерирует следующее сочетание без повторений

void pss::SetColor(int text, int background)
{
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

int pss::factorial(int a)
{
	if (a == 0) return 0;
	int ans = 1;
	for (int i = 2; i < a; i++)
		ans *= i;
	return ans;
}

int pss::C_n_k(int n, int k)
{
	return pss::factorial(n) / (pss::factorial(k)*pss::factorial(n - k));
}	//количество сочетаний из n по k;