#pragma once
#include <vector>
#include <algorithm>

class DefK{
private:
	bool DefK::PodModul(const std::vector<double> k){
		std::vector<double> DEFI;

		E = 0.01;

		std::vector<std::vector<double>>Matrix;
		std::vector<double> v;
		int countT = Code[1];
		int countSV = Code.size() - 4 - countT;
		Matrix.resize(N * 3);
		size_t i = 0;
		size_t j;
		for (i; i < N; i++){
			Matrix[i].resize(N * 3 + 1);
			Matrix[i][3 * i] = 1;
			Matrix[i][3 * i + 1] = -k[i];
			Matrix[i][3 * i + 2] = k[i] - 1;
		}
		for (i, j = 4; i < N + countSV; i++, j++){
			Matrix[i].resize(N * 3 + 1);
			Matrix[i][Convert(Code[j] / 100)] = 1;
			Matrix[i][Convert(Code[j] % 100)] = -1;
		}
		Matrix[i].resize(N * 3 + 1);
		Matrix[i][Convert(Code[2] / 100)] = 1;
		Matrix[i++][N * 3] = 1;
		Matrix[i].resize(N * 3 + 1);
		std::vector<double>tmpI;
		double TMP;
		for (size_t j = Code.size() - countT; j < Code.size(); j++){
			Matrix[i][Convert(Code[j] / 100)] = 1;
			TMP = GAUS(Matrix, Convert(Code[3] / 100));
			Matrix[i][Convert(Code[j] / 100)] = 0;
			if (abs(TMP) < 0.000001)
				return false;
			tmpI.push_back(1.0 / TMP);

		}
		if (Comparison(tmpI, PerOtn)){
			I = tmpI;
			return true;
		}
		else
			return false;
	}
	std::vector<size_t> Code;
	std::vector<double> PerOtn;
	inline int Convert(int x){
		return (x%10 - 1)*3 + x/10 - 1;
	}
	size_t N;
	double DefK::GAUS(std::vector<std::vector<double>> Sys, int Element){
		std::vector<std::vector<double>> a = Sys;
		const double EPS = 0.0001;
		int n = a.size();
		for (int i = 0; i<n; ++i) {
			int k = i;
			for (int j = i + 1; j<n; ++j)
			if (abs(a[j][i]) > abs(a[k][i]))
				k = j;
			if (k != i)
				std::swap(a[i], a[k]);
			for (int j = i + 1; j <= n; ++j)
			if (a[i][i] != 0)
				a[i][j] /= a[i][i];
			else
				return 0;
			for (int j = 0; j<n; ++j)
			if (j != i)
			for (int k = i + 1; k <= n; ++k)
				a[j][k] -= a[i][k] * a[j][i];
		}
		std::vector<double> ans;
		for (int i = 0; i<n; ++i)
			ans.push_back(a[i][n]);
		return ans[Element];
	}
	inline bool Comparison(std::vector<double> v1, std::vector<double> v2){
		std::sort(v1.begin(), v1.end());
		std::sort(v2.begin(), v2.end());
		for (size_t i = 0; i < v1.size(); i++)
			if ((v1[i] < v2[i]-E) || (v1[i] > v2[i]+E)) return false;
		return true;
	}
	bool GenNext(int n, std::vector<int>&v1){
		int k = (int)v1.size();
		for (int i = k - 1; i >= 0; --i)
		if (v1[i] < n) {
			++v1[i];
			return true;
		}
		else {
			v1[i] = 0;
		}
		return false;
	}

public:
	DefK(std::vector<size_t> code, std::vector<double>PO, double E1 = 0.1, double k1 = 0.1, double beg1 = -4.5, double end1 = -2.0, double beg2 = 2, double end2 = 4.5){
		beg = beg1;
		end = end2;
		double int_min = end1;
		double int_max = beg2;
		bool in_dia = true;
		if ((beg <= end1) && (end >= beg2)){
			in_dia = false;
		}
		E = E1;
		dk = k1;
		N = code[0];
		Code = code;
		PerOtn = PO;
		Finded = false;
		std::vector<double> k;
		for (size_t i = 0; i < PerOtn.size(); i++)
			k.push_back(beg);
		std::vector<int>GEN;
		for (size_t i = 0; i < k.size(); i++){
			GEN.push_back(0);
		}
		bool flag = true;
		int Len = (end - beg) / dk;
		Fin.clear();
		while (flag){
			for (size_t j = 0; j < k.size(); j++){
				double D = beg + GEN[j] * dk;
				if (!in_dia){
					if ((D > end1) && (D < beg2)){
						D = beg2;
						GEN[j] += (int)4.0 / dk - 1;
					}
				}
				k[j] = D;
			}
			if (PodModul(k)){
				Fin = k;
				Finded = true;
				return;
			}
			flag = GenNext(Len, GEN);
		}
	}
	~DefK(void){}
	bool Finded;
	std::vector<double>Fin;
	double E;
	double dk;
	double beg;
	double end;
	std::vector<double>I;
};




