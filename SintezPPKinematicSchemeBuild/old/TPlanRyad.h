#pragma once
#include<vector>
#include<iostream>

class TPlanRyad
{
public:
	enum type { default, type1, type2, type3, type4 };

	TPlanRyad(type t = default){
		YMAX = 9;
		XMAX = 13;
		Type_of_limit = t;
		const size_t mas_size = 7;
		Mas.resize(mas_size);
		for (size_t i = 0; i < mas_size; i++)
			Mas[i].resize(XMAX*YMAX);
		MakeLimits(Type_of_limit);
	}

	~TPlanRyad(void){}

	void print()
	{
		for ( int i = 0; i < Mas.size(); i++ )
			print( Mas[i] );
	}

	void print( const std::vector<size_t> & mas)
	{
		for ( int i = 0; i < mas.size(); i++ )
		{
			if ( i%YMAX == 0 )
				std::cout << std::endl;
			if ( mas[i] == 0 )
				std::cout << '.';
			else
				std::cout << '#';
			
		}
		std::cout << std::endl;
	}


	void Create(int Num, type t = default){
		int YC = (YMAX - 1) / 2;
		int XC = (XMAX - 1) / 2;
		for (size_t i = 0; i < Mas[0].size(); i++)
			Mas[0][i] = 0;
		switch (t){
		default:
			Mas[0][(XC - 2)*YMAX + YC] = 2000 + Num * 100;			// # # # # # # # # #	
			Mas[0][(XC - 1)*YMAX + YC] = 9999;						// . . . . . . . . .
			Mas[0][(XC)*YMAX + YC - 1] = 3000 + Num * 100;			// . . . . . . . . .
			Mas[0][(XC)*YMAX + YC] = 3000 + Num * 100;				// . . . . . . . . .
			Mas[0][(XC)*YMAX + YC + 1] = 3000 + Num * 100;			// . . . . 2 . . . . 
			Mas[0][(XC + 1)*YMAX + YC] = 9999;						// . . . . 9 . . . . 
			Mas[0][(XC + 2)*YMAX + YC] = 1000 + Num * 100;			// . . . 3 3 3 . . .
			if (t != Type_of_limit)									// . . . . 9 . . . . 
				MakeLimits(t);										// . . . . 1 . . . . 
			break;													// . . . . . . . . .
																	// . . . . . . . . .
																	// . . . . . . . . .
																	//# # # # # # # # #
		case type1:
			Mas[0][(XC + 2)*YMAX + YC - 1] = 1000 + Num * 100;		//# # # # # # # # #
			Mas[0][(XC + 1)*YMAX + YC - 1] = 9999;					// . . . . . . . . .
			Mas[0][XC*YMAX + YC - 1] = 9999;						// . . . . . . . . .
			Mas[0][(XC - 1)*YMAX + YC - 1] = 9999;					// . . . . . . . . .
																	//      3 3 3
			Mas[0][(XC + 2)*YMAX + YC + 1] = 2000 + Num * 100;		//      #   #
			Mas[0][(XC + 1)*YMAX + YC + 1] = 9999;					//      #   #
			Mas[0][XC*YMAX + YC + 1] = 9999;						//      #   #
			Mas[0][(XC - 1)*YMAX + YC + 1] = 9999;					//      1   2
																	// . . . . . . . . .	
			Mas[0][(XC - 2)*YMAX + YC - 1] = 3000 + Num * 100;		// . . . . . . . . .
			Mas[0][(XC - 2)*YMAX + YC] = 3000 + Num * 100;			// . . . . . . . . .
			Mas[0][(XC - 2)*YMAX + YC + 1] = 3000 + Num * 100;		//# # # # # # # # #
			if (t != Type_of_limit)
				MakeLimits(t);
			break;
		case type2:
			Mas[0][(XC - 2)*YMAX + YC - 1] = 1000 + Num * 100;		// # # # # # # # # #
			Mas[0][(XC - 1)*YMAX + YC - 1] = 9999;					// . . . . . . . . .
			Mas[0][XC*YMAX + YC - 1] = 9999;						// . . . . . . . . .
			Mas[0][(XC + 1)*YMAX + YC - 1] = 9999;					// . . . . . . . . .
																	// . . . 1 . 2 . . . 
			Mas[0][(XC - 2)*YMAX + YC + 1] = 2000 + Num * 100;		// . . . # . # . . . 
			Mas[0][(XC - 1)*YMAX + YC + 1] = 9999;					// . . . # . # . . . 
			Mas[0][XC*YMAX + YC + 1] = 9999;						// . . . # . # . . . 
			Mas[0][(XC + 1)*YMAX + YC + 1] = 9999;					// . . . 3 3 3 . . . 
																	// . . . . . . . . .	
			Mas[0][(XC + 2)*YMAX + YC - 1] = 3000 + Num * 100;		// . . . . . . . . .
			Mas[0][(XC + 2)*YMAX + YC] = 3000 + Num * 100;			// . . . . . . . . .
			Mas[0][(XC + 2)*YMAX + YC + 1] = 3000 + Num * 100;		// # # # # # # # # #
			if (t != Type_of_limit)
				MakeLimits(t);
			break;
		case type3:
			Mas[0][(XC + 2)*YMAX + YC - 1] = 2000 + Num * 100;		// # # # # # # # # #
			Mas[0][(XC + 1)*YMAX + YC - 1] = 9999;					// . . . . . . . . .
			Mas[0][XC*YMAX + YC - 1] = 9999;						// . . . . . . . . .
			Mas[0][(XC - 1)*YMAX + YC - 1] = 9999;					// . . . . . . . . .
																	// . . . 3 3 3 . . . 
			Mas[0][(XC + 2)*YMAX + YC + 1] = 1000 + Num * 100;		// . . . # . # . . . 
			Mas[0][(XC + 1)*YMAX + YC + 1] = 9999;					// . . . # . # . . . 
			Mas[0][XC*YMAX + YC + 1] = 9999;						// . . . # . # . . . 
			Mas[0][(XC - 1)*YMAX + YC + 1] = 9999;					// . . . 2 . 1 . . . 
																	// . . . . . . . . .	
			Mas[0][(XC - 2)*YMAX + YC - 1] = 3000 + Num * 100;		// . . . . . . . . .
			Mas[0][(XC - 2)*YMAX + YC] = 3000 + Num * 100;			// . . . . . . . . .
			Mas[0][(XC - 2)*YMAX + YC + 1] = 3000 + Num * 100;		// # # # # # # # # #
			if (t != Type_of_limit)
				MakeLimits(t);
			break;
		case type4:
			Mas[0][(XC - 2)*YMAX + YC - 1] = 2000 + Num * 100;		// # # # # # # # # #
			Mas[0][(XC - 1)*YMAX + YC - 1] = 9999;					// . . . . . . . . .
			Mas[0][XC*YMAX + YC - 1] = 9999;						// . . . . . . . . .
			Mas[0][(XC + 1)*YMAX + YC - 1] = 9999;					// . . . . . . . . .
																	// . . . 2 . 1 . . .
			Mas[0][(XC - 2)*YMAX + YC + 1] = 1000 + Num * 100;		// . . . # . # . . . 
			Mas[0][(XC - 1)*YMAX + YC + 1] = 9999;					// . . . # . # . . . 
			Mas[0][XC*YMAX + YC + 1] = 9999;						// . . . # . # . . . 
			Mas[0][(XC + 1)*YMAX + YC + 1] = 9999;					// . . . 3 3 3 . . . 
																	// . . . . . . . . .
			Mas[0][(XC + 2)*YMAX + YC - 1] = 3000 + Num * 100;		// . . . . . . . . .
			Mas[0][(XC + 2)*YMAX + YC] = 3000 + Num * 100;			// . . . . . . . . .
			Mas[0][(XC + 2)*YMAX + YC + 1] = 3000 + Num * 100;		// # # # # # # # # #
			if (t != Type_of_limit)
				MakeLimits(t);
			break;
		}
		size_t MasSize = Mas.size();
		//for (size_t i = 1; i < MasSize; i++)
		//	Invers(i);
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
		if (!(i < 0) && !(i >(Mas.size() - 1)) && !(j < 0) && !(j >(Mas[i].size() - 1)))
			return Mas[i][j];
		else
			return -1;
	}

