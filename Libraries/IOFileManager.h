#pragma once

#include <string>
#include <fstream>
#include <map>

#include "IIOItem.h"
#include "GlobalDefines.h"

NS_CORE_START

class IOFileManager
{
public:

	enum class eOutputFileType
	{
		INITIAL_DATA,	// initial data - W N Count_L Count_F Count_B
		DONE,			// done
		DONE_K,			// done K
		DONE_K_NUTON,			// done K
		DONE_K_SIMPLE,			// done K
		DONE_K_SELECTION,		// done K
		FAIL_N,			// wrong number of elements for brakes and frictions
		FAIL_0,			// links from in to out or between elements of one planetary mechanism
		FAIL_FREE,		// after setting frictions and brakes there are free elements
		FAIL_REPETTION,	// scheme has already exist 
		FAIL_NUTON,		// Nuton algorithm failed
		KIN_QUICK,
		KIN_SLOW,
		SETTINGS,
		K_TEST,
		DEF_K_LOG,
		RESULT			// Final results
	};

	class End : public IIOItem
	{
	public:

		virtual void writeToFile(std::ostream & stream) const override
		{
			stream << "end" << std::endl;
		}

		virtual bool loadFromFile(std::istream & stream) override
		{
			std::string str;
			stream >> str;
			return str == "end";
		}
	};

	static IOFileManager*						getInstance();
	~IOFileManager();

	void										init();

	static std::string							getFolder();

	void										writeToFile( const eOutputFileType type, const IIOItem & container );
	bool										loadFromFile( const eOutputFileType type, IIOItem & container );

	void										writeSolutionData();

	void										cleanFiles();
	bool										isFileExists( const eOutputFileType type );

	static const End							end;

private:

	std::map<eOutputFileType, std::string>		m_fileNames;

	IOFileManager();
	IOFileManager( const IOFileManager& ) = delete;
	IOFileManager&								operator=( IOFileManager& ) = delete;


	static const std::string					s_resultsFolder;

	const std::string&							getFolder( const eOutputFileType type );

	std::string									m_containingFolder;
	std::map<eOutputFileType, std::ofstream*>	m_oFiles;
	std::map<eOutputFileType, std::ifstream*>	m_iFiles;

};

NS_CORE_END
