#pragma once
#include "TIOFileManager.h"

namespace pss
{
	class TSingletons
	{
	public:
		static TSingletons*						getInstance();
		~TSingletons();
		void									init();
		TIOFileManager*							getIOFileManager();
		int										getNumberOfPlanetaryGears() const;
		int										getW() const;
		int										getNumberOfLinks() const;
		int										getNumberOfFrictions() const;
		int										getNumberOfBrakes() const;

	private:
												TSingletons();
												TSingletons(const TSingletons&) = delete;
		TSingletons&							operator=(TSingletons&) = delete;
		void									calculateNumbersOfElements();

		int										m_w;									//	число степеней свободы
		int										m_numberOfPlanetaryGears;				//	Количество планетарных рядов
		int										m_numberOfBrakes;						//	Количество тормозов
		int										m_numberOfFrictions;					//	Количество фрикционов
		int										m_numberOfLinks;						//	Количество связей
		int										m_codeSize;								//	Размер вектора кода
	};
}

