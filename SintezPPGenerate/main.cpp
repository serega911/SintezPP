#include <iostream>
#include <vector>
#include <algorithm>
#include <direct.h>
#include "../Libraries/func_lib.h"
#include "../Libraries/TCode.h"
#include "../Libraries/TSingletons.h"

std::vector<int> create_Vect_BF(std::vector<std::vector<int>>, int);
std::vector<std::vector<int>> create_Chains(int, int, const std::vector<int> &, int);

int main()
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

	//	��������� ���� ��������� ������
	std::vector<int> tmp;
	std::vector<int> vect_all_links;		//	������ ���� ��������� ������
	//	��������� ������ ���� ��������� ������, ���������� ����� ����� ���������� ������ ����.
	for (int i = 0; i <= 3 * (N - 1); i++)
		for (int j = (i / 3 + 1) * 3; j < 3 * N; j++)
			vect_all_links.push_back(pss::pos_2_code(i) * 100 + pss::pos_2_code(j));
	//	��������� �����
	pss::TCode C(W, N);
	std::vector<std::vector<std::vector<int>>> chains_all;	//	��� ������� ������
	for (int in = 0; in < 3 * N; in++)				//	���� �� ��� ������
		for (int out = 0; out < 3 * N; out++)			//	����� �� ��� ������
		{
			if (in != out)							//	��������: ���� � ����� �� ����� ���� ����� � ��� �� ���������
			{
				C.clear();
				C.setIn(pss::pos_2_code(in));
				C.setOut(pss::pos_2_code(out));
				std::vector<int> vect_links;			//	������ ������
				std::vector<int> vect_combi_links;		//	������ ��������� ������
				//	������� ������ ��������� ������ �� ���� ��������� ������ �� Count_L+Count_F (���������� ������ + ���������� ����������) ��� ����������: 0,1,2,3...
				for (int i = 0; i < pss::TSingletons::getInstance()->getNumberOfLinks(); i++)
					vect_combi_links.push_back(i);
				//	� ����� ���������� ��� ��������� ��������� ������
				do{
					//	��������� ������ ������ � ������ ���������������� ���������
					vect_links.clear();
					for (int i = 0; i < vect_combi_links.size(); i++)
						vect_links.push_back(vect_all_links[vect_combi_links[i]]);
					C.setLinks(vect_links);
					//	���������� ������� ������
					std::vector<std::vector<int>> chains = create_Chains(pss::pos_2_code(in), pss::pos_2_code(out), vect_links, N);
					bool flag = false;
					for (size_t i = 0; i < chains_all.size(); i++)
						if (chains_all[i] == chains)
						{
							tmp.clear();
							C.setFrictions(tmp);
							C.setBrakes(tmp);
							pss::TSingletons::getInstance()->getIOFileManager()->writeToFile(pss::TIOFileManager::eOutputFileType::FAIL_REPETTION, C);
							flag = true;
							break;
						}
					if (flag == true)
						continue;
					chains_all.push_back(chains);
					//	���������� ��������, �� ������� ����� ���������� �������� ��� ������
					std::vector<int> vect_all_FB = create_Vect_BF(chains, N);			//	������ ����������
					tmp = vect_all_FB;
					tmp.push_back(pss::pos_2_code(in));
					tmp.push_back(pss::pos_2_code(out));
					if (vect_all_FB.size() == pss::TSingletons::getInstance()->getNumberOfBrakes() + pss::TSingletons::getInstance()->getNumberOfFrictions())
					{
						std::vector<int> vect_all_frict;		//	������ ���� ��������� ����������
						std::vector<int> vect_combi_frict;		//	������ ��������� ����������
						std::vector<int> vect_frict;			//	������ ����������
						for (int i = 0; i < tmp.size(); i++)
							for (int j = i + 1; j < tmp.size(); j++)
								vect_all_frict.push_back(tmp[i] * 100 + tmp[j]);
						//	������� ������ ��������� ���������� �� ������ �� Count_F (���������� ����������) ��� ����������: 0,1...
							for (int i = 0; i < pss::TSingletons::getInstance()->getNumberOfFrictions(); i++)
							vect_combi_frict.push_back(i);
						//	� ����� ���������� ��� ��������� ��������� ����������
						do{
							//	��������� ������ ���������� � ������ ���������������� ���������
							vect_frict.clear();
							for (int i = 0; i < vect_combi_frict.size(); i++)
								vect_frict.push_back(vect_all_frict[vect_combi_frict[i]]);
							C.setFrictions(vect_frict);
							std::vector<int> vect_combi_brakes;		//	������ ��������� ��������
							//	������� ������ ��������� �������� �� ���� ��������� �� Count_B
							for (int i = 0; i < pss::TSingletons::getInstance()->getNumberOfBrakes(); i++)
								vect_combi_brakes.push_back(i);
							do{
								std::vector<int> vect_brakes;	//	������ ��������
								//	��������� ������ �������� � ������ ���������������� ���������
								for (int i = 0; i < vect_combi_brakes.size(); i++)
									vect_brakes.push_back(vect_all_FB[vect_combi_brakes[i]]);
								C.setBrakes(vect_brakes);
								//C.print();
								if (C.check())
									pss::TSingletons::getInstance()->getIOFileManager()->writeToFile(pss::TIOFileManager::eOutputFileType::DONE, C);
								else
									pss::TSingletons::getInstance()->getIOFileManager()->writeToFile(pss::TIOFileManager::eOutputFileType::FAIL_FREE, C);
							} while (pss::next_combination(vect_combi_brakes, vect_all_FB.size() - 1));
						} while (pss::next_combination(vect_combi_frict, vect_all_frict.size() - 1));
					}
					else
					{
						if (vect_all_FB.size() != 0)
						{
							tmp.clear();
							C.setFrictions(tmp);
							C.setBrakes(tmp);
							pss::TSingletons::getInstance()->getIOFileManager()->writeToFile(pss::TIOFileManager::eOutputFileType::FAIL_N, C);
						}
						else
						{
							tmp.clear();
							C.setFrictions(tmp);
							C.setBrakes(tmp);
							pss::TSingletons::getInstance()->getIOFileManager()->writeToFile(pss::TIOFileManager::eOutputFileType::FAIL_0, C);
						}
					}
				} while (pss::next_combination(vect_combi_links, vect_all_links.size() - 1));
			}
		}
	system("pause");
	return 0;
}

std::vector<int> create_Vect_BF(std::vector<std::vector<int>> Chains, int N)
{
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

std::vector<std::vector<int>> create_Chains(int in, int out, const std::vector<int> &links, int N)
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