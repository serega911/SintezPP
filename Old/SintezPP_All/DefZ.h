#pragma once
#include <vector>
#include <cmath>
class DefZ
{
public:
	std::vector<std::vector<int>> Z;
	DefZ( const std::vector<double> K){
		std::vector<double> k(K);
		for (size_t i = 0; i < k.size(); i++){
				Z.push_back(Def(k[i]));
		}
		
		for (size_t i = 0; i < Z.size(); i++){
			if (Z[i].size() != 3)
				Z.clear();
		}
		return;
	}

	~DefZ(void){
	}
private:
	std::vector<int> Def(double k){
		static int Zmin = 14;
		static int Zmax = 100;
		double M_PI = 3.14159;
		size_t Nsat = (size_t)(double)M_PI / (double)(asin((abs(k) - 1 + (8 / (double)Zmin)) / (abs(k) + 1)));//округляем в меньшую сторону - отбрасываем дробныю часть
		double Gamma = 14*(abs(k) - 1)/Nsat;
		double z1 = 0.123;
		double z2 = 0.123;
		double z4 = 0.123;
		int tmp;
		for (size_t i = Gamma; ((z1 - (int)z1 != 0) || (z2 - (int)z2 != 0) || (z4 - (int)z4 != 0) || ((int)z1 < Zmin) || ((int)z2 < Zmin) || ((int)z4 < Zmin)); i++){
			z1 = Nsat*i/(abs(k)+1);
			z2 = z1 * abs(k);
			z4 = (z2-z1)/2;
			tmp = i;
			if (z1 > Zmax){
				std::vector<int> ret;
				ret.push_back(0);
				return ret;
			}
		}
		std::vector<int> ret;
		ret.push_back(z1);
		ret.push_back(z2);
		ret.push_back(z4);
		return ret;
	}
};

