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

		int										m_w;									//	����� �������� �������
		int										m_numberOfPlanetaryGears;				//	���������� ����������� �����
		int										m_numberOfBrakes;						//	���������� ��������
		int										m_numberOfFrictions;					//	���������� ����������
		int										m_numberOfLinks;						//	���������� ������
		int										m_codeSize;								//	������ ������� ����
	};
}

