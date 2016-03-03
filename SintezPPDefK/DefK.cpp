#include "DefK.h"
#include "../Libraries/func_lib.h"
#include <algorithm>
#include <iostream>

pss::DefK::DefK(const pss::TI& I)
{
	m_iTarget = I;
}

pss::DefK::DefK() : DefK({ {}, 0.01f })
{

}

pss::DefK::~DefK(void){}

pss::TK pss::DefK::Run(const pss::TCode& Code, pss::TK K)
{
	do{
		K.print();
		if (PodModul(Code, K))
		{
			K.setFinded();
			return K;
		}
		//system("pause");
	}while(K.next());
	return K;
}

bool pss::DefK::PodModul(const pss::TCode & Code, const pss::TK &k)
{
	m_matrix.resize(3 * Code.getN());
	for (auto& it : m_matrix)
		it.resize(3 * Code.getN() + 1);
	//в первые N строк записываем уравнения Виллиса. 
	//Эти строки никогда не очищаем так как все значения всегда пишутся на одни и те же позиции
	for (int i = 0; i < k.size(); i++){
		m_matrix[i][3 * i] = 1;
		m_matrix[i][3 * i + 1] = -k[i];
		m_matrix[i][3 * i + 2] = k[i] - 1;
	}
;
		//system("pause");
		//очищаем уравнения
	for (int i = Code.getN(); i < Code.getN() + Code.getCountL() + 1; i++)
		for (int j = 0; j < 3 * Code.getN() + 1; j++)
				m_matrix[i][j] = 0;
		//в следующие countSV строк записываем связи
	for (int i = Code.getN(), j = 2; i < Code.getN() + Code.getCountL(); i++, j++){
			m_matrix[i][pss::code_2_pos(Code[j] / 100)] = 1;
			m_matrix[i][pss::code_2_pos(Code[j] % 100)] = -1;
		}
		//уравнение для звена, связанного с ведущим валом
	m_matrix[Code.getN() + Code.getCountL()][pss::code_2_pos(Code[0] / 100)] = 1;
	m_matrix[Code.getN() + Code.getCountL()][Code.getN() * 3] = 1;
			
	//print(Matrix, "11	21	31	12	22	32	13	23	33	RP \n___________________________________________________________________________");
	
	pss::TI tmpI({}, 0.01);	//вектор для полученных передаточных отношений при данном наборе K
	double TMP=0;

	std::vector<int> vect_combi_drive(Code.getW()-1);
	for (int i = 0; i < Code.getW() - 1; i++)
	vect_combi_drive[i] = i;
	//перебераем все сочетания включения элементов управления (фрикционов и тормозов) без повторений
	do {
		//записываем в матрицу уравнения с элементами управления
		for (int i = 0; i < vect_combi_drive.size(); i++)
		{
			int driver = Code[2 + Code.getCountL() + vect_combi_drive[i]];
			//std::cout << "driver: " << driver << std::endl;
			if (driver%100 == 66)	//driver - тормоз
				m_matrix[Code.getN() + Code.getCountL() + 1 + i][pss::code_2_pos(driver / 100)] = 1;
			else	//driver - фрикцион
			{
				m_matrix[Code.getN() + Code.getCountL() + 1 + i][pss::code_2_pos(driver / 100)] = 1;
				m_matrix[Code.getN() + Code.getCountL() + 1 + i][pss::code_2_pos(driver % 100)] = -1;
			}
		}
		//print(Matrix, "11	21	31	12	22	32	13	23	33	RP\n___________________________________________________________________________");
		//решаем систему уравнений
		TMP = pss::GAUS(m_matrix, pss::code_2_pos(Code[1] / 100));
		//проверяем результат
		if (abs(TMP) > 0.001)
			tmpI.push_back(1.0 / TMP);
		else
			return false;
		//очищаем уравнения с элементами управления
		for (int i = Code.getN() + Code.getCountL() + 1; i < Code.getN() + Code.getCountL() + Code.getW(); i++)
			for (int j = 0; j < 3 * Code.getN() + 1; j++)
				m_matrix[i][j] = 0;
	} while (pss::next_combination(vect_combi_drive, Code.getCountF() + Code.getCountB() - 1));
			//сравниваем полученные передаточные отношения с искомыми
	if (m_iTarget == tmpI)
	{
		m_iReal = tmpI;
		return true;
	}
	else
		return false;
}

