#pragma once
#include "TIOFileManager.h"

namespace pss
{
	class TSingletons
	{
	public:
		static TSingletons*							getInstance();
		~TSingletons();
		void									init();
		TIOFileManager*							getIOFileManager();

	private:
		TSingletons();
		TSingletons(const TSingletons&) = delete;
		TSingletons&							operator=(TSingletons&) = delete;
	};
}

