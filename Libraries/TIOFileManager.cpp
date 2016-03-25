#include "../Libraries/TIOFileManager.h"
#include "../Libraries/TSingletons.h"
#include <direct.h>

const std::string								pss::TIOFileManager::s_globalFolder = "..\\Results";

std::string pss::TIOFileManager::getFolder()
{
	return s_globalFolder;
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
		std::string fullName = m_containingFolder + "\\" + m_fileNames.at(type);
		out->open(fullName.c_str(), std::ofstream::out);
		m_oFiles.insert({type, out});
		code.writeCodeToFile(*out);
	}
}

void pss::TIOFileManager::writeInitialData()
{
	std::ofstream* file = new std::ofstream;
	m_oFiles.insert({ eOutputFileType::INITIAL_DATA, file });
	std::string fullName = m_containingFolder + "\\" + m_fileNames.at(eOutputFileType::INITIAL_DATA);
	file->open(fullName.c_str(), std::ofstream::out);
	*file << pss::TSingletons::getInstance()->getW() << ' ' << pss::TSingletons::getInstance()->getNumberOfPlanetaryGears() << ' ' << pss::TSingletons::getInstance()->getNumberOfLinks() << ' ' << pss::TSingletons::getInstance()->getNumberOfFrictions() << ' ' << pss::TSingletons::getInstance()->getNumberOfBrakes() << '\n';
	file->flush();
}

pss::TIOFileManager::TIOFileManager()
{
	init();
}

pss::TIOFileManager* pss::TIOFileManager::getInstance()
{
	static pss::TIOFileManager ioFileManager;
	return &ioFileManager;
}

pss::TIOFileManager::~TIOFileManager()
{
	for (auto& it : m_oFiles)
		it.second->close();
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

	auto folder = "w" + std::to_string(TSingletons::getInstance()->getW()) + "n" + std::to_string(TSingletons::getInstance()->getNumberOfPlanetaryGears());

	m_containingFolder = s_globalFolder + "//" + folder;

	_mkdir(s_globalFolder.c_str());
	_mkdir(m_containingFolder.c_str());
}
