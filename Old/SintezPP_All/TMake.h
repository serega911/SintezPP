#pragma once
#include<vector>
#include"TPlanRyad.h"
#include"TWave.h"

class TMake
{
public:

	TMake(void){}

	~TMake(void){}

	int Run(const std::vector<size_t> &Input){
		//Заполнение векторов связей===============================================================
		//Input = v1;
		//Определение количества планетарных рядов
		CountPlanRyad = Input[0];
		//Определение элемента входа
		iIn = Input[2];
		//определение связей
		for (size_t j = 3; j < Input.size(); j++){
			AllLinks.push_back(Input[j]);
		}
		//Формирование объектов=============================================================================================
		//создание массива начальных ограничений
		MasPlanRyad.resize(CountPlanRyad);
		TPlanRyad PlanRyad;
		for (size_t i = 0; i < MasPlanRyad.size(); i++){
			PlanRyad.Create(i+1);
			MasPlanRyad[i] = PlanRyad;
		}
		YmaxPlanRyad = PlanRyad.getYMAX();
		YmaxGearBox = CountPlanRyad * YmaxPlanRyad + 2;
		int iKombi[] = {1,2};
		for (int i = 0; i < 2; i++){
			if ((iIn-44)/1000 == 1) iKombi[i] = iKombi[i] + 4;;
			if ((iIn-44)/1000 == 3) iKombi[i] = iKombi[i] + 2;
		}
	//Начало трассировки=============================================================================================
		LinksForPaint.resize(AllLinks.size()+2);
		std::vector<int> TMP;
		TMP.resize(AllLinks.size());
		TMP = AllLinks;
		TWave Wave;
		int ret;
		int link;
		int Num;
		size_t count;
		for (int i = 0; i < 2; i++){
			count = 0;
			Num = 0;
	Lab:	CreateMas(Field,0);
			LinksForPaint.clear();
			V.clear();
			CreateMas(V,iKombi[i]);
			ret = 0;
	//построение входа
			ret += Wave.Run(V, YmaxGearBox, iIn/100, iIn%100);
			if (ret != 0)
				continue;
			for (size_t k = 0; k < Wave.Road.size(); k = k+2)
				Field[Wave.Road[k]*YmaxGearBox + Wave.Road[k+1]] = iIn;
			for (size_t k = 2; k < Wave.Road.size()-2; k = k+2)
				V[Wave.Road[k]*YmaxGearBox + Wave.Road[k+1]] = iIn;
			LinksForPaint.push_back(Wave.Road);
	//построение остальных связей
			for (size_t j = 0; j < AllLinks.size(); j++){
				ret += Wave.Run(Field, YmaxGearBox, AllLinks[j]/100, AllLinks[j]%100);
				if (ret != 0){
					link = AllLinks[0];
					AllLinks[0] = AllLinks[j];
					AllLinks[j] = link;
					count++;
					if ((count > AllLinks.size()*AllLinks.size()) || (Num == j)) break;
					Num = j;
					goto Lab;
				}
				for (size_t k = 0; k < Field.size(); k++){
					if ((Field[k] == ((AllLinks[j]/100)*100)) && (Field[k] != 6600)) Field[k] = AllLinks[j];
					if ((Field[k] == ((AllLinks[j]%100)*100)) && (Field[k] != 6600)) Field[k] = AllLinks[j];
				}
				for (size_t k = 0; k < Wave.Road.size(); k = k+2)
					Field[Wave.Road[k]*YmaxGearBox + Wave.Road[k+1]] = AllLinks[j];
				LinksForPaint.push_back(Wave.Road);
			}
			if (ret == 0){
				return 0;
			}
		}
		LinksForPaint.clear();
		if (Retry(TMP) == 0){
			return 0;
		}
		V.clear();
		return 1;
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
		if (!(i < 0) && !(i > LinksForPaint.size()-1) && !(j < 0) && !(j > LinksForPaint[i].size()-1))
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
	int YmaxPlanRyad;							//длина строки массива планетарного ряда
	//std::vector <size_t> Input;					//вектор кода
	std::vector <TPlanRyad> MasPlanRyad;		//контейнер планетарных рядов
	std::vector <int> AllLinks;					//все связи
	std::vector <int> Field;					//поле
	int CountPlanRyad;							//Количество планетарных рядов
	int YmaxGearBox;							//длина строки массива коробки передач
	std::vector <int> V;
	std::vector <std::vector <int>> LinksForPaint;


	void TMake::CreateMas(std::vector <int> & v, int a){
		//построчная запись поля из массивов планетарных рядов
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
					if ((k+1) == In) v.push_back(MasPlanRyad[k].getCellMas(a,i*YmaxPlanRyad+j));
					if ((k+1) != In) v.push_back(MasPlanRyad[k].getCellMas(0,i*YmaxPlanRyad+j));
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

	void TMake::CreateGearBox(void);

	int TMake::Retry(std::vector<int> &v1){
		int iKombi[] = {1,2};
		for (int i = 0; i < 2; i++){
			if ((iIn-44)/1000 == 1) iKombi[i] = iKombi[i] + 4;;
			if ((iIn-44)/1000 == 3) iKombi[i] = iKombi[i] + 2;
		}
		LinksForPaint.resize(AllLinks.size()+2);
		Field.clear();
		std::vector<int> TMP;
		TMP.resize(v1.size());
		TWave Wave;
		int count = 0;
		int ret;
		int link;
		for (int i = 0; i < 2; i++){
			count = 0;
			link = 0;
	Lab1:	CreateMas(Field,0);
			LinksForPaint.clear();
			V.clear();
			CreateMas(V,iKombi[i]);
			ret = 0;
	//построение входа
			ret += Wave.Run(V, YmaxGearBox, iIn/100, iIn%100);
			if (ret != 0) continue;
			for (size_t k = 0; k < Wave.Road.size(); k = k+2)
				Field[Wave.Road[k]*YmaxGearBox + Wave.Road[k+1]] = iIn;
			LinksForPaint.push_back(Wave.Road);
	//построение остальных связей
			for (size_t j = 0; j < v1.size(); j++){
				ret += Wave.Run(Field, YmaxGearBox, v1[j]/100, v1[j]%100);
				if (ret != 0){
					TMP.clear();
					TMP.push_back(v1[j]);
					for (size_t k = 0; k < v1.size(); k++)
						if (k != j) TMP.push_back(v1[k]);
					v1.clear();
					v1 = TMP;
					count++;
					if (((size_t)count > v1.size()*2) || (j == link)) break;
					link = 1;
					goto Lab1;
				}
				for (size_t k = 0; k < Field.size(); k++){
					if ((Field[k] == ((v1[j]/100)*100)) && (Field[k] != 6600)) Field[k] = v1[j];
					if ((Field[k] == ((v1[j]%100)*100)) && (Field[k] != 6600)) Field[k] = v1[j];
				}
				for (size_t k = 0; k < Wave.Road.size(); k = k+2)
					Field[Wave.Road[k]*YmaxGearBox + Wave.Road[k+1]] = v1[j];
				LinksForPaint.push_back(Wave.Road);
			}
			if (ret == 0){
				return 0;
			}
		}
		LinksForPaint.clear();
		V.clear();
		return 1;
	}
};

