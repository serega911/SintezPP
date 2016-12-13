//#pragma once
//#include "GlobalDefines.h"
//
//NS_CORE_START
//
//template<class T>
//class NumberBase {
//private:
//
//	T m_value;
//
//protected:
//
//	T& getRef() {
//		return m_value;
//	}
//
//public:
//
//	explicit NumberBase( const T& value ) : m_value( value )
//	{
//	}
//
//	NumberBase()
//	{
//	}
//
//	const T& getValue() const
//	{
//		return m_value;
//	}
//
//	NumberBase operator=( const NumberBase& right )
//	{
//		m_value = right.m_value;
//		return *this;
//	}
//
//	NumberBase operator+( const NumberBase& right )
//	{
//		return NumberBase( m_value + right.m_value );
//	}
//
//	NumberBase operator-( const NumberBase& right )
//	{
//		return NumberBase( m_value - right.m_value );
//	}
//
//	NumberBase operator*( const NumberBase& right )
//	{
//		return NumberBase( m_value * right.m_value );
//	}
//
//	NumberBase operator/( const NumberBase& right )
//	{
//		return NumberBase( m_value / right.m_value );
//	}
//
//	bool operator>( const NumberBase& right )
//	{
//		return m_value > right.m_value;
//	}
//
//	bool operator<( const NumberBase& right )
//	{
//		return m_value < right.m_value;
//	}
//
//	bool operator<=( const NumberBase& right )
//	{
//		return m_value <= right.m_value;
//	}
//
//	bool operator>=( const NumberBase& right )
//	{
//		return m_value >= right.m_value;
//	}
//
//	bool operator!=( const NumberBase& right )
//	{
//		return !(*this == right);
//	}
//
//	virtual bool operator==( const NumberBase& right )
//	{
//		return m_value == right.m_value;
//	}
//};
//
//NS_CORE_END