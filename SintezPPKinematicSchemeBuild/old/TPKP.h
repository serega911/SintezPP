#pragma once
#include <vector>
#include <iomanip>
#include <fstream>


class TPKP
{
public:
	char report[20];
	bool Finded;
	std::vector<size_t> Code;
	std::vector<std::vector<size_t>> Chains;
	std::vector<double> i;
	std::vector<double> k;
	std::vector<size_t> VectLimits;
	double E;
	double dk;
	double beg_1;
	double end_1;
	double beg_2;
	double end_2;
	int Frict;
	std::vector<double> K;
	int krit;

	TPKP(std::vector<size_t> Code1, const std::vector<std::vector<size_t>> &Chains1, std::vector<double> i1, double E1, double dk1, double beg1, double end1, double beg2, double end2, int frict = 0){
		krit = 1;
		E = E1;
		dk = dk1;
		beg_1 = beg1;
		end_1 = end1;
		beg_2 = beg2;
		end_2 = end2;
		Code = Code1;
		Chains = Chains1;
		if (frict == 0)
			Frict = Code[2] / 100 * 100 + Code[3] / 100;
		else
			Frict = frict;
		i = i1;
	}

	void SetVectLimits(std::vector<size_t> v){
		VectLimits = v;
		return;
	}

	~TPKP(void){
	}
};