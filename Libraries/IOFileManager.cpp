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

const std::string& IOFileManager::getFolder( const eOutputFileType type )
{
	return m_containingFolder;
}

void IOFileManager::writeToFile( const eOutputFileType type, const IIOItem & container )
{
	auto file = m_oFiles.find( type );
	if ( file != m_oFiles.end() )
	{
		*( file->second ) << std::endl;
		container.writeToFile( *( file->second ) );
	}
	else
	{
		std::ofstream* out = new std::ofstream;
		std::string fullName = getFolder( type ) + "\\" + m_fileNames.at( type );
		out->open( fullName.c_str(), std::ofstream::out );
		m_oFiles.insert( { type, out } );
		container.writeToFile( *out );
	}
}


bool IOFileManager::loadFromFile( const eOutputFileType type, IIOItem & container )
{
	bool result;

	auto file = m_iFiles.find( type );
	if ( file != m_iFiles.end() )
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
	const auto& initialData = Singletons::getInstance()->getInitialData();

	writeToFile( IOFileManager::eOutputFileType::INITIAL_DATA, initialData._i );

	for ( const auto& range : initialData._ranges )
		writeToFile( IOFileManager::eOutputFileType::INITIAL_DATA, range );
}

bool core::IOFileManager::isFileExists( const eOutputFileType type )
{
	bool result;

	if ( m_iFiles.find( type ) != m_iFiles.end() )
		result = true;
	else
	{
		std::string fullName = getFolder( type ) + "\\" + m_fileNames.at( type );
		std::ifstream* in = new std::ifstream( fullName.c_str() );

		if ( in->good() )
		{
			m_iFiles.insert( { type, in } );
			result = true;
		}
		else
		{
			result = false;
		}
	}

	return result;
}

void core::IOFileManager::cleanFiles()
{
	_rmdir( m_containingFolder.c_str() );
	_mkdir( m_containingFolder.c_str() );


	m_oFiles.clear();
	m_iFiles.clear();
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
	for ( auto& it : m_oFiles )
		it.second->close();
	for ( auto& it : m_oFiles )
		delete ( it.second );
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
	m_fileNames[eOutputFileType::DEF_K_LOG] = "done_test_log.pkp";
	m_fileNames[eOutputFileType::SETTINGS] = "settings.txt";

	const auto& initialData = Singletons::getInstance()->getInitialData();
	const auto& generalData = Singletons::getInstance()->getGeneralData();
	auto folder = "w" + std::to_string( initialData._w ) + "n" + std::to_string( initialData._numberOfPlanetaryGears ) + "d" + std::to_string( generalData._numberOfFrictions + generalData._numberOfBrakes );

	m_containingFolder = s_resultsFolder + "\\" + folder;

	_mkdir( s_resultsFolder.c_str() );
	_mkdir( m_containingFolder.c_str() );
}
