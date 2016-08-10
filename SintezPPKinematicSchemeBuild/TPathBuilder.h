#pragma once
#include "TKinematicScheme.h"
#include "TCordinates.h"
#include "eDirection.h"

namespace pss
{
	class TPathBuilder
	{
	public:
		typedef std::vector<std::vector<int>> Field;

	private:
		Field									m_field;

		int										m_start;
		int										m_finish;
		int										m_empty;
		int										m_wall;


		void									initField( const pss::TKinematicScheme & scheme, pss::TLink link );
		bool									spreadWave();
		std::vector<pss::TCordinates>			findPath();
		pss::TCordinates						findStartCell();
		void									printField();
	public:
		TPathBuilder();
		std::vector<pss::TCordinates>			findPath( const pss::TKinematicScheme & scheme, pss::TLink link );
	};
}


