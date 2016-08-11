#pragma once
#include<vector>

class TWave
{
public:

	TWave(void)
	{
	Direction = 2;
	}

	~TWave(void){}

	int Run(const std::vector<int> &MasField, int LStr, int Start, int Finish){
		std::vector<int> Mas = MasField;
		size_t MasSize = Mas.size();
		Road.clear();
		Direction = 2;
		if (Finish == 66)
			Direction = 1;
		int XMAX = MasSize / LStr;
		int YMAX = LStr;
		for (size_t i = 0; i < MasSize; i++){
			if (Mas[i]/100 == Start)
			{ 
				Mas[i] = XMAX*YMAX;
				continue;
			}
			if (Mas[i]%100 == Start){
				Mas[i] = XMAX*YMAX;
				continue;
			}
			if (Mas[i] == 0){
				Mas[i] =  XMAX*YMAX+1;
				continue;
			}
			if (Mas[i]/100 == Finish){
				Mas[i] = 0;
				continue;
			}
			if ((Mas[i]%100 == Finish) && (Finish != 66)){
				Mas[i] = 0;
				continue;
			}
			if ((Mas[i] < XMAX*YMAX) && (Mas[i] > 0)) 
				Mas[i] = XMAX*YMAX+2;
		}
		int Ni = 0;
		int Nk = XMAX * YMAX;
		//Распространение волны
		while (Ni < Nk){
			for (int i = 0; i < XMAX; i++)
				for (int j = 0; j < YMAX; j++){
					if (Mas[i*YMAX+j] == Ni){				
						if (Mas[(i + 1)*YMAX + j] == XMAX*YMAX + 1)
							Mas[(i + 1)*YMAX + j] = Ni + 1;
						if (Mas[(i - 1)*YMAX + j] == XMAX*YMAX + 1)
							Mas[(i-1)*YMAX+j] = Ni+1;
						if (Mas[i*YMAX + j + 1] == XMAX*YMAX + 1)
							Mas[i*YMAX+j+1] = Ni+1;	
						if (Mas[i*YMAX + j - 1] == XMAX*YMAX + 1)
							Mas[i*YMAX+j-1] = Ni+1;
					}
				}
			Ni++;
		}
		//Поиск оптимального пути
		int x = 0;
		int y = 0;
		int min = XMAX*YMAX;
		for (int i = 0; i < XMAX; i++)
				for (int j = 0; j < YMAX; j++){
					if (Mas[i*YMAX + j] == XMAX*YMAX){
						if (Mas[(i-1)*YMAX+j] < min){
							min = Mas[(i-1)*YMAX+j];
							x = i;
							y = j;
						}
						if (Mas[i*YMAX+(j-1)] < min){
							min = Mas[i*YMAX+(j-1)];
							x = i;
							y = j;
						}
						if (Mas[(i+1)*YMAX+j] < min){
							min = Mas[(i+1)*YMAX + j];
							x = i;
							y = j;
						}
						if (Mas[i*YMAX+(j+1)] < min){
							min = Mas[i*YMAX+(j+1)];
							x = i;
							y = j;
						}
					}
				}
		if ((x == 0) && (y == 0)) return 1;
		Road.push_back(x);
		Road.push_back(y);
		int x1 = 0;
		int y1 = 0;	
		int et = Mas[x*YMAX+y];
		while (Mas[x*YMAX+y] != 0){
			switch (Direction){
			case 1:
				if (Mas[x*YMAX+(y-1)] < et){
					et = Mas[x*YMAX+(y-1)];
					x1 = x;
					y1 = y - 1;
				}
				if (Mas[x*YMAX+(y+1)] < et){
					et = Mas[x*YMAX+(y+1)];
					x1 = x;
					y1 = y+1;
				}
				if (Mas[(x-1)*YMAX+y] < et){
					et = Mas[(x-1)*YMAX+y];
					x1 = x-1;
					y1 = y;
					Direction = 2;
				}
				if (Mas[(x+1)*YMAX+y] < et){
					et = Mas[(x+1)*YMAX + y];
					x1 = x+1;
					y1 = y;
					Direction = 2;
				}
				break;
			case 2:
				if (Mas[(x-1)*YMAX+y] < et){
					et = Mas[(x-1)*YMAX+y];
					x1 = x-1;
					y1 = y;
				}
				if (Mas[(x+1)*YMAX+y] < et){
					et = Mas[(x+1)*YMAX + y];
					x1 = x+1;
					y1 = y;
				}
				if (Mas[x*YMAX+(y+1)] < et){
					et = Mas[x*YMAX+(y+1)];
					x1 = x;
					y1 = y+1;
					Direction = 1;
				}
				if (Mas[x*YMAX+(y-1)] < et){
					et = Mas[x*YMAX+(y-1)];
					x1 = x;
					y1 = y - 1;
					Direction = 1;
				}
				break;
			}
			x = x1;
			y = y1;
			x1 = 0;
			y1 = 0;
			Road.push_back(x);
			Road.push_back(y);
		}
		return 0;
	}

	std::vector<int> Road;
private:
	int Direction;
};

