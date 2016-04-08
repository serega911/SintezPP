#include "../Libraries/TGaus.h"
#include "../Libraries/TSingletons.h"
#include "../Libraries/func_lib.h"

void pss::TGaus::solve()
{
	const double EPS = 0.0001;
	m_solution.clear();
	int n = m_system.size();
	for (int i = 0; i < n; ++i) {
		int k = i;
		for (int j = i + 1; j<n; ++j)
		if (abs(m_system[j][i]) > abs(m_system[k][i]))
			k = j;
		if (k != i)
			std::swap(m_system[i], m_system[k]);
		for (int j = i + 1; j <= n; ++j)
		if (m_system[i][i] != 0)
			m_system[i][j] /= m_system[i][i];
		else
			return;
		for (int j = 0; j < n; ++j)
		if (j != i)
		for (int k = i + 1; k <= n; ++k)
			m_system[j][k] -= m_system[i][k] * m_system[j][i];
	}
	for (int i = 0; i < n; ++i)
		m_solution.push_back(m_system[i][n]);
}

void pss::TGaus::createSystem(const pss::TCode & Code, const pss::TK &k, int driver)
{
	auto N = pss::TSingletons::getInstance()->getNumberOfPlanetaryGears();
	auto L = pss::TSingletons::getInstance()->getNumberOfLinks();
	auto F = pss::TSingletons::getInstance()->getNumberOfFrictions();
	auto B = pss::TSingletons::getInstance()->getNumberOfBrakes();
	auto W = pss::TSingletons::getInstance()->getW();

	m_system.resize(3 * N);
	for (auto& it : m_system)
		it.resize(3 * N + 1);
	//в первые N строк записываем уравнения Виллиса. 
	//Эти строки никогда не очищаем так как все значения всегда пишутся на одни и те же позиции
	for (int i = 0; i < k.size(); i++){
		m_system[i][3 * i] = 1;
		m_system[i][3 * i + 1] = -k[i];
		m_system[i][3 * i + 2] = k[i] - 1;
	}

	//system("pause");
	//очищаем уравнения
	for (int i = N; i < N + L + 1; i++)
	for (int j = 0; j < 3 * N + 1; j++)
		m_system[i][j] = 0;
	//в следующие countSV строк записываем связи
	for (int i = N, j = 2; i < N + L; i++, j++){
		m_system[i][pss::code_2_pos(Code[j] / 100)] = 1;
		m_system[i][pss::code_2_pos(Code[j] % 100)] = -1;
	}
	//уравнение для звена, связанного с ведущим валом
	m_system[N + L][pss::code_2_pos(Code[0] / 100)] = 1;
	m_system[N + L][N * 3] = 1;
}
