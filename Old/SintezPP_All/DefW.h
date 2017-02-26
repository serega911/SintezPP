#pragma once
#include <vector>
class DefW
{
public:
	std::vector<std::vector<double>> Result;
	std::vector<std::vector<double>> Result_Ext;
	DefW(std::vector<size_t> Code, std::vector<double>k, int Frict){
		std::vector<std::vector<double>>Matrix;
		std::vector<double> v;
		int countT = Code[1];
		int countSV = Code.size() - 4 - countT;
		size_t N = k.size();
		Matrix.resize(N*3);
		size_t i = 0;
		size_t j;
		for (i; i < N; i++){
			Matrix[i].resize(N*3+1);
			Matrix[i][3*i] = 1;
			Matrix[i][3*i+1] = -k[i];
			Matrix[i][3*i+2] = k[i]-1;
		}
		for (i, j = 4; i < N + countSV; i++, j++){
			Matrix[i].resize(N*3+1);
			Matrix[i][Convert(Code[j]/100)] = 1;
			Matrix[i][Convert(Code[j]%100)] = -1;
		}
		Matrix[i].resize(N*3+1);
		Matrix[i][Convert(Code[2]/100)] = 1;
		Matrix[i++][N*3] = 100;
		Matrix[i].resize(N*3+1);
		std::vector<double>tmpI;
		std::vector<double>tmpI_Ext;
		for (size_t j = Code.size() - countT; j < Code.size(); j++){
			Matrix[i][Convert(Code[j]/100)] = 1;
			tmpI = GAUS(Matrix);
			tmpI_Ext = tmpI;
			//угл скорости сателлитов
			for (size_t l = 0; l < N; l++){
				tmpI.push_back(2.0*(tmpI[3 * l] - tmpI[3 * l + 2]) / (k[l] + 1));
				tmpI_Ext.push_back(2.0*(tmpI_Ext[3 * l] - tmpI_Ext[3 * l + 2]) / (k[l] + 1));
			}
			Result.push_back(tmpI);
			//угл скорости тормозов
			for (size_t l = Code.size() - countT; l < Code.size(); l++){
				tmpI_Ext.push_back(tmpI_Ext[Convert(Code[l]/100)]);
			}
			//угл скорости фрикционов
			tmpI_Ext.push_back(tmpI_Ext[Convert(Frict / 100)]);
			tmpI_Ext.push_back(tmpI_Ext[Convert(Frict % 100)]);
			//угл скорости входа и выхода
			tmpI_Ext.push_back(tmpI_Ext[Convert(Code[2] / 100)]);
			tmpI_Ext.push_back(tmpI_Ext[Convert(Code[3] / 100)]);
			Result_Ext.push_back(tmpI_Ext);

			Matrix[i][Convert(Code[j]/100)] = 0;
		}
		tmpI_Ext.clear();
		for (size_t i = 0; i < Result_Ext[0].size(); i++)
			tmpI_Ext.push_back(100);
		Result_Ext.push_back(tmpI_Ext);
	}

	inline int Convert(int x){
		return (x%10 - 1)*3 + x/10 - 1;
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


	~DefW(void)
	{
	}
};

