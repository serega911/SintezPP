#pragma once
#include <vector>
#include <fstream>

#include "../Libraries/IContainer.h"

namespace pss{
	class TCode: public pss::IContainer
	{
	private:
		std::vector<int>						m_code;									//	������ ����
		int										m_codeSize;								//	������ ������� ����

		std::vector<std::vector<int>>			m_chains;

		int										m_links;
		int										m_frictions;
		int										m_brekes;

		void									createChains();

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
		int										getIn() const;
		int										getOut() const;
		const std::vector<std::vector<int>>&	getChains() const;
		const std::vector<int>					getElementsForFrictions() const;
		const std::vector<int>					getElementsForBrakes() const;
		void									writeToFile(std::ofstream&) const override;
		void									loadFromFile(std::ifstream&) override;
		bool									checkFree() const;
		bool									check() const;
		void									print() const;							//	����� ������� �� �����
		void									clear();
		int										size() const override;
	
	};

}