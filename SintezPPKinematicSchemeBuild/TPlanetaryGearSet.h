#pragma once

#include <vector>
#include "../Libraries/TChain.h"

namespace pss
{
	class TPlanetaryGearSet
	{
	public:
		enum class Type
		{
			TYPE_N,
			TYPE_N_REVERSE,
			TYPE_U,
			TYPE_U_REVERSE,
			TYPE_DEFAULT
		};
	private:
		typedef std::vector<std::vector<pss::TChain>> Field;

		static const int						s_maxX;
		static const int						s_maxY;
		static const int						s_centerX;
		static const int						s_centerY;

		Type									m_planetaryGearSetType;

		std::vector<Field>						m_fieldWithLimts;	//new
		Field									m_field;

		void									makeLimits( Type type );
		void									invers();

		void									resetField();
		void									resetLimits();

		void									makeLimitsForTypeN();
		void									makeLimitsForTypeNReverse( );
		void									makeLimitsForTypeU();
		void									makeLimitsForTypeUReverse();
		void									makeLimitsForTypeDefault();

		void									createTypeN( int gearSetN );
		void									createTypeNReverse( int gearSetN );
		void									createTypeU( int gearSetN );
		void									createTypeUReverse( int gearSetN );
		void									createTypeDefault( int gearSetN );
	public:
		TPlanetaryGearSet();
		~TPlanetaryGearSet();

		void									print();
		void									print( const Field & field );

		void									create( int gearSetN, Type type );
	};
}



