#pragma once
#include <vector>
#include <fstream>

namespace pss{
	class TCode
	{
	public:
		TCode(int, int);
		TCode() = delete;
		~TCode(void);
		int										operator[](int i) const;				//	Оператор получения элемента вектора кода
		bool									setIn(int);								//	Установка звена, связанного со входом
		bool									setOut(int);							//	Установка звена, связанного со выходом
		bool									setLinks(std::vector<int>);				//	Установка связей
		bool									setFrictions(std::vector<int>);			//	Установка фрикционов
		bool									setBrakes(std::vector<int>);			//	Установка тормозов
		int										getNumberOfPlanetaryGears() const;
		int										getW() const;
		int										getNumberOfLinks() const;
		int										getNumberOfFrictions() const;
		int										getNumberOfBrakes() const;
		const std::vector<int>&					getCode() const;
		void									writeCodeToFile(std::ofstream&) const;
		void									writeParametersToFile(std::ofstream&) const;
		void									loadCodeFromFile(std::ifstream&);
		void									loadParametersFromFile(std::ifstream&);
		bool									check() const;
		void									print() const;							//	Вывод объекта на экран
		void									clear();
		int										size() const;
	private:
		std::vector<int>						m_code;									//	Вектор кода
		int										m_w;									//	число степеней свободы
		int										m_numberOfPlanetaryGears;				//	Количество планетарных рядов
		int										m_numberOfBrakes;						//	Количество тормозов
		int										m_numberOfFrictions;					//	Количество фрикционов
		int										m_numberOfLinks;						//	Количество связей
		int										m_codeSize;								//	Размер вектора кода
	};

}