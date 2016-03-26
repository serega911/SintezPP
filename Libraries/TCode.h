#pragma once
#include <vector>
#include <fstream>

#include "../Libraries/IContainer.h"

namespace pss{
	class TCode: public pss::IContainer
	{
	public:
		TCode();
		~TCode(void);
		int										operator[](int i) const;				//	�������� ��������� �������� ������� ����
		bool									setIn(int);								//	��������� �����, ���������� �� ������
		bool									setOut(int);							//	��������� �����, ���������� �� �������
		bool									setLinks(std::vector<int>);				//	��������� ������
		bool									setFrictions(std::vector<int>);			//	��������� ����������
		bool									setBrakes(std::vector<int>);			//	��������� ��������

		const std::vector<int>&					getCode() const;
		void									writeToFile(std::ofstream&) const override;
		void									loadFromFile(std::ifstream&) override;
		bool									check() const;
		void									print() const;							//	����� ������� �� �����
		void									clear();
		int										size() const override;
	private:
		std::vector<int>						m_code;									//	������ ����
		int										m_codeSize;								//	������ ������� ����

		int										m_links;
		int										m_frictions;
		int										m_brekes;
	};

}