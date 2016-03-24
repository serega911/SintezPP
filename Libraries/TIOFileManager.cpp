#include "../Libraries/TIOFileManager.h"
#include <direct.h>

const std::string								pss::TIOFileManager::s_folder = "..//Results";

std::string pss::TIOFileManager::getFolder()
{
	return s_folder;
}

void pss::TIOFileManager::writeToFile(eOutputFileType type, const TCode & code)
{
	auto file = m_oFiles.find(type);
	if (file != m_oFiles.end())
	{
		code.writeCodeToFile(*(file->second));
	}
	else
	{
		std::ofstream* out = new std::ofstream;
		std::string fullName = s_folder + "//" + m_fileNames.at(type);
		out->open(fullName.c_str(), std::ofstream::out);
		m_oFiles.insert({type, out});
		code.writeCodeToFile(*out);
	}
}

pss::TIOFileManager::TIOFileManager()
{
}

pss::TIOFileManager* pss::TIOFileManager::getInstance()
{
	static pss::TIOFileManager ioFileManager;
	return &ioFileManager;
}

pss::TIOFileManager::~TIOFileManager()
{
	for (auto& it : m_oFiles)
		delete (it.second);
	m_oFiles.clear();
}

void pss::TIOFileManager::init()
{
	m_fileNames[eOutputFileType::FAIL_0] = "failed_0.log";
	m_fileNames[eOutputFileType::FAIL_FREE] = "failed_free.log";
	m_fileNames[eOutputFileType::FAIL_N] = "failed_N.log";
	m_fileNames[eOutputFileType::FAIL_REPETTION] = "failed_repetition.log";
	m_fileNames[eOutputFileType::INITIAL_DATA] = "initial_data.init";
	m_fileNames[eOutputFileType::DONE] = "done.pkp";
	_mkdir(s_folder.c_str());
}
