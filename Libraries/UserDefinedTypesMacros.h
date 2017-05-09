#pragma once
#include "GlobalDefines.h"

template <class buildInType>
class IUserDefinedType
{
public:
	virtual buildInType getAbs() const = 0;
	virtual const buildInType& getValue() const = 0;
};




template <class buildInType>
class Integral : public IUserDefinedType<buildInType>
{
private:
	buildInType m_value;
public:
	explicit					Integral( const buildInType value ) : m_value( value )		{}
	Integral() : m_value( 0 )																{}
	virtual const buildInType&	getValue() const override									{ return m_value; }
	inline friend Integral		operator-( const Integral& obj1, const Integral& obj2 )		{ return Integral( obj1.m_value - obj2.m_value ); }
	inline friend Integral		operator+( const Integral& obj1, const Integral& obj2 )		{ return Integral( obj1.m_value + obj2.m_value ); }
	inline friend bool			operator<( const Integral& obj1, const Integral& obj2 )		{ return obj1.m_value < obj2.m_value; }
	inline friend bool			operator>( const Integral& obj1, const Integral& obj2 )		{ return obj1.m_value > obj2.m_value; }
	inline friend bool			operator==( const Integral& obj1, const Integral& obj2 )	{ return obj1.m_value == obj2.m_value; }
	inline friend bool			operator<=( const Integral& obj1, const Integral& obj2 )	{ return !( obj1 > obj2 ); }
	inline friend bool			operator>=( const Integral& obj1, const Integral& obj2 )	{ return !( obj1 < obj2 ); }
	inline friend bool			operator!=( const Integral& obj1, const Integral& obj2 )	{ return !( obj1 == obj2 ); }
	virtual buildInType			getAbs() const override										{ return abs( m_value ); }
	inline const Integral&		operator=( const buildInType& value )						{ m_value = value; return *this; }
	inline const Integral&		operator=( const Integral& obj2 )							{ m_value = obj2.m_value; return *this; }
	inline const Integral&		operator++( )												{ m_value++; return *this; }
	inline const Integral&		operator--( )												{ m_value--; return *this; }
};




template <class buildInType>
class Floating : public Integral<buildInType>																															\
{
private:
	buildInType m_value;
public:
	explicit					Floating( const buildInType value ) : m_value( value )		{}
	Floating() : m_value( 0 )										{}
	inline const buildInType&	getValue() const 											{ return m_value; }
	inline friend Floating		operator-( const Floating& obj1, const Floating& obj2 )		{ return Floating( obj1.m_value - obj2.m_value ); }
	inline friend Floating		operator+( const Floating& obj1, const Floating& obj2 )		{ return Floating( obj1.m_value + obj2.m_value ); }
	inline friend bool			operator<( const Floating& obj1, const Floating& obj2 )		{ return obj1.m_value < obj2.m_value; }
	inline friend bool			operator>( const Floating& obj1, const Floating& obj2 )		{ return obj1.m_value > obj2.m_value; }
	inline friend bool			operator==( const Floating& obj1, const Floating& obj2 )	{ return abs( obj1.m_value - obj2.m_value ) < 0.00001; }
	inline friend bool			operator<=( const Floating& obj1, const Floating& obj2 )	{ return !( obj1 > obj2 ); }
	inline friend bool			operator>=( const Floating& obj1, const Floating& obj2 )	{ return !( obj1 < obj2 ); }
	inline friend bool			operator!=( const Floating& obj1, const Floating& obj2 )	{ return !( obj1 == obj2 ); }
	inline buildInType			getAbs() const 												{ return abs( m_value ); }
	inline const Floating&		operator=( const buildInType& value )						{ m_value = value; return *this; }
	inline const Floating&		operator=( const Floating& obj2 )							{ m_value = obj2.m_value; return *this; }
};





#define USER_DEFINED_TYPE_INTEGRAL( typeName, buildInType) typedef Integral<buildInType> typeName;
#define USER_DEFINED_TYPE_FLOATING( typeName, buildInType) typedef Floating<buildInType> typeName;

#define USER_DEFINED_TYPE_VECTOR( typeName, containerType, buildInType )																		\
class typeName : public containerType<buildInType>{};