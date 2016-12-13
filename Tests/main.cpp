#include "../Libraries/Parser.h"
#include "../Libraries/Singletons.h"
#include "../Libraries/Log.h"
#include "../Libraries/NumberInt.h"
#include "../Libraries/NumberFloat.h"

#pragma comment(lib, "../Libraries/SintezPPLibary.lib")

NS_CORE_USING
/*
template<class T>
class NumberBase
{
private:
	T											m_value;
protected:
	const T& getRef(){ return m_value; }
public:
	virtual explicit NumberBase( const T& value ) : m_value( value ){}
	virtual NumberBase(){}
	const T& getValue() const {	return m_value;	}
	virtual inline NumberBase operator+( const NumberBase& right ) { return NumberBase(m_value + right.m_value); }
	virtual inline NumberBase operator=( const NumberBase& right ) { m_value = right.m_value; return *this;	}
};

template<class T>
class NumberInt : public NumberBase<T>
{
public:	inline void operator++() final { getRef()++; }
};

template<class T>
class NumberFloat : public NumberBase<T>
{
public:	virtual inline bool operator==( const NumberBase& right ) final { return abs( getValue() - right.getValue() ) < 0.0001; }
};



class Count : public NumberInt<int>{};
class Size : public NumberInt<int>{};


int main()
{
	Count c1(5);
	Count c2 = 5;
	Count c3 = c1 + c2;
	c3++;

	system("pause");

	return 0;
}*/



//USER_DEFINED_INT(Count)
// USER_DEFINED_INT(Size)
// 
// class Count : public NumberInt {
// public:
// 	using NumberBase::operator=;
// 	Count( const integral& value ) : NumberInt( value ) {}
// 	Count() : NumberInt() {}
// 	Count( const Count& value ) : NumberInt( value.getValue() ) {}
// }; 
// 
// class Size : public NumberInt {
// public:
// 	using NumberBase::operator=;
// 	Size( const integral& value ) : NumberInt( value ) {}
// 	Size() : NumberInt() {}
// 	Size( const Size& value ) : NumberInt( value.getValue() ) {}
// };
// 
// int main()
// {
// 	Count c1( 5 );
// 	Count c2 = 5;
// 	Count c3 = c1 + c2;
// 	c3 = c1 + c2;
// 	//++c3;
// 	Size s1 = 5;
// 	s1 = c3;
// 	system( "pause" );
// 	return 0;
// }


typedef int Count;
typedef int Size;

int main()
{
	Count c = 5;
	Size s = c;   //эта строка компилируется
}