	inline std::vector<size_t>getMas(size_t i){
		return Mas[i];
	}

private:
	size_t XMAX;
	size_t YMAX;
	type Type_of_limit;
	std::vector<std::vector<size_t>>Mas;

	void MakeLimits(type t){
		Type_of_limit = t;
		size_t YC = (YMAX - 1) / 2;
		size_t XC = (XMAX - 1) / 2;
		for (size_t i = 1; i < Mas.size(); i++)
		for (size_t j = 0; j < Mas[i].size(); j++)
			Mas[i][j] = 0;
		switch (Type_of_limit){
		default:
			for (size_t i = 1; i < XC - 1; i++){
				Mas[1][i*YMAX - 1 + YC] = 9999;
				Mas[2][i*YMAX + 1 + YC] = 9999;
			}
			for (size_t i = 2; i < XC - 1; i++){
				Mas[2][i*YMAX + YC - 1] = 9999;
			}
			for (size_t i = XC - 1; i < XC + 2; i++){
				if (i != XC){
					Mas[3][i*YMAX - 1 + YC] = 9999;
					Mas[4][i*YMAX + 1 + YC] = 9999;
				}
				Mas[3][i*YMAX - 2 + YC] = 9999;
				Mas[4][i*YMAX + 2 + YC] = 9999;
			}
			for (size_t i = XC + 2; i < XMAX; i++){
				Mas[5][i*YMAX + 1 + YC] = 9999;
				Mas[6][i*YMAX - 1 + YC] = 9999;
			}
			for (size_t i = 2; i < XC - 2; i++){
				Mas[6][i*YMAX + YC] = 9999;
			}
			break;
		case type1:
			for (size_t i = XC + 2; i < XMAX; i++){
				Mas[1][i*YMAX + YC] = 9999;
				Mas[2][i*YMAX + YC + 2] = 9999;
				Mas[5][i*YMAX + YC] = 9999;
				Mas[6][i*YMAX + YC - 2] = 9999;
			}
			for (size_t i = 1; i < XC - 2; i++){
				Mas[3][i*YMAX - 1 + YC] = 9999;
				Mas[4][i*YMAX + 1 + YC] = 9999;
			}
			for (size_t i = 2; i < XC - 1; i++){
				Mas[4][i*YMAX + YC - 2] = 9999;
			}
			Mas[3][(XC - 2)*YMAX - 2 + YC] = 9999;
			Mas[3][(XC - 3)*YMAX - 2 + YC] = 9999;
			Mas[4][(XC - 2)*YMAX + 2 + YC] = 9999;
			Mas[4][(XC - 3)*YMAX + 2 + YC] = 9999;
			break;
		case type2:
			for (size_t i = 1; i < XC - 1; i++){
				Mas[1][i*YMAX + YC] = 9999;
				Mas[2][i*YMAX + YC + 2] = 9999;
				Mas[5][i*YMAX + YC] = 9999;
				Mas[6][i*YMAX + YC - 2] = 9999;
			}
			for (size_t i = 2; i < XC - 1; i++){
				Mas[2][i*YMAX + YC] = 9999;
			}
			for (size_t i = 2; i < XC - 1; i++){
				Mas[5][i*YMAX + YC - 2] = 9999;
			}
			for (size_t i = XC + 2; i < XMAX; i++){
				Mas[3][i*YMAX - 1 + YC] = 9999;
				Mas[4][i*YMAX + 1 + YC] = 9999;
			}
			Mas[3][(XC + 2)*YMAX - 2 + YC] = 9999;
			Mas[3][(XC + 3)*YMAX - 2 + YC] = 9999;
			Mas[4][(XC + 2)*YMAX + 2 + YC] = 9999;
			Mas[4][(XC + 3)*YMAX + 2 + YC] = 9999;
			break;
		case type3:
			for (size_t i = XC + 2; i < XMAX; i++){
				Mas[1][i*YMAX + YC - 2] = 9999;
				Mas[2][i*YMAX + YC] = 9999;
				Mas[5][i*YMAX + YC + 2] = 9999;
				Mas[6][i*YMAX + YC] = 9999;
			}
			for (size_t i = 1; i < XC - 1; i++){
				Mas[3][i*YMAX - 1 + YC] = 9999;
				Mas[4][i*YMAX + 1 + YC] = 9999;
			}
			for (size_t i = 2; i < XC - 1; i++){
				Mas[4][i*YMAX + YC - 2] = 9999;
			}
			Mas[3][(XC - 2)*YMAX - 2 + YC] = 9999;
			Mas[3][(XC - 3)*YMAX - 2 + YC] = 9999;
			Mas[4][(XC - 2)*YMAX + 2 + YC] = 9999;
			Mas[4][(XC - 3)*YMAX + 2 + YC] = 9999;
			break;
		case type4:
			for (size_t i = 1; i < XC - 1; i++){
				Mas[1][i*YMAX + YC - 2] = 9999;
				Mas[2][i*YMAX + YC] = 9999;
				Mas[5][i*YMAX + YC + 2] = 9999;
				Mas[6][i*YMAX + YC] = 9999;
			}
			for (size_t i = 2; i < XC - 1; i++){
				Mas[2][i*YMAX + YC - 2] = 9999;
			}
			for (size_t i = 2; i < XC - 1; i++){
				Mas[5][i*YMAX + YC] = 9999;
			}
			for (size_t i = XC + 2; i < XMAX; i++){
				Mas[3][i*YMAX - 1 + YC] = 9999;
				Mas[4][i*YMAX + 1 + YC] = 9999;
			}
			Mas[3][(XC + 2)*YMAX - 2 + YC] = 9999;
			Mas[3][(XC + 3)*YMAX - 2 + YC] = 9999;
			Mas[4][(XC + 2)*YMAX + 2 + YC] = 9999;
			Mas[4][(XC + 3)*YMAX + 2 + YC] = 9999;
			break;
		}
	}
};

