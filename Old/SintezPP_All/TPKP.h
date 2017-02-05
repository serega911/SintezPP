#pragma once
#include <vector>
#include <iomanip>
#include <fstream>
#include "DefW.h"
#include "DefZ.h"
#include "DefK.h"
#include "DefM.h"
#include "DefN.h"
#include "DefMn.h"

class TPKP
{
public:
	char report[20];
	bool Finded;
	std::vector<size_t> Code;
	std::vector<double> i;
	std::vector<double> k;
	std::vector<std::vector<double>> w;
	std::vector<std::vector<double>> w_Ext;
	std::vector<std::vector<double>> M;
	std::vector<std::vector<char>> N;
	std::vector<std::vector<int>> z;
	std::vector<std::vector<double>> Mn;
	double E;
	double dk;
	double beg_1;
	double end_1;
	double beg_2;
	double end_2;
	double K1;
	double K2;
	double K3;
	double K4;
	double K5_1;
	double K5_2;
	double K6;
	double K7;
	double K8;
	double K9;
	double K10;
	double Kint;
	std::vector<double> K;
	int krit;

	TPKP(std::vector<size_t> Code1, std::vector<double> i1, double E1, double dk1, double beg1, double end1, double beg2, double end2, int frict = 0){
		krit = 1;
		E = E1;
		dk = dk1;
		beg_1 = beg1;
		end_1 = end1;
		beg_2 = beg2;
		end_2 = end2;
		Code = Code1;
		int Frict;
		sprintf_s(report, "");
		if (frict == 0)
			Frict = Code[2] / 100 * 100 + Code[3] / 100;
		else
			Frict = frict;
		i = i1;
		DefK DK(Code, i, E, dk, beg_1, end_1, beg_2, end_2);
		if (DK.Finded){
			Finded = true;
			k = DK.Fin;
			DefW DW(Code, k, Frict);
			w = DW.Result;
			w_Ext = DW.Result_Ext;
			DefZ DZ(k);
			z = DZ.Z;
			if (z.size() == 0){
				sprintf_s(report, "DZ: Failed.");
				Finded = false;
				return;
			}
			DefM DM(Code, Frict, k);
			M = DM.M;
			DefN DN(M, w_Ext, Code);
			N = DN.N;
			DefMn DMn(Code, Frict, k, N);
			Mn = DMn.Mn;
			KriteriiPKP();
		}
		else{
			Finded = false;
			sprintf_s(report, "DK: Failed.");
		}
	}

	int WriteToFile(std::fstream &File){
		for (size_t i = 0; i < Code.size(); i++)
			File << Code[i] << ' ';
		File << '\n';
		for (size_t i = 0; i < k.size(); i++)
			File << 'k' << (i+1) << '	';
		File << '\n';
		for (size_t i = 0; i < k.size(); i++)
			File << k[i] << '	';
		File << '\n';
		File << "z1" << '	' << "z2" << '	' << "z4" << '\n';
		for (size_t i = 0; i < z.size(); i++){
			for (size_t j = 0; j < z[i].size(); j++)
				File << z[i][j] << '	';
			File << '\n';
		}
		File << '\n';
		for (size_t i = 0; i < k.size(); i++)
			File << "w1" << (i + 1) << "	w2" << (i + 1) << "	w3" << (i + 1) << '	';
		for (size_t i = 0; i < k.size(); i++)
			File << "w4" << (i + 1) << '	';
		for (size_t i = 0; i < k.size(); i++)
			File << "T" << (i + 1) << '	';
		File << "F1	F2	In	Out\n";
		for (size_t i = 0; i < w_Ext.size(); i++){
			for (size_t j = 0; j < w_Ext[i].size(); j++)
				File << w_Ext[i][j] << '	';
			File << '\n';
		}
		File << "\n";
		File << "\n";
		File.flush();
		return 0;
	}

	~TPKP(void){
	}

	bool operator < (TPKP const & x1){
		if (x1.K[krit] < this->K[krit])
			return true;
		else 
			return false;
	}

