#include "../Libraries/Gaus.h"
#include "../Libraries/Singletons.h"

NS_CORE_USING

void Gaus::solve()
{
	m_solution.clear();
	int n = m_system.size();
	for (int i = 0; i < n; ++i)
	{
		int k = i;
		for (int j = i + 1; j<n; ++j)
		if (abs(m_system[j][i]) > abs(m_system[k][i]))
			k = j;
		if (k != i)
			std::swap(m_system[i], m_system[k]);
		for (int j = i + 1; j <= n; ++j)
			if ( m_system[i][i] != 0 )
				m_system[i][j] /= m_system[i][i];
			else
				return;
		for (int j = 0; j < n; ++j)
			if ( j != i )
				for ( int k = i + 1; k <= n; ++k )
					m_system[j][k] -= m_system[i][k] * m_system[j][i];
	}
	for (int i = 0; i < n; ++i)
		m_solution.push_back(m_system[i][n]);
}

void Gaus::createSystem(const Code & Code, const InternalGearRatios &k)
{
	auto code = Code.getCode();

	auto N = Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
	auto L = Singletons::getInstance()->getGeneralData()._numberOfLinks;
 
	m_system.resize(3 * N);
	for (auto& it : m_system)
		it.resize(3 * N + 1);
	//� ������ N ����� ���������� ��������� �������. 
	//��� ������ ������� �� ������� ��� ��� ��� �������� ������ ������� �� ���� � �� �� �������
	for ( size_t i = 0; i < k.size(); i++ ){
		m_system[i][3 * i] = 1;
		m_system[i][3 * i + 1] = -k[i].getValue();
		m_system[i][3 * i + 2] = k[i].getValue() - 1;
	}
	//system("pause");
	//������� ���������
	for ( size_t i = N; i < N + L + 1; i++ )
		for ( size_t j = 0; j < 3 * N + 1; j++ )
			m_system[i][j] = 0;
	//� ��������� countSV ����� ���������� �����
	for ( size_t i = N, j = 2; i < N + L; i++, j++ ){
		m_system[i][code[j].getElem1().getSerialNumber()] = 1;
		m_system[i][code[j].getElem2().getSerialNumber()] = -1;
	}
	//��������� ��� �����, ���������� � ������� �����
	m_system[N + L][code[0].getElem1().getSerialNumber()] = 1;
	m_system[N + L][N * 3] = 1;
}

void Gaus::createSystemDrivers( const TLinkArray& drivers )
{
	auto N = Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
	auto L = Singletons::getInstance()->getGeneralData()._numberOfLinks;
	for ( size_t i = 0; i < drivers.size(); i++ )
	{
		Link driver = drivers[i];
		for (size_t j = 0; j < 3 * N + 1; j++)
		{
			m_system[N + L + 1 + i][j] = 0;
		}
		if (driver.getElem2() == Element::BRAKE)	//driver - ������
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

std::vector<std::vector<double>> Gaus::getSystem() const
{
	return m_system;
}

const std::vector<double>& Gaus::getSolution() const
{
	return m_solution;
}
