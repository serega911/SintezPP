#pragma once

#include <vector>
#include "../Libraries/TChain.h"

namespace pss
{
	class TPlanetaryGearSet
	{
	public:

		typedef std::vector<std::vector<pss::TChain>> Field;

		enum class Type
		{
			TYPE_N,
			TYPE_N_REVERSE,
			TYPE_U,
			TYPE_U_REVERSE,
			TYPE_DEFAULT
		};

		static const int						s_xSize;
		static const int						s_ySize;
		static const int						s_centerX;
		static const int						s_centerY;

	private:

		Field									m_field;
		int										m_gearSetN;

		void									resetField();
		void									createTypeN( int gearSetN );
		void									createTypeDefault( int gearSetN );
		void									reverseX();
		void									reverseY();
	public:

		void									print();
		void									printLine( int xPos );

		void									create( int gearSetN, Type type );

		std::vector<pss::TChain>&				operator[]( int xPos );
		const std::vector<pss::TChain>&			operator[]( int xPos ) const;
	};
}



