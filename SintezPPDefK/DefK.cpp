#include "DefK.h"
#include "../Libraries/func_lib.h"
#include "../Libraries/TSingletons.h"
#include <iostream>

pss::DefK::DefK(const pss::TI& I)
{
	m_iTarget = I;
}


pss::DefK::~DefK(void)
{
}

pss::TK pss::DefK::run(const pss::TCode& Code, pss::TK K)
{
	do{
		//K.print();
		if (podModul(Code, K))
		{
			K.setFinded();
			return K;
		}
		//system("pause");
	}while(K.next());
	return K;
}

bool pss::DefK::podModul(const pss::TCode & Code, const pss::TK &k)
{
	auto N = pss::TSingletons::getInstance()->getNumberOfPlanetaryGears();
	auto L = pss::TSingletons::getInstance()->getNumberOfLinks();
	auto F = pss::TSingletons::getInstance()->getNumberOfFrictions();
	auto B = pss::TSingletons::getInstance()->getNumberOfBrakes();
	auto W = pss::TSingletons::getInstance()->getW();

	m_matrix.resize(3 * N);
	for (auto& it : m_matrix)
		it.resize(3 * N + 1);
	//� ������ N ����� ���������� ��������� �������. 
	//��� ������ ������� �� ������� ��� ��� ��� �������� ������ ������� �� ���� � �� �� �������
	for (int i = 0; i < k.size(); i++){
		m_matrix[i][3 * i] = 1;
		m_matrix[i][3 * i + 1] = -k[i];
		m_matrix[i][3 * i + 2] = k[i] - 1;
	}

		//system("pause");
		//������� ���������
	for (int i = N; i < N + L + 1; i++)
	for (int j = 0; j < 3 * N + 1; j++)
				m_matrix[i][j] = 0;
		//� ��������� countSV ����� ���������� �����
	for (int i = N, j = 2; i < N + L; i++, j++){
			m_matrix[i][pss::code_2_pos(Code[j] / 100)] = 1;
			m_matrix[i][pss::code_2_pos(Code[j] % 100)] = -1;
		}
		//��������� ��� �����, ���������� � ������� �����
	m_matrix[N + L][pss::code_2_pos(Code[0] / 100)] = 1;
	m_matrix[N + L][N * 3] = 1;
			
	//print(Matrix, "11	21	31	12	22	32	13	23	33	RP \n___________________________________________________________________________");
	
	pss::TI tmpI({}, 0.01);	//������ ��� ���������� ������������ ��������� ��� ������ ������ K
	double TMP=0;

	std::vector<int> vect_combi_drive(W - 1);//TReplace
	for (int i = 0; i < W - 1; i++)
	vect_combi_drive[i] = i;
	//���������� ��� ��������� ��������� ��������� ���������� (���������� � ��������) ��� ����������
	do {
		//���������� � ������� ��������� � ���������� ����������
		for (int i = 0; i < vect_combi_drive.size(); i++)
		{
			int driver = Code[2 + L + vect_combi_drive[i]];
			//std::cout << "driver: " << driver << std::endl;
			if (driver%100 == 66)	//driver - ������
				m_matrix[N + L + 1 + i][pss::code_2_pos(driver / 100)] = 1;
			else	//driver - ��������
			{
				m_matrix[N + L + 1 + i][pss::code_2_pos(driver / 100)] = 1;
				m_matrix[N + L + 1 + i][pss::code_2_pos(driver % 100)] = -1;
			}
		}
		//print(Matrix, "11	21	31	12	22	32	13	23	33	RP\n___________________________________________________________________________");
		//������ ������� ���������
		TMP = pss::GAUS(m_matrix, pss::code_2_pos(Code[1] / 100));
		//��������� ���������
		if (abs(TMP) > 0.001)
			tmpI.push_back(1.0 / TMP);
		else
			return false;
		//������� ��������� � ���������� ����������
		for (int i = N + L + 1; i < N + L + W; i++)
			for (int j = 0; j < 3 * N + 1; j++)
				m_matrix[i][j] = 0;
	} while (pss::next_combination(vect_combi_drive, F + B - 1));
			//���������� ���������� ������������ ��������� � ��������
	if (m_iTarget == tmpI)
	{
		m_iReal = tmpI;
		return true;
	}
	else
		return false;
}

