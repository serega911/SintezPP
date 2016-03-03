#pragma once
#include<vector>

namespace pss{
	int code_2_pos(int);
	int pos_2_code(int);
	bool next_combination_repetition(std::vector<int>&, int=4, int=0);
	bool next_combination(std::vector<int>&, int);
	void SetColor(int, int);
	int factorial(int);
	int C_n_k(int, int);

	template <class T>
	void print(std::vector<T> vect, char* str = "")
	{
		std::cout << std::endl;
		if (strcmp(str, "") != 0)
			std::cout << str << ":\n";
		for (int i = 0; i < vect.size(); i++)
			std::cout << vect[i] << '\t';
		std::cout << std::endl;
	}	//вывод на консоль одномерного вектора

	template<class T>
	int in_vect(const std::vector<T> &Vect, T Value, float E = 0)
	{
		int len = Vect.size();
		for (int i = 0; i < len; i++)
			if ((Value <= Vect[i] + E) && (Value >= Vect[i] - E))
				return i;
		return -1;
	}	//возвращает позицию элемента Value в векторе Vect. Если элемент не найден - возвращает -1

	template<class T>
	bool del_repetition(std::vector<T> &Vect){
		std::sort(Vect.begin(), Vect.end());
		for (int i = 0; i < Vect.size() - 1; i++){
			if (Vect[i] == Vect[i + 1]){
				Vect.erase(Vect.begin() + i + 1);
				i = i - 1;
			}
		}
		return true;
	}	//удаляет из вектора Vect повторяющиеся элементы

	template <class T>
	T GAUS(std::vector<std::vector<T>> Sys, int elem)
	{
		const double EPS = 0.0001;
		int n = Sys.size();
		std::vector<T> ans;
		for (int i = 0; i < n; ++i) {
			int k = i;
			for (int j = i + 1; j<n; ++j)
				if (abs(Sys[j][i]) > abs(Sys[k][i]))
					k = j;
			if (k != i)
				std::swap(Sys[i], Sys[k]);
			for (int j = i + 1; j <= n; ++j)
				if (Sys[i][i] != 0)
					Sys[i][j] /= Sys[i][i];
				else
					return 0;
			for (int j = 0; j < n; ++j)
				if (j != i)
					for (int k = i + 1; k <= n; ++k)
						Sys[j][k] -= Sys[i][k] * Sys[j][i];
		}
		for (int i = 0; i < n; ++i)
			ans.push_back(Sys[i][n]);
		return ans[elem];
	}	//находит решение x[elem] системы уравнений Sys методом Гаусса

}