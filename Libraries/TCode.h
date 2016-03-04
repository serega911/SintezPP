#pragma once
#include <vector>
#include <fstream>

namespace pss{
	class TCode
	{
	public:
		TCode(int, int);
		TCode() = delete;
		~TCode(void);
		int										operator[](int i) const;				//	�������� ��������� �������� ������� ����
		bool									setIn(int);								//	��������� �����, ���������� �� ������
		bool									setOut(int);							//	��������� �����, ���������� �� �������
		bool									setLinks(std::vector<int>);				//	��������� ������
		bool									setFrict(std::vector<int>);				//	��������� ����������
		bool									setBrakes(std::vector<int>);			//	��������� ��������
		void									print() const;							//	����� ������� �� �����
		void									clear();
		int										size() const;
		int										getN() const;
		int										getW() const;
		int										getCountL() const;
		int										getCountF() const;
		int										getCountB() const;
		void									writeCodeToFile(std::ofstream&) const;
		void									writeParametersToFile(std::ofstream&) const;
		void									loadCodeFromFile(std::ifstream&);
		void									loadParametersFromFile(std::ifstream&);
		bool									check() const;
		const std::vector<int>&					getCode() const;
	private:
		std::vector<int>						m_code;									//	������ ����
		int										m_w;									//	����� �������� �������
		int										m_numberOfPlanetaryGears;				//	���������� ����������� �����
		int										m_numberOfBrakes;						//	���������� ��������
		int										m_numberOfFrictions;					//	���������� ����������
		int										m_numberOfLinks;						//	���������� ������
		int										m_codeSize;								//	������ ������� ����
	};

}