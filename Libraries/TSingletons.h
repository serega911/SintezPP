#pragma once

namespace pss
{
	class TSingletons
	{
	public:
		TSingletons*							getInstance();
		~TSingletons();
		void									init();

	private:
		TSingletons();
	};
}

