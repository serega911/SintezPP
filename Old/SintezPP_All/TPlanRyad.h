#pragma once
#include<vector>

class TPlanRyad
{
public:

	TPlanRyad(void){
		YMAX = 9;
		XMAX = 13;
		size_t YC = (YMAX - 1) / 2;
		size_t XC = (XMAX - 1) / 2;
		const size_t mas_size = 7;
		Mas.resize(mas_size);
		for (size_t i = 0; i < mas_size; i++)
			Mas[i].resize(XMAX*YMAX);
		for (size_t i = 1; i < XC-1; i++){
			Mas[1][i*YMAX-1+YC] = 9999;
			Mas[2][i*YMAX+1+YC] = 9999;
		}
		for (size_t i = XC-1; i < XC+2; i++){
			if (i != XC){
				Mas[3][i*YMAX-1+YC] = 9999;
				Mas[4][i*YMAX+1+YC] = 9999;
			}
			Mas[3][i*YMAX-2+YC] = 9999;
			Mas[4][i*YMAX+2+YC] = 9999;
		}
		for (size_t i = XC+2; i < XMAX; i++){
			Mas[5][i*YMAX+1+YC] = 9999;
			Mas[6][i*YMAX-1+YC] = 9999;
		}
	}

	~TPlanRyad(void){}

	void Create(int Num){
		int YC = (YMAX-1)/2;
		int XC = (XMAX-1)/2;
		Mas[0][(XC-2)*YMAX+YC] = 2000 + Num*100;
		Mas[0][(XC-1)*YMAX+YC] = 9999;
		Mas[0][(XC)*YMAX+YC-1] = 3000 + Num*100;
		Mas[0][(XC)*YMAX+YC] = 3000 + Num*100;
		Mas[0][(XC)*YMAX+YC+1] = 3000 + Num*100;
		Mas[0][(XC+1)*YMAX+YC] = 9999;
		Mas[0][(XC+2)*YMAX+YC] = 1000 + Num*100;
		size_t MasSize = Mas.size();
		for (size_t i = 1; i < MasSize; i++)
			Invers(i);
	}

	void Invers(int Num){
		for (size_t i = 0; i < XMAX*YMAX; i++)
			if (Mas[0][i] != 0)
				Mas[Num][i] = Mas[0][i];
	}

	inline size_t getXMAX(){
		return XMAX;
	}

	inline size_t getYMAX(){
		return YMAX;
	}

	inline int getCellMas(size_t i, size_t j){
		if (!(i < 0) && !(i > (Mas.size()-1)) && !(j < 0) && !(j > (Mas[i].size()-1)))
			return Mas[i][j];
		else
			return -1;
	}

private:
	size_t XMAX;
	size_t YMAX;
	std::vector<std::vector<size_t>>Mas;
};

