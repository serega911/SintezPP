#pragma once

#include <vector>

#include "TIOFileManager.h"
#include "TLoaderFromFile.h"
#include "TRange.h"
#include "TI.h"
#include "GlobalDefines.h"

NS_CORE_START

struct InitialData
{
	int										_w;									//	����� �������� �������
	int										_numberOfGears;						//	���������� ����������� ������� ��� ������
	int										_numberOfPlanetaryGears;			//	���������� ����������� �����
	std::vector<TRange>						_ranges;
	TI										_i;
};

struct GeneralData
{
	int										_numberOfActuatedDrivingElements;	//	���������� ����������� ���������, ����������� ��� ��������� ��������
	int										_numberOfFrictions;					//	���������� ����������
	int										_numberOfBrakes;					//	���������� ��������
	int										_numberOfLinks;						//	���������� ������
	int										_codeSize;							//	������ ������� ����
};


class TSingletons
{
private:

	TSingletons();
	TSingletons( const TSingletons& ) = delete;

	TSingletons&								operator=( TSingletons& ) = delete;

	void										calculateNumbersOfElements();

	GeneralData									m_generalData;
	InitialData									m_initialData;

public:

	static TSingletons*						getInstance();
	~TSingletons();

	TIOFileManager*							getIOFileManager();
	TLoaderFromFile*						getLoaderFromFile();

	const GeneralData&						getGeneralData() const;
	const InitialData&						getInitialData() const;

	void									setGlobalParameters(int w, int n);
	void									addRangeK( const TRange& range );
	void									addGearRatio( const float& i );

};

NS_CORE_END