	void KriteriiPKP(void){
		//1
		double N_max = 0;
		for (size_t i = 0; i < w.size(); i++){
			if (Mn[i][Mn[i].size()-1] < 0){
				for (size_t j = 0; j < Code[0]*3; j++){
					if (abs(Mn[i][j] * w_Ext[i][j]) > N_max)
						N_max = abs(Mn[i][j] * w_Ext[i][j]);
				}
			}
		}
		K1 = N_max/(float)abs(Mn[0][Mn[0].size()-2]*w_Ext[0][w_Ext[0].size()-2]);
		//2
		N_max = 0;
		for (size_t i = 0; i < w.size(); i++){
			if (Mn[i][Mn[i].size()-1] > 0){
				for (size_t j = 0; j < Code[0] * 3; j++){
					if (abs(Mn[i][j] * w_Ext[i][j]) > N_max)
						N_max = abs(Mn[i][j] * w_Ext[i][j]);
				}
			}
		}
		K2 = N_max/(float)abs(Mn[0][Mn[0].size()-2]*w_Ext[0][w_Ext[0].size()-2]);
		//3
		double Mf_max = 0;
		for (size_t i = 0; i < Mn.size(); i++){
			for (size_t j = Code[0] * 3 + Code[1]; j < Mn[0].size() - 2; j++){
				if (abs(Mn[i][j]) > Mf_max)
					Mf_max = abs(Mn[i][j]);
			}
		}
		K3 = Mf_max/abs(Mn[0][Mn[0].size()-2]);
		//4
		double Mt_max = 0;
		for (size_t i = 0; i < Mn.size(); i++){
			for (size_t j = Code[0] * 3; j < Code[0] * 3 + Code[1]; j++){
				if (abs(Mn[i][j]) > Mt_max)
					Mt_max = abs(Mn[i][j]);
			}
		}
		K4 = Mt_max/abs(Mn[0][Mn[0].size()-2]);
		//5_1
		double w_max = 0;
		for (size_t i = 0; i < w.size(); i++){
			for (size_t j = w[i].size() - Code[0]; j < w[i].size(); j++){
				if ((Mn[i][3*( j-w[i].size()-Code[0]+1)-1]+Mn[i][3*( j-w[i].size()-Code[0]+1)-2]+Mn[i][3*( j-w[i].size()-Code[0]+1)-3]) != 0)
					if (abs(w[i][j]) > w_max)
						w_max = abs(w[i][j]);
			}
		}
		K5_1 = w_max/abs(w_Ext[0][w_Ext[0].size()-2]);
		//5_2
		w_max = 0;
		for (size_t i = 0; i < w.size(); i++){
			for (size_t j = w[i].size() - Code[0]; j < w[i].size(); j++){
				if ((Mn[i][3*( j-w[i].size()-Code[0]+1)-1]+Mn[i][3*(j-w[i].size()-Code[0]+1)-2]+Mn[i][3*(j-w[i].size()-Code[0]+1)-3]) == 0)
					if (abs(w[i][j]) > w_max)
						w_max = abs(w[i][j]);
			}
		}
		K5_2 = w_max/abs(w_Ext[0][w_Ext[0].size()-2]);
		//6
		w_max = 0;
		for (size_t i = 0; i < w_Ext.size(); i++){
			for (size_t j = Code[0] * 3; j < w_Ext[i].size() - 2; j++){
				if ((Mn[i][j] == 0) && (abs(w_Ext[i][j]) > w_max))
					w_max = abs(w_Ext[i][j]);
			}
		}
		
		K6 = w_max/abs(w_Ext[0][w_Ext[0].size()-2]);
		K.push_back(K1);
		K.push_back(K2);
		K.push_back(K3);
		K.push_back(K4);
		K.push_back(K5_1);
		K.push_back(K5_2);
		K.push_back(K6);
		//Kint
		Kint = 0;
		for(size_t i = 0; i < K.size(); i++)
			Kint += K[i];
		K.push_back(Kint);
		
		return;
	}
};