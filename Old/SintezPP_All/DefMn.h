#pragma once
#include <vector>
class DefMn
{
public:
	std::vector<std::vector<double>>Mn;

	DefMn(const std::vector<size_t>Code, int Friction, std::vector<double>K, std::vector<std::vector<char>> N1, int Min = 1000){
		std::vector<std::vector<double>>Matrix;
		int N = Code[0];
		size_t countT = Code[1];
		size_t countSV = Code.size() - 4 - countT;
		size_t L = N * 3 + countT + 4;
		Matrix.resize(L);
		double KPDvn = 0.99;
		double KPDnar = 0.98;
		std::vector<double>TMP;
		for (size_t k = 0; k < countT; k++){
			size_t i = 0;
			for (size_t j = 0; j < K.size(); i = i+2, j++){
				Matrix[i].clear();
				Matrix[i].resize(L+1);
				Matrix[i+1].clear();
				Matrix[i+1].resize(L+1);
				int temp1;
				if (N1[k][3*j] == '0')
					temp1 = 0;
				if (N1[k][3*j] == '-')
					temp1 = 1;;
				if (N1[k][3*j] == '+')
					temp1 = -1;
				int temp2;
				if (N1[k][3*j+1] == '0')
					temp2 = 0;
				if (N1[k][3*j+1] == '-')
					temp2 = 1;;
				if (N1[k][3*j+1] == '+')
					temp2 = -1;
				Matrix[i][3*j] = pow(KPDnar,temp1);
				Matrix[i][3*j+1] = pow(KPDvn,temp2);
				Matrix[i][3*j+2] = 1;
				Matrix[i+1][3*j] = K[j]*pow(KPDnar,temp1);
				Matrix[i+1][3*j+1] = 1*pow(KPDvn,temp2);
			}
			std::vector<std::vector<size_t>>C = SearchChain(Code, Friction);
			for (size_t j = 0; j < C.size(); j++, i++){
				Matrix[i].clear();
				Matrix[i].resize(L+1);
				for (size_t k1 = 0; k1 < C[j].size(); k1++){
					if (C[j][k1] < 40)
						Matrix[i][Convert(C[j][k1])] = 1;
					else if (C[j][k1]/11 == 4)
						Matrix[i][L-2] = 1;
					else if (C[j][k1]/11 == 5)
						Matrix[i][L-1] = 1;
					else if (C[j][k1]/11 >= 6)
						Matrix[i][L-4 + C[j][k1]/11 - 6 - countT] = 1;
					else if (C[j][k1] == 41)
						Matrix[i][L-4] = 1;
					else if (C[j][k1] == 42)
						Matrix[i][L-3] = 1;
				}
			}
			for (size_t j = 0; j < countT; j++){
				if (j != k){
					Matrix[i].clear();
					Matrix[i].resize(L+1);
					Matrix[i][L-4 + j - countT] = 1;
					i++;
				}	
			}	
			Matrix[i].clear();
			Matrix[i].resize(L+1);
			Matrix[i][L-4] = 1;
			i++;
			Matrix[i].clear();
			Matrix[i].resize(L+1);
			Matrix[i][L-3] = 1;
			i++;
			Matrix[i].clear();
			Matrix[i].resize(L+1);
			Matrix[i][L-2] = 1;
			Matrix[i][L] = 1000;
			TMP = GAUS(Matrix);
			Mn.push_back(TMP);	
		}
		int k = countT;
		size_t i = 0;
		for (size_t j = 0; j < K.size(); i = i+2, j++){
			Matrix[i].clear();
			Matrix[i].resize(L+1);
			Matrix[i+1].clear();
			Matrix[i+1].resize(L+1);
			int temp1;
			if (N1[k][3*j] == '0')
				temp1 = 0;
			if (N1[k][3*j] == '-')
				temp1 = 1;;
			if (N1[k][3*j] == '+')
				temp1 = -1;
			int temp2;
			if (N1[k][3*j+1] == '0')
				temp2 = 0;
			if (N1[k][3*j+1] == '-')
				temp2 = 1;;
			if (N1[k][3*j+1] == '+')
				temp2 = -1;
			Matrix[i][3*j] = pow(KPDnar,temp1);
			Matrix[i][3*j+1] = pow(KPDvn,temp2);
			Matrix[i][3*j+2] = 1;
			Matrix[i+1][3*j] = K[j]*pow(KPDnar,temp1);
			Matrix[i+1][3*j+1] = 1*pow(KPDvn,temp2);
		}
		std::vector<std::vector<size_t>>C = SearchChain(Code, Friction);
		for (size_t j = 0; j < C.size(); j++, i++){
			Matrix[i].clear();
			Matrix[i].resize(L+1);
			for (size_t k1 = 0; k1 < C[j].size(); k1++){
				if (C[j][k1] < 40)
					Matrix[i][Convert(C[j][k1])] = 1;
				else if (C[j][k1]/11 == 4)
					Matrix[i][L-2] = 1;
				else if (C[j][k1]/11 == 5)
					Matrix[i][L-1] = 1;
				else if (C[j][k1]/11 >= 6)
					Matrix[i][L-4 + C[j][k1]/11 - 6 - countT] = 1;
				else if (C[j][k1] == 41)
					Matrix[i][L-4] = 1;
				else if (C[j][k1] == 42)
					Matrix[i][L-3] = 1;
			}
		}
		for (size_t j = 0; j < countT; j++){
			Matrix[i].clear();
			Matrix[i].resize(L+1);
			Matrix[i][L-4 + j - countT] = 1;
			i++;	
		}	
		Matrix[i].clear();
		Matrix[i].resize(L+1);
		Matrix[i][L-4] = 1;
		Matrix[i][L-3] = 1;
		i++;
		Matrix[i].clear();
		Matrix[i].resize(L+1);
		Matrix[i][L-2] = 1;
		Matrix[i][L] = 1000;
		TMP = GAUS(Matrix);
		Mn.push_back(TMP);
		return;
	}

