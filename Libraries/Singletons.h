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
	size_t										_w;									//	число степеней свободы
	size_t										_numberOfGears;						//	Количество реализуемых передач без прямой
	size_t										_realNumberOfGears;					//  Количество введенных пользователем передач
	size_t										_numberOfPlanetaryGears;			//	Количество планетарных рядов
	RangeArray									_ranges;
	Ratios										_i;
};

struct GeneralData
{
	size_t										_numberOfActuatedDrivingElements;	//	Количество управляющих элементов, необходимых для включения передачи
	size_t										_numberOfFrictions;					//	Количество фрикционов
	size_t										_numberOfBrakes;					//	Количество тормозов
	size_t										_numberOfLinks;						//	Количество связей
	size_t										_codeSize;							//	Размер вектора кода
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

