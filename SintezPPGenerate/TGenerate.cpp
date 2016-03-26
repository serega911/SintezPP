#include "TGenerate.h"
#include "../Libraries/func_lib.h"
#include "../Libraries/TCode.h"
#include "../Libraries/TSingletons.h"
#include <iostream>

#include <algorithm>

void pss::TGenerate::generate()
{
	setlocale(LC_ALL, "Russian");
	std::cout << "======  ������ ����������� ������� � ����� ��������� �������.  ======\n\n";
	//	�������� ������
	int W;
	int N;
	std::cout << "\t\t\t�������� ������." << std::endl << "����� �������� �������:	";
	std::cin >> W;
	std::cout << "���������� ��:		";
	std::cin >> N;
	pss::TSingletons::getInstance()->setGlobalParameters(W, N);
	std::cout << "���������� ������:	" << pss::TSingletons::getInstance()->getNumberOfLinks() << std::endl;
	std::cout << "���������� ����������:	" << pss::TSingletons::getInstance()->getNumberOfFrictions() << std::endl;
	std::cout << "���������� ��������:	" << pss::TSingletons::getInstance()->getNumberOfBrakes() << std::endl;

	//	��������� ������ ���� ��������� ������, ���������� ����� ����� ���������� ������ ����.
	m_allLinks.clear();
	for (int i = 0; i <= 3 * (N - 1); i++)
	{
		for (int j = (i / 3 + 1) * 3; j < 3 * N; j++)
			m_allLinks.push_back(pss::pos_2_code(i) * 100 + pss::pos_2_code(j));
	}


}

void pss::TGenerate::generateInOut()
{
	pss::TCode C;
	auto N = pss::TSingletons::getInstance()->getNumberOfPlanetaryGears();
	for (int in = 0; in < 3 * N; in++)				//	���� �� ��� ������
	for (int out = 0; out < 3 * N; out++)		//	����� �� ��� ������
	{
		if (in != out)							//	��������: ���� � ����� �� ����� ���� ����� � ��� �� ���������
		{
			C.clear();
			C.setIn(pss::pos_2_code(in));
			C.setOut(pss::pos_2_code(out));
			generateLinks(C);
		}
	}
}

bool pss::TGenerate::generateLinks(pss::TCode & code)
{
	std::vector<int> links;			//	������ ������
	std::vector<int> linksCombi;		//	������ ��������� ������
	//	������� ������ ��������� ������ �� ���� ��������� ������ �� Count_L+Count_F (���������� ������ + ���������� ����������) ��� ����������: 0,1,2,3...
	for (int i = 0; i < pss::TSingletons::getInstance()->getNumberOfLinks(); i++)
		linksCombi.push_back(i);
	//	� ����� ���������� ��� ��������� ��������� ������
	do{
		//	��������� ������ ������ � ������ ���������������� ���������
		links.clear();
		for (int i = 0; i < linksCombi.size(); i++)
			links.push_back(m_allLinks[linksCombi[i]]);
		code.setLinks(links);
		//	���������� ������� ������
		std::vector<std::vector<int>> chains = create_Chains(pss::pos_2_code(code.getIn()), pss::pos_2_code(code.getOut()), links);
		bool flag = false;
		for (size_t i = 0; i < m_existingSchemes.size(); i++)
		if (m_existingSchemes[i] == chains)
		{
			pss::TSingletons::getInstance()->getIOFileManager()->writeToFile(pss::TIOFileManager::eOutputFileType::FAIL_REPETTION, code);
			flag = true;
			break;
		}
		if (flag == true)
			continue;
		m_existingSchemes.push_back(chains);



	} while (pss::next_combination(linksCombi, m_allLinks.size() - 1));
}

std::vector<int> pss::TGenerate::create_Vect_BF(std::vector<std::vector<int>> Chains)
{
	auto N = pss::TSingletons::getInstance()->getNumberOfPlanetaryGears();
	size_t b = 0;
	std::vector<int> brakes;
	//�������� ������������ ����
	for (size_t i = 0; i < Chains.size(); i++)
	{
		//�������� ����� ����-�����
		if (Chains[i].size() > 1 && Chains[i][Chains[i].size() - 2] >= 44 && Chains[i][Chains[i].size() - 1] >= 44)
		{
			//std::cout << "���� ����� ����� � �������:\n";
			return brakes;
		}
		//�������� ������ ����� ���������� ������ ����
		for (int j = 1; j <= N; j++)
		{
			b = 0;
			for (int k = 0; k < Chains[i].size(); k++)
			if (Chains[i][k] % 10 == j)
				b++;
			if (b > 1)
			{
				//std::cout << "���� ����� ����� ���������� ������ ����:\n";
				return brakes;
			}
		}
	}
	//����������� ��������
	for (size_t i = 0; i < Chains.size(); i++)
	if (Chains[i][Chains[i].size() - 1] < 44)
		brakes.push_back(Chains[i][0]);
	return brakes;
}	//	�������� ������������ � ����������� ��������� ������������ ��������. ���� ��������� ��� �������� �� ������ - ���������� ������ ������, ���� ������ - ������ � ���������

std::vector<std::vector<int>> pss::TGenerate::create_Chains(int in, int out, const std::vector<int> &links)
{
	//������� ��������� ������� (������ ����� �������� ��������)
	std::vector<std::vector<int>> Chains;
	Chains.resize(links.size() + 2);
	Chains[0].push_back(in);
	Chains[0].push_back(44);
	Chains[1].push_back(out);
	Chains[1].push_back(55);
	for (int i = 0; i < links.size(); i++){
		Chains[i + 2].push_back(links[i] / 100);
		Chains[i + 2].push_back(links[i] % 100);
		std::sort(Chains[i + 2].begin(), Chains[i + 2].end());
	}
	//����� ���������, ��������� �� ������ � �������� �������, ������� �� ��������
	size_t b;
	auto N = pss::TSingletons::getInstance()->getNumberOfPlanetaryGears();
	for (size_t i = 0; i < 3 * N; i++)
	{
		b = 0;
		for (size_t j = 0; j < links.size(); j++){
			if (links[j] / 100 == pss::pos_2_code(i) || links[j] % 100 == pss::pos_2_code(i)){
				b++;
			}
		}
		if (b == 0 && pss::pos_2_code(i) != in && pss::pos_2_code(i) != out){
			Chains.resize(Chains.size() + 1);
			Chains[Chains.size() - 1].push_back(pss::pos_2_code(i));
			b = 0;
		}
	}
	//����� ������� ������
	b = 0;
	for (size_t i = 0; i < Chains.size() - 1; i++){
		for (size_t j = i + 1; j < Chains.size(); j++){
			for (size_t k = 0; k < Chains[i].size(); k++){
				if (pss::in_vect(Chains[j], Chains[i][k]) != -1)
					b = Chains[i][k];
			}
			if (b != 0){
				for (size_t k = 0; k < Chains[i].size(); k++)
					Chains[j].push_back(Chains[i][k]);
				Chains[i].clear();
				Chains[i].push_back(0);
				b = 0;
			}
		}
	}
	//�������� ������ �������
	for (size_t i = 0; i < Chains.size(); i++){
		if (Chains[i][0] == 0){
			Chains.erase(Chains.begin() + i);
			i = i - 1;
		}
	}
	//�������� ����������
	for (size_t i = 0; i < Chains.size(); i++){
		pss::del_repetition(Chains[i]);
	}
	return Chains;
}