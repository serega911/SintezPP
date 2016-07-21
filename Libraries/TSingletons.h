#pragma once

#include <vector>

#include "TIOFileManager.h"
#include "TRange.h"
#include "TI.h"

namespace pss
{

	struct InitialData
	{
		int										_w;									//	число степеней свободы
		int										_numberOfGears;						//	Количество реализуемых передач без прямой
		int										_numberOfPlanetaryGears;			//	Количество планетарных рядов
		std::vector<TRange>						_ranges;
		TI										_i;
	};

	struct GeneralData
	{
		int										_numberOfActuatedDrivingElements;	//	Количество управляющих элементов, необходимых для включения передачи
		int										_numberOfFrictions;					//	Количество фрикционов
		int										_numberOfBrakes;					//	Количество тормозов
		int										_numberOfLinks;						//	Количество связей
		int										_codeSize;							//	Размер вектора кода
	};


	class TSingletons
	{
	public:

		static TSingletons*						getInstance();
		~TSingletons();

		TIOFileManager*							getIOFileManager();

		const GeneralData&						getGeneralData() const;
		const InitialData&						getInitialData() const;

		void									setGlobalParameters(int w, int n);
		void									addRangeK( const TRange& range );
		void									addGearRatio( const float& i );

	private:
												TSingletons();
												TSingletons(const TSingletons&) = delete;
		TSingletons&							operator=(TSingletons&) = delete;
		void									calculateNumbersOfElements();

		GeneralData								m_generalData;
		InitialData								m_initialData;
	};
}

