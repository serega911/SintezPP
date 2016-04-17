#pragma once

#include <vector>

namespace pss{
	int											code_2_pos(int);	// RK: rename
	int											pos_2_code(int);	// RK: rename
	bool										next_combination_repetition(std::vector<int>&, int=4, int=0);
	bool										next_combination(std::vector<int>&, int);
	void										SetColor(int, int);		
	int											factorial(int);
	int											C_n_k(int, int);		// RK: rename

	template <class T>
	void print(std::vector<T> vect, char* str = "");

	template<class T>
	int in_vect(const std::vector<T> &Vect, T Value, double E = 0);

	template<class T>
	bool del_repetition(std::vector<T> &Vect);

	template <class T>
	T GAUS(std::vector<std::vector<T>> Sys, int elem);

}

#include "func_lib.inl"