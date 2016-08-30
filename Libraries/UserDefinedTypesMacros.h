#pragma once
#include "GlobalDefines.h"

#define USER_DEFINED_TYPE( typeName, buildInType)																								\
class typeName																																	\
{																																				\
private:																																		\
	buildInType m_value;																														\
public:																																			\
	explicit					typeName(const buildInType value): m_value(value)			{}													\
								typeName()													{}													\
	inline const buildInType&	getValue() const											{ return m_value; }									\
	inline friend typeName		operator-( const typeName& obj1, const typeName& obj2 )		{ return typeName(obj1.m_value - obj2.m_value); }	\
	inline friend typeName		operator+( const typeName& obj1, const typeName& obj2 )		{ return typeName(obj1.m_value + obj2.m_value); }	\
	inline friend bool			operator<( const typeName& obj1, const typeName& obj2 )		{ return obj1.m_value < obj2.m_value; }				\
	inline friend bool			operator>( const typeName& obj1, const typeName& obj2 )		{ return obj1.m_value > obj2.m_value; }				\
	inline friend bool			operator==( const typeName& obj1, const typeName& obj2 )	{ return obj1.m_value == obj2.m_value; }			\
	inline friend bool			operator<=( const typeName& obj1, const typeName& obj2 )	{ return obj1.m_value <= obj2.m_value; }			\
	inline friend bool			operator>=( const typeName& obj1, const typeName& obj2 )	{ return obj1.m_value >= obj2.m_value; }			\
	inline friend bool			operator!=( const typeName& obj1, const typeName& obj2 )	{ return obj1.m_value != obj2.m_value; }			\
	inline typeName				getAbs() const												{ return typeName( abs( m_value ) ); }				\
};																																		

#define USER_DEFINED_TYPE_VECTOR( typeName, containerType, buildInType ) class typeName : public containerType<buildInType> {};																					