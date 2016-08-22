#pragma once

#include "GlobalDefines.h"

NS_CORE_START

	template <class T>
	void print(std::vector<T> vect, char* str /*= ""*/)
	{
		std::cout << std::endl;
		if(strcmp(str, "") != 0)
			std::cout << str << ":\n";
		for(int i = 0; i < vect.size(); i++)
			std::cout << vect[i] << '\t';
		std::cout << std::endl;
	}	//вывод на консоль одномерного вектора

	template<class T>
	int in_vect(const std::vector<T> &Vect, T Value, double E /*= 0*/)
	{
		int len = Vect.size();
		for(int i = 0; i < len; i++)
		if((Value <= Vect[i] + E) && (Value >= Vect[i] - E))
			return i;
		return -1;
	}	//возвращает позицию элемента Value в векторе Vect. Если элемент не найден - возвращает -1

	template<class T>
	bool del_repetition(std::vector<T> &Vect)
	{
		std::sort(Vect.begin(), Vect.end());
		for(int i = 0; i < Vect.size() - 1; i++)
		{
			if(Vect[i] == Vect[i + 1])
			{
				Vect.erase(Vect.begin() + i + 1);
				i = i - 1;
			}
		}
		return true;
	}	//удаляет из вектора Vect повторяющиеся элементы

NS_CORE_END
