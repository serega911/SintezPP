#pragma once
#include <vector>
#include <fstream>

#include "../Libraries/IContainer.h"

namespace pss{
	class TCode: public pss::IContainer
	{
	public:
		TCode();
		~TCode(void);
		int										operator[](int i) const;				//	Оператор получения элемента вектора кода
		bool									setIn(int);								//	Установка звена, связанного со входом
		bool									setOut(int);							//	Установка звена, связанного со выходом
		bool									setLinks(std::vector<int>);				//	Установка связей
		bool									setFrictions(std::vector<int>);			//	Установка фрикционов
		bool									setBrakes(std::vector<int>);			//	Установка тормозов

		const std::vector<int>&					getCode() const;
		void									writeToFile(std::ofstream&) const override;
		void									loadFromFile(std::ifstream&) override;
		bool									check() const;
		void									print() const;							//	Вывод объекта на экран
		void									clear();
		int										size() const override;
	private:
		std::vector<int>						m_code;									//	Вектор кода
		int										m_codeSize;								//	Размер вектора кода

		int										m_links;
		int										m_frictions;
		int										m_brekes;
	};

}