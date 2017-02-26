#pragma once
#include <direct.h>
#include<string.h>
#include <vector>
#include <ctime>
#include <iomanip>
#include <fstream>
#include"TPKP.h"
#include"TMake.h"
#include"TPKP_Container.h"

class TGenerate
{
public:
	
	TGenerate(int countp, int w, const std::vector<double>&v){
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		char* form = "%d_%B_%Y_%H_%M_%S";
		char dir[80];
		strftime(dir, 80, form, timeinfo);
		mkdir("SintezPP_All_Logs");
		char as[80] = "SintezPP_All_Logs\\";
		strcat(as, dir);
		mkdir(as);
		char tmp[80];
		strcat(strcpy(tmp, as), "\\Done.txt");
		Done.open(tmp, std::ios::out);
		strcat(strcpy(tmp, as), "\\FailedMake.txt");
		MakeFailed.open(tmp, std::ios::out);
		strcat(strcpy(tmp, as), "\\FailedPKP.txt");
		PKPFailed.open(tmp, std::ios::out);
		strcat(strcpy(tmp, as), "\\FailedCreateT.txt");
		CreateTFailed.open(tmp, std::ios::out);
		strcat(strcpy(tmp, as), "\\FailedRepetition.txt");
		RepetitionFailed.open(tmp, std::ios::out);
		strcat(strcpy(tmp, as), "\\DoneXLS.xls");
		DoneXLS.open(tmp, std::ios::out);
		char buffer[80];
		char* format = "%A %B %d, %Y %H:%M:%S";
		strftime(buffer, 80, format, timeinfo);
		Done << "Process started: " << buffer << "\n";
		CountP = countp;
		W = w;
		VectI = v;
		switch (W){
			case 2:
				F = 1;
				CountT = CountP - 1;
				N = CountT;
				CountSV = 2*N - W;
				break;
			case 3:
				F = 2;
				if (CountP == 3) CountT = 1;
				if ((CountP > 3) && (CountP <= 6)) CountT = 2;
				if ((CountP > 6) && (CountP <= 10)) CountT = 3;
				if ((CountP > 10) && (CountP <= 12)) CountT = 4;
				N = CountT + 1;
				CountSV = 2*N - W;
				break;
		}
		std::vector<size_t>V1;
		bool b = false;
		V1.push_back(1);
		V1.push_back(2);
		while (!b){
			if (Convert(V1[0])%10 != Convert(V1[1])%10)
				AllLinks.push_back(Convert(V1[0])*100 + Convert(V1[1]));
			b = GenNext(3*N,V1);
		}
	}

	~TGenerate(void){
		char buffer[80];
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		char* format = "%A, %B %d, %Y %H:%M:%S";
		strftime(buffer, 80, format, timeinfo);
		Done << "Process finished: " << buffer << "\n";
		Done.close();
		MakeFailed.close();
		PKPFailed.close();
		CreateTFailed.close();
		RepetitionFailed.close();
	}

	int Run(double E, double k, double beg1, double end1, double beg2, double end2){
		Done << "E = " << E << ";	" << "dK = " << k << ";	" << "K = [" << beg1 << ".." << end1 << "][" << beg2 << ".." << end2 << "]\n";
		Done << "I = ";
		for (size_t i = 0; i < VectI.size(); i++)
			Done << VectI[i] << "	";
		Done << "\n";
		int ret = 0;
		for (int i = 0; i < 3*N; i++){
			for (int j = 0; j < 3*N; j++){
				ret += Run(i+1,j+1, E, k, beg1, end1, beg2, end2);
			}
		}
		return ret;
	}

	int Run(int i, int j, double E, double k, double beg1, double end1, double beg2, double end2){
		if ((i > 3*N) || (j > 3*N) || (i == j)) return 1;
		bool bSV = false;
		CombiSV.clear();
		for (int m = 0; m < CountSV; m++)
			CombiSV.push_back(m+1);
		while (!bSV){
			Input.clear();
			Input.push_back(N);
			Input.push_back(CountT);
			Input.push_back(Convert(i)*100 + 44);
			Input.push_back(Convert(j)*100 + 55);
			for (size_t m = 0; m < CombiSV.size(); m++)
				Input.push_back(AllLinks[CombiSV[m]-1]);
			if (CreateT(Input) == CountT){
				TMake Make;
				if (!Make.Run(Input) && (MasPKP_all.InList(Input))){
					TPKP pkp(Input, VectI, E, k, beg1, end1, beg2, end2);
					if (pkp.Finded){
						if (MasPKP_all.push_back(pkp) == true){
							WriteToFile(Done, Input, "Done");
							pkp.WriteToFile(DoneXLS);
							
						}
						else
							WriteToFile(RepetitionFailed, Input, "Repetition: Failed");
					}
					else
						WriteToFile(PKPFailed, Input, pkp.report);
				} else
					WriteToFile(MakeFailed, Input, "Make: Failed.");
			}
			else{
				WriteToFile(CreateTFailed, Input, "CreateT: Failed.");
			}
			bSV = GenNext(AllLinks.size(),CombiSV);
		}
		Done.flush();
		MakeFailed.flush();
		PKPFailed.flush();
		CreateTFailed.flush();
		RepetitionFailed.flush();
		DoneXLS.flush();
		return 0;
	}

