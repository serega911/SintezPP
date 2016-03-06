#pragma once

namespace pss
{
	class TIOFileManager
	{
	public:
		static TIOFileManager*					getInstance();
		~TIOFileManager();
		void									init();
		void									set(){}
	private:
		TIOFileManager();
		TIOFileManager(const TIOFileManager&) = delete;
		TIOFileManager&							operator=(TIOFileManager&) = delete;
	};

	



}