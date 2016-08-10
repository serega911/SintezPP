#pragma once
#include "TIOFileManager.h"
#include "TLoaderFromFile.h"

namespace pss
{
	class TSingletons
	{
	public:
		static TSingletons*						getInstance();
		~TSingletons();
		void									init();
		TIOFileManager*							getIOFileManager();
		TLoaderFromFile*							getLoaderFromFile( );
		int										getNumberOfPlanetaryGears() const;
		int										getNumberOfGears() const;
		int										getW() const;
		int										getNumberOfLinks() const;
		int										getNumberOfActuatedDrivingElements() const;
		int										getNumberOfFrictions() const;
		int										getNumberOfBrakes() const;

		void									setGlobalParameters(int w, int n);

	private:
												TSingletons();
												TSingletons(const TSingletons&) = delete;
		TSingletons&							operator=(TSingletons&) = delete;
		void									calculateNumbersOfElements();

		int										m_w;									//	����� �������� �������
		int										m_numberOfGears;						//	���������� ����������� ������� ��� ������
		int										m_numberOfActuatedDrivingElements;		//	���������� ����������� ���������, ����������� ��� ��������� ��������
		int										m_numberOfPlanetaryGears;				//	���������� ����������� �����
		int										m_numberOfBrakes;						//	���������� ��������
		int										m_numberOfFrictions;					//	���������� ����������
		int										m_numberOfLinks;						//	���������� ������
		int										m_codeSize;								//	������ ������� ����
	};
}

