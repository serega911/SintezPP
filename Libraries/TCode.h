#pragma once
#include <vector>
#include <fstream>

#include "../Libraries/IContainer.h"
#include "../Libraries/TLink.h"
#include "../Libraries/TChain.h"

namespace pss{
	class TCode: public pss::IContainer
	{
	private:
		std::vector<TLink>						m_code;									//	Вектор кода
		int										m_codeSize;								//	Размер вектора кода

		std::vector<TChain>						m_chains;

		int										m_links;
		int										m_frictions;
		int										m_brakes;

		void									createChains();

	public:
		TCode();
		~TCode(void);
		TLink									operator[](int i) const;				//	Оператор получения элемента вектора кода
		void									setIn(const TElement & in);								//	Установка звена, связанного со входом
		void									setOut(const TElement & out);							//	Установка звена, связанного со выходом
		void									setLinks(const std::vector<TLink>& links);				//	Установка связей
		void									setFrictions(const std::vector<TLink>& frictions);			//	Установка фрикционов
		void									setBrakes(const std::vector<TLink>& brakes);			//	Установка тормозов

		const std::vector<TLink>&				getCode() const;
		TLink										getIn() const;
		TLink										getOut() const;
		const std::vector<TChain>&				getChains() const;
		const std::vector<TElement>				getElementsForFrictions() const;
		const std::vector<TElement>				getElementsForBrakes() const;
		void									writeToFile(std::ofstream&) const override;
		void									loadFromFile(std::ifstream&) override;
		bool									checkFree() const;
		bool									check() const;
		void									print() const;							//	Вывод объекта на экран
		void									clear();
		int										size() const override;
	
	};

	bool operator<(const TCode& code1, const TCode& code2);
}

