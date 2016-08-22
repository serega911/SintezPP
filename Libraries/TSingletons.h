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
	size_t										_w;									//	����� �������� �������
	size_t										_numberOfGears;						//	���������� ����������� ������� ��� ������
	size_t										_numberOfPlanetaryGears;			//	���������� ����������� �����
	std::vector<TRange>							_ranges;
	TI											_i;
};

struct GeneralData
{
	size_t										_numberOfActuatedDrivingElements;	//	���������� ����������� ���������, ����������� ��� ��������� ��������
	size_t										_numberOfFrictions;					//	���������� ����������
	size_t										_numberOfBrakes;					//	���������� ��������
	size_t										_numberOfLinks;						//	���������� ������
	size_t										_codeSize;							//	������ ������� ����
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

	static TSingletons*							getInstance();
	~TSingletons();

	TIOFileManager*								getIOFileManager();
	TLoaderFromFile*							getLoaderFromFile();

	const GeneralData&							getGeneralData() const;
	const InitialData&							getInitialData() const;

	void										setGlobalParameters(int w, int n);
	void										addRangeK( const TRange& range );
	void										addGearRatio( const double& i );

};

NS_CORE_END