	inline int Convert(int x){
			return (x%10 - 1)*3 + x/10 - 1;
		}

	std::vector<std::vector<size_t>> SearchChain(const std::vector<size_t> Code, int Frict){
		int b = 0;
		std::vector<std::vector<size_t>>Chains;
		std::vector<size_t>Links;
		int count = 0;
		for (size_t i = 2; i < Code.size(); i++){
			int temp = Code[i];
			if (temp%100 == 66){
				temp = temp+count*11;
				count++;
			}
			Links.push_back(temp);

		}
		std::vector<size_t>TMP;
		for (size_t i = 0; i < Links.size(); i++){
			TMP.push_back(Links[i]/100);
			TMP.push_back(Links[i]%100);
			Chains.push_back(TMP);
			TMP.clear();
		}
		for (size_t i = 0; i < Chains.size()-1; i++){
			for (size_t j = i+1; j < Chains.size(); j++){
				for (size_t k = 0; k < Chains[i].size(); k++){
					for (size_t l = 0; l < Chains[j].size(); l++){
						if (Chains[i][k] == Chains[j][l])
							b = Chains[i][k];
					}
				}
				if (b != 0){
					for (size_t k = 0; k < Chains[i].size(); k++)
						if (Chains[i][k] != b)
							Chains[j].push_back(Chains[i][k]);
					Chains[i].clear();
					Chains[i].push_back(0);
					b = 0;
				}
			}
		}
		for (int i = Chains.size()-1; i > -1; i--)
			if (Chains[i][0] == 0)
				Chains.erase(Chains.begin()+i);
			else
				for (size_t j = 0; j < Chains[i].size(); j++){
					if (Chains[i][j] == Frict/100)
						Chains[i].push_back(41);			//Mf1
					if (Chains[i][j] == Frict%100)
						Chains[i].push_back(42);			//Mf2
				}

		return Chains;
	}

	std::vector<double> GAUS(std::vector<std::vector<double>> Sys){
		std::vector<std::vector<double>> a = Sys;
		const double EPS = 1E-9;
		int n = a.size();
		for (int i=0; i<n; ++i) {
			int k = i;
			for (int j=i+1; j<n; ++j)
				if (abs (a[j][i]) > abs (a[k][i]))
					k = j;
			if (k!=i)
				std::swap (a[i], a[k]);
			for (int j=i+1; j<=n; ++j)
				a[i][j] /= a[i][i];
			for (int j=0; j<n; ++j)
				if (j != i)
					for (int k=i+1; k<=n; ++k)
						a[j][k] -= a[i][k] * a[j][i];
		}
		std::vector<double> ans;
		for (int i=0; i<n; ++i)
			ans.push_back(a[i][n]);
		return ans;
	}

	~DefMn(void)
	{
	}
};

