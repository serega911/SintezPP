#pragma once

namespace pss
{
	class TIOFileManager
	{
	public:
		TIOFileManager*							getInstance();
		~TIOFileManager();

	private:
		TIOFileManager();
	};

	



}