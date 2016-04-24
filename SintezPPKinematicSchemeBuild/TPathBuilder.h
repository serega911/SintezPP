#pragma once
#include "TKinematicScheme.h"
#include "TCordinates.h"

namespace pss
{
	class TPathBuilder
	{
	public:
		typedef std::vector<std::vector<int>> Field;
		enum class Direction
		{
			UP,
			DOWN,
			LEFT,
			RIGHT
		};
	private:
		Direction								m_direction;
		Field									m_field;

		int										m_start;
		int										m_finish;
		int										m_empty;
		int										m_wall;


		void									initField( const pss::TKinematicScheme & scheme, pss::TLink link );
		void									spreadWave();
		void									printField();
	public:
		TPathBuilder();
		bool									findPath( const pss::TKinematicScheme & scheme, pss::TLink link );
	};
}


