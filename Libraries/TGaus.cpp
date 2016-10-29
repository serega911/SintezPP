#include "../Libraries/TGaus.h"
#include "../Libraries/TSingletons.h"
#include "../Libraries/func_lib.h"

NS_CORE_USING

void TGaus::solve()
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

void TGaus::createSystem(const TCode & Code, const TK &k)
{
	auto code = Code.getCode();

	auto N = TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
	auto L = TSingletons::getInstance()->getGeneralData()._numberOfLinks;
 
	m_system.resize(3 * N);
	for (auto& it : m_system)
		it.resize(3 * N + 1);
	//в первые N строк записываем уравнения Виллиса. 
	//Эти строки никогда не очищаем так как все значения всегда пишутся на одни и те же позиции
	for ( size_t i = 0; i < k.size(); i++ ){
		m_system[i][3 * i] = 1;
		m_system[i][3 * i + 1] = -k[i].getValue();
		m_system[i][3 * i + 2] = k[i].getValue() - 1;
	}
	//system("pause");
	//очищаем уравнения
	for ( size_t i = N; i < N + L + 1; i++ )
		for ( size_t j = 0; j < 3 * N + 1; j++ )
			m_system[i][j] = 0;
	//в следующие countSV строк записываем связи
	for ( size_t i = N, j = 2; i < N + L; i++, j++ ){
		m_system[i][code[j].getElem1().getSerialNumber()] = 1;
		m_system[i][code[j].getElem2().getSerialNumber()] = -1;
	}
	//уравнение для звена, связанного с ведущим валом
	m_system[N + L][code[0].getElem1().getSerialNumber()] = 1;
	m_system[N + L][N * 3] = 1;
}

void TGaus::createSystemDrivers( const TLinkArray& drivers )
{
	auto N = TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
	auto L = TSingletons::getInstance()->getGeneralData()._numberOfLinks;
	for ( size_t i = 0; i < drivers.size(); i++ )
	{
		TLink driver = drivers[i];
		for (size_t j = 0; j < 3 * N + 1; j++)
		{
			m_system[N + L + 1 + i][j] = 0;
		}
		if (driver.getElem2() == TElement::BRAKE)	//driver - тормоз
		{
			m_system[N + L + 1 + i][driver.getElem1().getSerialNumber()] = 1;
		}
		else	//driver - фрикцион
		{
			m_system[N + L + 1 + i][driver.getElem1().getSerialNumber()] = 1;
			m_system[N + L + 1 + i][driver.getElem2().getSerialNumber()] = -1;
		}
	}
}

std::vector<std::vector<double>> TGaus::getSystem() const
{
	return m_system;
}

const std::vector<double>& TGaus::getSolution() const
{
	return m_solution;
}
