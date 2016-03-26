#include "TSingletons.h"
#include <iostream>


pss::TSingletons::TSingletons()
{
	init();
}

void pss::TSingletons::calculateNumbersOfElements()
{
	if (m_w == 0 || m_numberOfPlanetaryGears == 0)
		return;
	switch (m_w)
	{
		case 2:
		{
				  m_numberOfBrakes = m_numberOfPlanetaryGears;
				  m_numberOfFrictions = 0;	// ��� ������������� ������������� �������� �� �������
				  m_numberOfLinks = 2 * m_numberOfPlanetaryGears - m_w;
		}
			break;
		case 3:
		{
				  if (m_numberOfPlanetaryGears == 1)
				  {
					  std::cout << "������: ���� ����������� ��� ��� ���� �������� �������!\n";
					  system("pause");
					  return;
				  }
				  m_numberOfBrakes = m_numberOfPlanetaryGears - 1;
				  m_numberOfFrictions = 2;
				  m_numberOfLinks = 2 * m_numberOfPlanetaryGears - m_w;
		}
			break;
		default:
		{
				   std::cout << "������: ������������ ���������� �������� �������!\n";
				   system("pause");
				   return;
		}
			break;
	}
}

pss::TSingletons* pss::TSingletons::getInstance()
{
	static pss::TSingletons Singletons;
	return &Singletons;
}

pss::TSingletons::~TSingletons()
{
}

pss::TIOFileManager* pss::TSingletons::getIOFileManager()
{
	return pss::TIOFileManager::getInstance();
}

int pss::TSingletons::getNumberOfPlanetaryGears() const
{
	return m_numberOfPlanetaryGears;
}

int pss::TSingletons::getW() const
{
	return m_w;
}

int pss::TSingletons::getNumberOfLinks() const
{
	return m_numberOfLinks;
}

int pss::TSingletons::getNumberOfFrictions() const
{
	return m_numberOfFrictions;
}

int pss::TSingletons::getNumberOfBrakes() const
{
	return m_numberOfBrakes;
}

void pss::TSingletons::setGlobalParameters(int w, int n)
{
	m_w = w;
	m_numberOfPlanetaryGears = n;

	switch (m_w)
	{
	case 2:
	{
			  m_numberOfBrakes = m_numberOfPlanetaryGears;
			  m_numberOfFrictions = 0;	// ��� ������������� ������������� �������� �� �������
			  m_numberOfLinks = 2 * m_numberOfPlanetaryGears - m_w;
	}
		break;
	case 3:
	{
			  if (m_numberOfPlanetaryGears == 1)
			  {
				  std::cout << "������: ���� ����������� ��� ��� ���� �������� �������!\n";
				  system("pause");
				  exit(0);
			  }
			  m_numberOfBrakes = m_numberOfPlanetaryGears - 1;
			  m_numberOfFrictions = 2;
			  m_numberOfLinks = 2 * m_numberOfPlanetaryGears - m_w;
	}
		break;
	default:
	{
			   std::cout << "������: ������������ ���������� �������� �������!\n";
			   system("pause");
			   exit(0);
	}
		break;
	}
	getIOFileManager()->writeInitialData();
}

void pss::TSingletons::init()
{
}