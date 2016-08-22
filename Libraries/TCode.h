#pragma once
#include <vector>

#include "IContainer.h"
#include "TLink.h"
#include "GlobalDefines.h"

NS_CORE_START



class TCode: public IContainer
{
private:

	TLinkArray									m_code;													//	������ ����
	size_t										m_links;												//	���������� ������
	size_t										m_frictions;											//	���������� ����������
	size_t										m_brakes;												//	���������� ��������

public:

	TCode();
	~TCode();

	void										setIn(const TElement & in);								//	��������� �����, ���������� �� ������
	void										setOut(const TElement & out);							//	��������� �����, ���������� �� �������
	void										setLinks( const TLinkArray& links );					//	��������� ������
	void										setFrictions( const TLinkArray& frictions );			//	��������� ����������
	void										setBrakes( const TLinkArray& brakes );					//	��������� ��������

	const TLinkArray&							getCode() const;

	void										print() const;											//	����� ������� �� �����
		
	// IContainer
	void										writeToFile( std::ostream& ) const override;
	bool										loadFromFile( std::istream& ) override;
	size_t										size() const override;

};

NS_CORE_END