	bool GenNext(size_t n, std::vector<size_t>&v1){
		if (v1.size() == 0)  return 1;
		std::vector<size_t>tmp;
		size_t m = v1.size();
		tmp = v1;
		int x;
		if (tmp[m-1] < n)
			tmp[m-1]++;
		else{ 
			if (m == 1) return 1;
			for (size_t i = 1; i < m; i++)
				if (tmp[i] > i+n-m){
					x = i;
					break;
				}
			tmp[x-1]++;
			for (size_t i = x; i < m; i++)
				tmp[i] = tmp[i-1] + 1;
		}
		if (tmp[0] > n-m+1){
			return 1;
		}	
		v1 = tmp;
		return 0;
	}

	inline int Convert(int x){
		return ((x-1)%3+1)*10 + (x-1)/3 + 1;
	}

	int N;											//количество планетарных рядов

	PKP_Container MasPKP_all;

private:

	int TGenerate::CreateT(std::vector<size_t> &v){
		std::vector<size_t>Elements;
		std::vector<size_t>Links;
		std::vector<size_t>TMP;
		std::vector<std::vector<size_t>>Chains;
		int count = 0;
		for (size_t i = 4; i < v.size(); i++)
			Links.push_back(v[i]);
		//поиск элементов, свободных от входа и выхода
		for (size_t i = 1; i <= v[0] * 3; i++)
			if ((Convert(i) != v[2]/100) && (Convert(i) != v[3]/100))
				Elements.push_back(Convert(i));
			else 
				Elements.push_back(0);
	
		if (v.size() == 4){
			for (size_t i = 0; i <Elements.size(); i++){
				if (Elements[i] != 0){
					v.push_back(Elements[i]*100 + 66);
					count++;
				}
			}
			return count;
		}
		//поиск цепочек связей
		int b = 0;
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
	
		for (size_t i = 0; i < Chains.size(); i++)
			for (size_t j = 0; j < Chains[i].size(); j++)
				for (size_t k = 0; k < Chains[i].size(); k++)
					if ((Chains[i][j]%10 == Chains[i][k]%10) && (Chains[i][j] != Chains[i][k]))
						count++;

		//удаление цепочек, содержащих вход и выход
		b = 0;
		for (size_t i = 0; i < Chains.size(); i++){
			for (size_t j = 0; j < Chains[i].size(); j++)
				if ((Chains[i][j] == v[2]/100) || (Chains[i][j] == v[3]/100) || (Chains[i][j] == 0))
					b = 1;
			if (b != 1){
				v.push_back(Chains[i][0]*100 + 66);
				count++;
			}
			b = 0;
		}
		//поиск свободных звеньев
		for (size_t i = 0; i <Elements.size() ; i++){
			for (size_t j = 0; j < Links.size(); j++)
				if ((Elements[i] == Links[j]/100) || (Elements[i] == Links[j]%100))
					Elements[i] = 0;
			if (Elements[i] != 0){
				v.push_back(Elements[i]*100 + 66);
				count++;
			}
		}
		return count;
	}

	void WriteToFile(std::fstream &File, std::vector<size_t> Code, const char* str){
		for (size_t m = 0; m < Code.size(); m++)
			File << Code[m] << ' ';
		File << str << '\n';
		return;
	}

	std::fstream Done;
	std::fstream MakeFailed;
	std::fstream PKPFailed;
	std::fstream CreateTFailed;
	std::fstream RepetitionFailed;

	std::fstream DoneXLS;

	int F;			//количество фрикционов
	int CountT;		//количество тормозов
	int CountP;		//количество передач
	int CountSV;	//количество необходимых связей
	int W;			//количество степеней свободы в КП
	std::vector<double> VectI;		//вектор передаточных отношений
	std::vector<size_t>AllLinks;		//Вектор всех возможных связей
	std::vector<size_t>Input;			//Вектор кода
	std::vector<size_t>CombiSV;		//Вектор комбинаций связей
};












