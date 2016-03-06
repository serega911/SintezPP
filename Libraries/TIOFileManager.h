#pragma once

#include <string>
#include <fstream>

namespace pss
{
	class TIOFileManager
	{
	public:
		static TIOFileManager*					getInstance();
		~TIOFileManager();
		void									init();
		std::string								getFolder();

	private:
												TIOFileManager();
												TIOFileManager(const TIOFileManager&) = delete;
		TIOFileManager&							operator=(TIOFileManager&) = delete;

		static const std::string				s_folder;
		
	};

	



}