#pragma once

#include <vector>

#include "IOFileManager.h"
#include "LoaderFromFile.h"
#include "Range.h"
#include "RangeArray.h"
#include "Ratios.h"
#include "GlobalDefines.h"
#include "Combinatorics.h"
#include "Settings.h"

NS_CORE_START

struct InitialData
{
	size_t										_w;									//	����� �������� �������
	size_t										_numberOfGears;						//	���������� ����������� ������� ��� ������
	size_t										_realNumberOfGears;					//  ���������� ��������� ������������� �������
	size_t										_numberOfPlanetaryGears;			//	���������� ����������� �����
	RangeArray									_ranges;
	Ratios										_i;
};

struct GeneralData
{
	size_t										_numberOfActuatedDrivingElements;	//	���������� ����������� ���������, ����������� ��� ��������� ��������
	size_t										_numberOfFrictions;					//	���������� ����������
	size_t										_numberOfBrakes;					//	���������� ��������
	size_t										_numberOfLinks;						//	���������� ������
	size_t										_codeSize;							//	������ ������� ����
};


class Singletons
{
private:

	Singletons();
	Singletons( const Singletons& ) = delete;

	Singletons&									operator=( Singletons& ) = delete;

	GeneralData									m_generalData;
	InitialData									m_initialData;

public:

	static Singletons*							getInstance();
	~Singletons();

	IOFileManager*								getIOFileManager();
	LoaderFromFile*								getLoaderFromFile();
	Combinatorics*								getCombinatorics();
	Settings*									getSettings();

	const GeneralData&							getGeneralData() const;
	const InitialData&							getInitialData() const;

	void										setGlobalParameters( const size_t w, const size_t n, const size_t d );
	void										addRangeK( const Range& range );
	void										addGearRatio( const double& i );

};

NS_CORE_END

