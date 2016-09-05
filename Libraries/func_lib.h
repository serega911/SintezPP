#pragma once

#include <vector>

#include "GlobalDefines.h"

NS_CORE_START

	void										SetColor(int, int);		

	template <class T>
	void print(std::vector<T> vect, char* str = "");

	template<class T>
	int in_vect(const std::vector<T> &Vect, T Value, double E = 0);

	template<class T>
	bool del_repetition(std::vector<T> &Vect);

NS_CORE_END

#include "func_lib.inl"