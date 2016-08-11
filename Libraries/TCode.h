#pragma once
#include <vector>

#include "IContainer.h"
#include "TLink.h"
#include "GlobalDefines.h"
#include "GlobalTypes.h"

NS_CORE_START

typedef std::vector<TLink> TLinks;

class TCode: public IContainer
{
private:

	TLinks										m_code;													//	������ ����
	TCount										m_links;												//	���������� ������
	TCount										m_frictions;											//	���������� ����������
	TCount										m_brakes;												//	���������� ��������

public:

	TCode();
	~TCode();

	void										setIn(const TElement & in);								//	��������� �����, ���������� �� ������
	void										setOut(const TElement & out);							//	��������� �����, ���������� �� �������
	void										setLinks( const TLinks& links );						//	��������� ������
	void										setFrictions( const TLinks& frictions );				//	��������� ����������
	void										setBrakes( const TLinks& brakes );						//	��������� ��������

	const TLinks&								getCode() const;

	void										print() const;											//	����� ������� �� �����
		
	// IContainer
	void										writeToFile( std::ostream& ) const override;
	bool										loadFromFile( std::istream& ) override;
	size_t										size() const override;

};

NS_CORE_END