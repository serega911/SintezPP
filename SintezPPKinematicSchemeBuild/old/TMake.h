#pragma once
#include <vector>
#include <algorithm>
#include "TPlanRyad.h"
#include "TWave.h"

bool pred(const std::vector<int> &v1, const std::vector<int> &v2){
	return v1.size() > v2.size();
}

class TMake
{
public:

	TMake(void){
		iKombi[0] = 1;
		iKombi[1] = 2;
		NUM = 0;
	}

	~TMake(void){}

	int Run(const std::vector<size_t> &Input, size_t first_frict_pos){
		CountPlanRyad = Input[0];
		TPlanRyad PlanRyad;
		MasPlanRyad.resize(CountPlanRyad);
		for (size_t i = 0; i < MasPlanRyad.size(); i++){
			PlanRyad.Create(i + 1);
			MasPlanRyad[i] = PlanRyad;
		}
		YmaxPlanRyad = PlanRyad.getYMAX();
		YmaxGearBox = CountPlanRyad * YmaxPlanRyad + 2;
		for (size_t j = 2; j < Input.size(); j++){
			AllLinks.push_back(Input[j]);
		}
		iIn = AllLinks[0];
		int iKombi[] = { 1, 2 };
		TWave Wave;
		int ret;
		CreateMas(V, 0);
		CreateMas(Field, 0);
		for (size_t j = 0; j < AllLinks.size(); j++){
			Wave.Run(Field, YmaxGearBox, AllLinks[j] / 100, AllLinks[j] % 100);
			LinksForPaint.push_back(Wave.Road);

			if (j >= first_frict_pos && AllLinks[j] % 100 != 66 && first_frict_pos != 0)
				for (size_t k = 4; k < Wave.Road.size()-2; k = k+2)
				{
					Field[Wave.Road[k]*YmaxGearBox + Wave.Road[k+1]] = 7777;
					if (k > 2 && k < Wave.Road.size()-2)
						k+=2;
				}
			else
			{
				for (size_t k = 0; k < Wave.Road.size(); k = k+2)			
				{
					Field[Wave.Road[k]*YmaxGearBox + Wave.Road[k+1]] = AllLinks[j];
					if (k > 2 && k < Wave.Road.size()-2)
						k+=2;
				}
			}
		}
		//std::sort(LinksForPaint.begin(), LinksForPaint.end(), pred);
		return 0;
	}

	inline int getCountPlanRyad(){
		return CountPlanRyad;
	}

	inline size_t getYmaxGearBox(){
		return YmaxGearBox;
	}

	inline int getCellV(size_t i){
		if (!(i < 0) && !(i > V.size()-1))
			return V[i];
		else
			return -1;
	}

	inline int getCellLinksForPaint(size_t i, size_t j){
		if ((i >= 0) && (i < LinksForPaint.size()) && (j >= 0) && (j < LinksForPaint[i].size()))
			return LinksForPaint[i][j];
		else
			return -1;
	}

	inline size_t getSizeV(){
		return V.size();
	}

	inline size_t getSizeLinksForPaint(){
		return LinksForPaint.size();
	}

	inline size_t getSizeLinksForPaint(size_t i){
		return LinksForPaint[i].size();
	}

private:
	int	iIn;									//элемент входа
	int YmaxPlanRyad;							//длина строки массива планетарного р€да
	std::vector <TPlanRyad> MasPlanRyad;		//контейнер планетарных р€дов
	std::vector <size_t> AllLinks;					//все св€зи
	std::vector <int> Field;					//поле
	int CountPlanRyad;							// оличество планетарных р€дов
	int YmaxGearBox;							//длина строки массива коробки передач
	std::vector <int> V;
	std::vector <std::vector <int>> LinksForPaint;
	std::vector<size_t>VectType;
	int iKombi[2];
	size_t NUM;

	bool GenNext(std::vector<size_t> &v, size_t MaxLen = 4){
		if (v.size() == 1)
			return false;
		for (int i = v.size() - 1; i > -1; i--){
			if (v[i] != 0 && v[i] < MaxLen){
				v[i]++;
				for (size_t j = i + 1; j < v.size(); j++){
					if (v[j] == MaxLen){
						v[j] = 1;
					}
				}
				return true;
			}
		}
		return false;
	}

	TPlanRyad::type GetType(size_t Num){
		switch (Num){
		case 0:
			return TPlanRyad::default;
		case 1:
			return TPlanRyad::type1;
			break;
		case 2:
			return TPlanRyad::type2;
			break;
		case 3:
			return TPlanRyad::type3;
			break;
		case 4:
			return TPlanRyad::type4;
			break;
		}
		return TPlanRyad::default;
	}

	void TMake::CreateMas(std::vector <int> & v, int a){
		//построчна€ запись пол€ из массивов планетарных р€дов
		v.clear();
		TPlanRyad PlanRyad;
		PlanRyad.Create(0);
		int In = (iIn-44)/100%10;
		for (int i = 0; i < YmaxGearBox; i++)
			v.push_back(9999);
		for (size_t i = 0; i < PlanRyad.getXMAX(); i++){
			v.push_back(9999);
			for (size_t k = 0; k < MasPlanRyad.size(); k++){
				for (int j = 0; j < YmaxPlanRyad; j++){
					if ((k+1) == In) 
						v.push_back(MasPlanRyad[k].getCellMas(a,i*YmaxPlanRyad+j));
					if ((k+1) != In) 
						v.push_back(MasPlanRyad[k].getCellMas(0,i*YmaxPlanRyad+j));
				}
			}
			v.push_back(9999);}
		for (int i = 0; i < YmaxGearBox; i++)
			v.push_back(9999);
		for (int i = 1; i < YmaxGearBox-1; i++)
			v[YmaxGearBox + i] = 6600;														//корпус
		v[YmaxGearBox*PlanRyad.getXMAX() + 1] = 4400;										//вход
		v[YmaxGearBox*PlanRyad.getXMAX() + MasPlanRyad.size()*PlanRyad.getYMAX()] = 5500;			//выход
	}



	
};

