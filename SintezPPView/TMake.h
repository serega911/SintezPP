#pragma once
#include <vector>
#include <algorithm>
#include "TPlanetaryGearSet.h"
#include "TWave.h"

bool pred(const std::vector<int> &v1, const std::vector<int> &v2){
	return v1.size() > v2.size();
}

class TMake
{
public:

	TMake(void);
	~TMake(void);
	int Run(const std::vector<size_t> &Input, size_t first_frict_pos);
	int getCountPlanRyad();
	size_t getYmaxGearBox();
	int getCellV(size_t i);
	int getCellLinksForPaint(size_t i, size_t j);
	size_t getSizeV();
	size_t getSizeLinksForPaint();

	size_t getSizeLinksForPaint(size_t i);

private:
	int	iIn;									//������� �����
	int YmaxPlanRyad;							//����� ������ ������� ������������ ����
	std::vector <ari::TPlanetaryGearSet> MasPlanRyad;	//��������� ����������� �����
	std::vector <size_t> AllLinks;				//��� �����
	std::vector <int> Field;					//����
	int CountPlanRyad;							//���������� ����������� �����
	int YmaxGearBox;							//����� ������ ������� ������� �������
	std::vector <int> V;
	std::vector <std::vector <int>> LinksForPaint;
	std::vector<size_t>VectType;
	int iKombi[2];
	size_t NUM;

	bool GenNext(std::vector<size_t> &v, size_t MaxLen = 4);

	ari::TPlanetaryGearSet::ePlanetarySetType GetType(size_t Num);

};

