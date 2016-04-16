#include "../Libraries/TGaus.h"
#include "../Libraries/TSingletons.h"
#include "../Libraries/func_lib.h"

void pss::TGaus::solve()
{
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

void pss::TGaus::createSystem(const pss::TCode & Code, const pss::TK &k)
{
	auto N = pss::TSingletons::getInstance()->getNumberOfPlanetaryGears();
	auto L = pss::TSingletons::getInstance()->getNumberOfLinks();

	m_system.resize(3 * N);
	for (auto& it : m_system)
		it.resize(3 * N + 1);
	//� ������ N ����� ���������� ��������� �������. 
	//��� ������ ������� �� ������� ��� ��� ��� �������� ������ ������� �� ���� � �� �� �������
	for (int i = 0; i < k.size(); i++){
		m_system[i][3 * i] = 1;
		m_system[i][3 * i + 1] = -k[i];
		m_system[i][3 * i + 2] = k[i] - 1;
	}
	//system("pause");
	//������� ���������
	for (int i = N; i < N + L + 1; i++)
		for (int j = 0; j < 3 * N + 1; j++)
			m_system[i][j] = 0;
	//� ��������� countSV ����� ���������� �����
	for (int i = N, j = 2; i < N + L; i++, j++){
		m_system[i][Code[j].getElem1().getSerialNumber()] = 1;
		m_system[i][Code[j].getElem2().getSerialNumber()] = -1;
	}
	//��������� ��� �����, ���������� � ������� �����
	m_system[N + L][Code[0].getElem1().getSerialNumber()] = 1;
	m_system[N + L][N * 3] = 1;
}

void pss::TGaus::createSystemDrivers(const std::vector<pss::TLink>& drivers)
{
	auto N = pss::TSingletons::getInstance()->getNumberOfPlanetaryGears();
	auto L = pss::TSingletons::getInstance()->getNumberOfLinks();
	for (int i = 0; i < drivers.size(); i++)
	{
		pss::TLink driver = drivers[i];
		for (int j = 0; j < 3 * N + 1; j++)
		{
			m_system[N + L + 1 + i][j] = 0;
		}
		//std::cout << "driver: " << driver << std::endl;
		if (driver.getElem2() == pss::TElement::BRAKE)	//driver - ������
		{
			m_system[N + L + 1 + i][driver.getElem1().getSerialNumber()] = 1;
		}
		else	//driver - ��������
		{
			m_system[N + L + 1 + i][driver.getElem1().getSerialNumber()] = 1;
			m_system[N + L + 1 + i][driver.getElem2().getSerialNumber()] = -1;
		}
	}
}

const std::vector<float>& pss::TGaus::getSolution()
{
	return m_solution;
}
