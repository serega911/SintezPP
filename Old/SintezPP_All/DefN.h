#pragma once
#include <vector>
class DefN
{
public:
	std::vector<std::vector<char>> N;

	DefN(std::vector<std::vector<double>> M, std::vector<std::vector<double>> w, std::vector<size_t> Code){
		std::vector<char> TMP;
		if ((M.size() != w.size()) && (M[0].size() != w[0].size()))
			return;
		for (size_t k = 0; k < w.size(); k++){
			TMP.clear();
			for (size_t i = 0; i < w[k].size(); i++){
				int M1 = M[k][i];
				int w1 = w[k][i];
				if ((M1*w1) == 0){
					if (M1 == 0) 
						TMP.push_back('0');
					else{
						if ((i >= w[k].size()-4-Code[1]) && (i < w[k].size()-4)) 
							TMP.push_back('-');
						else
							TMP.push_back('+');

					}
				}
				if ((M1*w1) > 0) TMP.push_back('+');
				if ((M1*w1) < 0) TMP.push_back('-');
			}	
			N.push_back(TMP);
		}
	}

	~DefN(void)
	{
	}
};

