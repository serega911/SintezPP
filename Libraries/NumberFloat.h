//#pragma once
//#include "GlobalDefines.h"
//#include "NumberBase.h"
//
//#include <cstdlib>
//
//NS_CORE_START
//
//typedef int floating;
//
//class NumberFloat : public NumberBase<floating>
//{
//protected:
//	NumberFloat( floating value ) : NumberBase( value )
//	{
//	}
//
//	NumberFloat( const NumberBase<floating>& value ) : NumberBase<floating>( value )
//	{
//	}
//
//public:
//	virtual bool operator==( const NumberBase<floating>& right ) override
//	{
//		return abs(getValue() - right.getValue()) < 0.00001;
//	}
//};
//
//NS_CORE_END