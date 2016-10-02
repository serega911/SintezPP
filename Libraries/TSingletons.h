#pragma once

#include <vector>

#include "TIOFileManager.h"
#include "TLoaderFromFile.h"
#include "TRange.h"
#include "TRangeArray.h"
#include "TI.h"
#include "GlobalDefines.h"
#include "TCombinatorics.h"

NS_CORE_START

struct InitialData
{
	size_t										_w;									//	����� �������� �������
	size_t										_numberOfGears;						//	���������� ����������� ������� ��� ������
	size_t										_numberOfPlanetaryGears;			//	���������� ����������� �����
	TRangeArray									_ranges;
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

	//void										calculateNumbersOfElements();

	GeneralData									m_generalData;
	InitialData									m_initialData;

public:

	static TSingletons*							getInstance();
	~TSingletons();

	TIOFileManager*								getIOFileManager();
	TLoaderFromFile*							getLoaderFromFile();
	TCombinatorics*								getCombinatorics();

	const GeneralData&							getGeneralData() const;
	const InitialData&							getInitialData() const;

	void										setGlobalParameters( const size_t w, const size_t n, const size_t d );
	void										setNumberOfGears( const size_t n );
	void										addRangeK( const TRange& range );
	void										addGearRatio( const double& i );

};

NS_CORE_END

