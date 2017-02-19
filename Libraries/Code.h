#pragma once
#include <vector>

#include "IIOItem.h"
#include "Link.h"
#include "GlobalDefines.h"

NS_CORE_START



class Code: public IIOItem
{
private:

	Link										m_input;
	Link										m_output;
	TLinkArray									m_links;
	TLinkWithFrictionArray						m_frictions;
	TLinkArray									m_brakes;

public:

	Code();
	~Code();

	void										setIn(const Element & in);								//	��������� �����, ���������� �� ������
	void										setOut(const Element & out);							//	��������� �����, ���������� �� �������
	void										setLinks( const TLinkArray& links );					//	��������� ������
	void										setFrictions( const TLinkWithFrictionArray& frictions );//	��������� ����������
	void										setBrakes( const TLinkArray& brakes );					//	��������� ��������

	const Link&									getIn() const;
	const Link&									getOut() const;
	const TLinkArray&							getLinks() const;
	const TLinkWithFrictionArray&				getFrictions() const;
	const TLinkArray&							getBrakes() const;

	bool										isContain( const Element& elem ) const ;

	void										print() const;											//	����� ������� �� �����
		
	// IIOItem
	void										writeToFile( std::ostream& ) const override;
	bool										loadFromFile( std::istream& ) override;

};

NS_CORE_END