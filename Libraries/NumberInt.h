//#pragma once
//#include "GlobalDefines.h"
//#include "NumberBase.h"
//
//typedef int integral;
//
//NS_CORE_START
//
//
//
//class NumberInt : public NumberBase<integral>
//{
//protected:
//	NumberInt( const integral& value ) : NumberBase<integral>( value )
//	{
//	}
//
//	NumberInt( const NumberInt& value ) : NumberBase<integral>( value.getValue() )
//	{
//	}
//
//	NumberInt() : NumberBase<integral>()
//	{
//	}
//
//public:
//	void operator++()
//	{
//		getRef()++;
//	}
//};
//
//
//#define USER_DEFINED_INT( typenNme )\
//class typenNme : public NumberInt {\
//public:\
//	typenNme( const integral& value ) : NumberInt( value ) {}\
//	typenNme() : NumberInt() {}\
//	typenNme( const NumberBase<integral>& value ) : NumberInt( value ) {}\
//};\
//
//NS_CORE_END