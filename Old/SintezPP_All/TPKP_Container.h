#pragma once
#include<vector>
#include<algorithm>
#include"TPKP.h"
class PKP_Container
{
public:
	std::vector<TPKP> CODES;
	std::vector<std::vector<std::vector<size_t>>> CHAINS;

	PKP_Container(void){}

	~PKP_Container(void){}

	bool push_back(TPKP pkp){
		std::vector<size_t>v = pkp.Code;
		std::vector<size_t>Links;
		std::vector<size_t>TMP;
		std::vector<std::vector<size_t>>Chains;

		for (unsigned int i = 2; i < v.size(); i++)
			Links.push_back(v[i]);

		//поиск цепочек связей
		int b = 0;
		for (unsigned int i = 0; i < Links.size(); i++){
			TMP.push_back(Links[i]/100);
			TMP.push_back(Links[i]%100);
			Chains.push_back(TMP);
			TMP.clear();
		}
		for (unsigned int i = 0; i < Chains.size()-1; i++){
			for (unsigned int j = i+1; j < Chains.size(); j++){
				for (unsigned int k = 0; k < Chains[i].size(); k++){
					for (unsigned int l = 0; l < Chains[j].size(); l++){
						if ((Chains[i][k] == Chains[j][l]) && (Chains[i][k] != 66)) 
							b = Chains[i][k];
					}
				}
				if (b != 0){
					for (unsigned int k = 0; k < Chains[i].size(); k++)
						if (Chains[i][k] != b)
							Chains[j].push_back(Chains[i][k]);
					Chains[i].clear();
					Chains[i].push_back(0);
					b = 0;
				}
			}
		}

		std::vector<std::vector<size_t>>ChainsTMP;
		for (unsigned int i = 0; i < Chains.size(); i++)
			if (Chains[i][0] != 0)
				ChainsTMP.push_back(Chains[i]);
		Chains = ChainsTMP;

		for (unsigned int i = 0; i < Chains.size(); i++)
			std::sort(Chains[i].begin(), Chains[i].end());
		std::sort(Chains.begin(), Chains.end());

		if (CHAINS.size() == 0){
			CODES.push_back(pkp);
			CHAINS.push_back(Chains);
			return true;
		}

		for(size_t i = 0; i < CHAINS.size(); i++)
			if (CHAINS[i] == Chains){
				return false;
			}
		CODES.push_back(pkp);
		CHAINS.push_back(Chains);
		return true;
	}

	inline TPKP& operator [](int i){
		return CODES[i];
	}

	inline size_t size(){
		return CODES.size();
	}

	bool InList(std::vector<size_t>v){
		std::vector<size_t>Links;
		std::vector<size_t>TMP;
		std::vector<std::vector<size_t>>Chains;

		if (v[0] == 1){
			return true;
		}

		if (CHAINS.size() == 0)
			return true;

		for (unsigned int i = 2; i < v.size(); i++)
			Links.push_back(v[i]);

		//поиск цепочек связей
		int b = 0;
		for (unsigned int i = 0; i < Links.size(); i++){
			TMP.push_back(Links[i]/100);
			TMP.push_back(Links[i]%100);
			Chains.push_back(TMP);
			TMP.clear();
		}
		for (unsigned int i = 0; i < Chains.size()-1; i++){
			for (unsigned int j = i+1; j < Chains.size(); j++){
				for (unsigned int k = 0; k < Chains[i].size(); k++){
					for (unsigned int l = 0; l < Chains[j].size(); l++){
						if ((Chains[i][k] == Chains[j][l]) && (Chains[i][k] != 66)) 
							b = Chains[i][k];
					}
				}
				if (b != 0){
					for (unsigned int k = 0; k < Chains[i].size(); k++)
						if (Chains[i][k] != b)
							Chains[j].push_back(Chains[i][k]);
					Chains[i].clear();
					Chains[i].push_back(0);
					b = 0;
				}
			}
		}

		std::vector<std::vector<size_t>>ChainsTMP;
		for (unsigned int i = 0; i < Chains.size(); i++)
			if (Chains[i][0] != 0)
				ChainsTMP.push_back(Chains[i]);
		Chains = ChainsTMP;

		for (unsigned int i = 0; i < Chains.size(); i++)
			std::sort(Chains[i].begin(), Chains[i].end());
		std::sort(Chains.begin(), Chains.end());
		for(size_t i = 0; i < CHAINS.size(); i++)
			if (CHAINS[i] == Chains){
				return false;
			}
		return true;
	}

private:
	inline int Convert(int x){
		return ((x-1)%3+1)*10 + (x-1)/3 + 1;
	}

};

