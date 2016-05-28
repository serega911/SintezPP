#pragma once

#include "WSet.h"
#include "UndefinedVariables_fwd.h"

#include "../Libraries/TChain.h"

#include <vector>
namespace pss
{

	class Variables
	{
		friend class UndefinedVariables;
	private:

		double									m_wInput = 1.0;
		double									m_wOut;
		double									m_wBrake = 0.0;
		double									m_wDefaultValue = 1.0;

		std::vector<WSet>						m_variables;
		std::vector<variable>					m_values;

		void									resize( size_t size );

		void									addInputChain( const TChain& chain );
		void									addBrakeChain( const TChain& chain );
		void									addOutputChain( const TChain& chain, double i );
		void									addUndefinedChain( const TChain& chain);
		

	public:
		Variables( size_t size );

		void									init( const std::vector<TChain>& chains, const TElement& brake, double i );

		WSet &									operator[]( size_t i );
	};
}
