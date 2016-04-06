#pragma once

#include <string>
#include <fstream>
#include <map>

#include "../Libraries/IContainer.h"

namespace pss
{
	class TIOFileManager
	{
	public:

		enum class eOutputFileType
		{
			INITIAL_DATA,	// initial data - W N Count_L Count_F Count_B
			DONE,			// done
			DONE_K,			// done K
			FAIL_N,			// wrong number of elements for brakes and frictions
			FAIL_0,			// links from in to out or between elements of one planetary mechanism
			FAIL_FREE,		// after setting frictions and brakes there are free elements
			FAIL_REPETTION	// scheme has already exist 
		};

		static TIOFileManager*					getInstance();
		~TIOFileManager();
		void									init();
		std::string								getFolder();

		void									writeToFile(eOutputFileType type, const IContainer & container);
		bool									loadFromFile(eOutputFileType type, IContainer & container);
		
		void									writeSolutionData();
	private:
		
		std::map<eOutputFileType, std::string>	m_fileNames;

												TIOFileManager();
												TIOFileManager(const TIOFileManager&) = delete;
		TIOFileManager&							operator=(TIOFileManager&) = delete;

		static const std::string				s_globalFolder;
		std::string								m_containingFolder;
		
		std::map<eOutputFileType, std::ofstream*> m_oFiles;

		std::map<eOutputFileType, std::ifstream*> m_iFiles;
		
	};

	



}