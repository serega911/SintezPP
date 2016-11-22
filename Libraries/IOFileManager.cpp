#include <direct.h>
#include <windows.h>

#include "IOFileManager.h"
#include "Singletons.h"

NS_CORE_USING

const std::string								IOFileManager::s_resultsFolder = "..\\Results";

std::string IOFileManager::getFolder()
{
	return s_resultsFolder;
}

const std::string& IOFileManager::getFolder( eOutputFileType type )
{
	return m_containingFolder;// type == eOutputFileType::SETTINGS ? s_settingsFolder : m_containingFolder;
}

void IOFileManager::writeToFile( eOutputFileType type, const IIOItem & container )
{
	auto file = m_oFiles.find(type);
	if (file != m_oFiles.end())
	{
		*(file->second) << std::endl;
		container.writeToFile(*(file->second));
	}
	else
	{
		std::ofstream* out = new std::ofstream;
		std::string fullName = getFolder(type) + "\\" + m_fileNames.at( type );
		out->open(fullName.c_str(), std::ofstream::out);
		m_oFiles.insert({type, out});
		container.writeToFile(*out);
	}
}


bool IOFileManager::loadFromFile(eOutputFileType type, IIOItem & container)
{
	bool result;

	auto file = m_iFiles.find(type);
	if (file != m_iFiles.end())
	{
		result = container.loadFromFile( *( file->second ) );
	}
	else
	{
		std::string fullName = getFolder( type ) + "\\" + m_fileNames.at( type );
		std::ifstream* in = new std::ifstream( fullName.c_str() );

		if ( in->good() )
		{
			m_iFiles.insert( { type, in } );
			result = container.loadFromFile( *in );
		}
		else
		{
			result = false;
		}
	}
	return result;
}

void IOFileManager::writeSolutionData()
{
	std::ofstream* file = new std::ofstream;
	m_oFiles.insert({ eOutputFileType::INITIAL_DATA, file });
	std::string fullName = m_containingFolder + "\\" + m_fileNames.at(eOutputFileType::INITIAL_DATA);
	file->open(fullName.c_str(), std::ofstream::out);

	SYSTEMTIME st;
	GetLocalTime(&st);
	*file << "Started:	" << st.wHour << ':' << st.wMinute << ':' << st.wSecond << std::endl;

	const auto& generalData = Singletons::getInstance()->getGeneralData();
	const auto& initialData = Singletons::getInstance()->getInitialData();

	*file << initialData._w << ' ' 
		<< initialData._numberOfPlanetaryGears << ' '
		<< generalData._numberOfLinks << ' '
		<< generalData._numberOfFrictions << ' '
		<< generalData._numberOfBrakes << '\n';
	file->flush();
}

IOFileManager::IOFileManager()
{
	init();
}

IOFileManager* IOFileManager::getInstance()
{
	static IOFileManager ioFileManager;
	return &ioFileManager;
}

IOFileManager::~IOFileManager()
{
	auto file = m_oFiles.find(eOutputFileType::INITIAL_DATA);
	if (file != m_oFiles.end() && file->second->is_open())
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		*(file->second) << "Finished:	" << st.wHour << ':' << st.wMinute << ':' << st.wSecond << std::endl;
	}

	for (auto& it : m_oFiles)
		it.second->close();
	for (auto& it : m_oFiles)
		delete (it.second);
	m_oFiles.clear();
}

void IOFileManager::init()
{
	m_fileNames[eOutputFileType::FAIL_0] = "failed_0.log";
	m_fileNames[eOutputFileType::FAIL_FREE] = "failed_free.log";
	m_fileNames[eOutputFileType::FAIL_N] = "failed_N.log";
	m_fileNames[eOutputFileType::FAIL_REPETTION] = "failed_repetition.log";
	m_fileNames[eOutputFileType::INITIAL_DATA] = "solution_data.init";
	m_fileNames[eOutputFileType::DONE] = "done.pkp";
	m_fileNames[eOutputFileType::DONE_K] = "done_K.pkp";
	m_fileNames[eOutputFileType::DONE_K_SIMPLE] = "done_K_simple.pkp";
	m_fileNames[eOutputFileType::DONE_K_NUTON] = "done_K_nuton.pkp";
	m_fileNames[eOutputFileType::DONE_K_SELECTION] = "done_K_selection.pkp";
	m_fileNames[eOutputFileType::FAIL_NUTON] = "failed_Nuton.pkp";
	m_fileNames[eOutputFileType::KIN_QUICK] = "kin_quick.pkp";
	m_fileNames[eOutputFileType::KIN_SLOW] = "kin_slow.pkp";
	m_fileNames[eOutputFileType::K_TEST] = "done_test.pkp";
	m_fileNames[eOutputFileType::K_TEST_LOG] = "done_test_log.pkp";
	m_fileNames[eOutputFileType::SETTINGS] = "settings.txt";

	const auto& initialData = Singletons::getInstance()->getInitialData();
	const auto& generalData = Singletons::getInstance()->getGeneralData();
	auto folder = "w" + std::to_string( initialData._w ) + "n" + std::to_string( initialData._numberOfPlanetaryGears ) + "d" + std::to_string( generalData._numberOfFrictions + generalData._numberOfBrakes );

	m_containingFolder = s_resultsFolder + "\\" + folder;

	_mkdir(s_resultsFolder.c_str());
	_mkdir(m_containingFolder.c_str());
}
