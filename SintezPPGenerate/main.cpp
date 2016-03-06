#include <iostream>
#include <vector>
#include <algorithm>
#include <direct.h>
#include "../Libraries/func_lib.h"
#include "../Libraries/TCode.h"
#include "../Libraries/TSingletons.h"

std::vector<int> create_Vect_BF(std::vector<std::vector<int>>, int);
std::vector<std::vector<int>> create_Chains(int, int, const std::vector<int> &, int);

int main()
{
	std::ofstream file_out, file_fail_0, file_fail_N, fail_free, fail_chains;
	setlocale(LC_ALL, "Russian");
	std::cout << "======  Синтез планетарных передач с тремя степенями свободы.  ======\n\n";
	//	Исходные данные
	int W;
	int N;
	int Count_L;
	int Count_F;
	int Count_B;

	std::cout << "\t\t\tИсходные данные." << std::endl << "Число степеней свободы:	";
	std::cin >> W;
	std::cout << "Количество ПМ:		";
	std::cin >> N;

	switch (W)
	{
	case 2:
	{
			  Count_B = N;
			  Count_F = 0;	// для двухстепенных блокировочный фрикцион не считаем
			  Count_L = 2 * N - W;
	}
		break;
	case 3:
	{
			  if (N == 1)
			  {
				  std::cout << "Ошибка: Один планетарный ряд при трех степенях свободы!\n";
				  system("pause");
				  return 0;
			  }
			  Count_B = N - 1;
			  Count_F = 2;
			  Count_L = 2 * N - W;
	}
		break;
	default:
	{
			   std::cout << "Ошибка: Некорректное количество степеней свободы!\n";
			   system("pause");
			   return 0;
	}
		break;
	}
	std::cout << "Количество связей:	" << Count_L << std::endl;
	std::cout << "Количество фрикционов:	" << Count_F << std::endl;
	std::cout << "Количество тормозов:	" << Count_B << std::endl;



	_mkdir("..\\Results");
	file_out.open("..\\Results\\pkp_db.pkp", std::ofstream::out);
	file_fail_0.open("..\\Results\\failed_0.pkp.log", std::ofstream::out);
	file_fail_N.open("..\\Results\\failed_N.pkp.log", std::ofstream::out);
	fail_free.open("..\\Results\\failed_free.pkp.log", std::ofstream::out);
	fail_chains.open("..\\Results\\fail_chains.pkp.log", std::ofstream::out);

	file_out << W << ' ' << N << ' ' << Count_L << ' ' << Count_F << ' ' << Count_B << '\n';
	file_fail_0 << W << ' ' << N << ' ' << Count_L << ' ' << 0 << ' ' << 0 << '\n';
	file_fail_N << W << ' ' << N << ' ' << Count_L << ' ' << 0 << ' ' << 0 << '\n';
	fail_chains << W << ' ' << N << ' ' << Count_L << ' ' << 0 << ' ' << 0 << '\n';
	fail_free << W << ' ' << N << ' ' << Count_L << ' ' << Count_F << ' ' << Count_B << '\n';
	//	Генерация всех возможных связей
	std::vector<int> tmp;
	std::vector<int> vect_all_links;		//	Вектор всех возможных связей
	//	Заполняем вектор всех возможных связей, пропускаем связи между элементами одного ряда.
	for (int i = 0; i <= 3 * (N - 1); i++)
		for (int j = (i / 3 + 1) * 3; j < 3 * N; j++)
			vect_all_links.push_back(pss::pos_2_code(i) * 100 + pss::pos_2_code(j));
	//	Генерация кодов
	pss::TCode C(W, N);
	std::vector<std::vector<std::vector<int>>> chains_all;	//	Все цепочки связей
	for (int in = 0; in < 3 * N; in++)				//	Вход на все звенья
		for (int out = 0; out < 3 * N; out++)			//	Выход на все звенья
		{
			if (in != out)							//	Проверка: вход и выход не могут быть одним и тем же элементом
			{
				C.clear();
				C.setIn(pss::pos_2_code(in));
				C.setOut(pss::pos_2_code(out));
				std::vector<int> vect_links;			//	Вектор связей
				std::vector<int> vect_combi_links;		//	Вектор сочетаний связей
				//	Создаем первое сочетание связей из всех возможных связей по Count_L+Count_F (количество связей + количество фрикционов) без повторений: 0,1,2,3...
				for (int i = 0; i < Count_L; i++)
					vect_combi_links.push_back(i);
				//	В цикле генерируем все возможные сочетания связей
				do{
					//	Заполняем вектор связей с учетом сгенерированного сочетания
					vect_links.clear();
					for (int i = 0; i < vect_combi_links.size(); i++)
						vect_links.push_back(vect_all_links[vect_combi_links[i]]);
					C.setLinks(vect_links);
					//	Определяем цепочки связей
					std::vector<std::vector<int>> chains = create_Chains(pss::pos_2_code(in), pss::pos_2_code(out), vect_links, N);
					bool flag = false;
					for (size_t i = 0; i < chains_all.size(); i++)
						if (chains_all[i] == chains)
						{
							tmp.clear();
							C.setFrictions(tmp);
							C.setBrakes(tmp);
							C.writeCodeToFile(fail_chains);
							flag = true;
							break;
						}
					if (flag == true)
						continue;
					chains_all.push_back(chains);
					//	Определяем элементы, на которых будет установлен фрикцион или тормоз
					std::vector<int> vect_all_FB = create_Vect_BF(chains, N);			//	Вектор фрикционов
					tmp = vect_all_FB;
					tmp.push_back(pss::pos_2_code(in));
					tmp.push_back(pss::pos_2_code(out));
					if (vect_all_FB.size() == Count_B + Count_F)
					{
						std::vector<int> vect_all_frict;		//	Вектор всех возможных фрикционов
						std::vector<int> vect_combi_frict;		//	Вектор сочетаний фрикционов
						std::vector<int> vect_frict;			//	Вектор фрикционов
						for (int i = 0; i < tmp.size(); i++)
							for (int j = i + 1; j < tmp.size(); j++)
								vect_all_frict.push_back(tmp[i] * 100 + tmp[j]);
						//	Создаем первое сочетание фрикционов из связей по Count_F (количество фрикционов) без повторений: 0,1...
						for (int i = 0; i < Count_F; i++)
							vect_combi_frict.push_back(i);
						//	В цикле генерируем все возможные сочетания фрикционов
						do{
							//	Заполняем вектор фрикционов с учетом сгенерированного сочетания
							vect_frict.clear();
							for (int i = 0; i < vect_combi_frict.size(); i++)
								vect_frict.push_back(vect_all_frict[vect_combi_frict[i]]);
							C.setFrictions(vect_frict);
							std::vector<int> vect_combi_brakes;		//	Вектор сочетаний тормозов
							//	Создаем первое сочетание тормозов из всех возможных по Count_B
							for (int i = 0; i < Count_B; i++)
								vect_combi_brakes.push_back(i);
							do{
								std::vector<int> vect_brakes;	//	Вектор тормозов
								//	Заполняем вектор тормозов с учетом сгенерированного сочетания
								for (int i = 0; i < vect_combi_brakes.size(); i++)
									vect_brakes.push_back(vect_all_FB[vect_combi_brakes[i]]);
								C.setBrakes(vect_brakes);
								//C.print();
								if (C.check())
									C.writeCodeToFile(file_out);
								else
									C.writeCodeToFile(fail_free);
							} while (pss::next_combination(vect_combi_brakes, vect_all_FB.size() - 1));
						} while (pss::next_combination(vect_combi_frict, vect_all_frict.size() - 1));
					}
					else
					{
						if (vect_all_FB.size() != 0)
						{
							tmp.clear();
							C.setFrictions(tmp);
							C.setBrakes(tmp);
							C.writeCodeToFile(file_fail_N);
						}
						else
						{
							tmp.clear();
							C.setFrictions(tmp);
							C.setBrakes(tmp);
							C.writeCodeToFile(file_fail_0);
						}
					}
				} while (pss::next_combination(vect_combi_links, vect_all_links.size() - 1));
			}
		}
	file_out.close();
	file_fail_0.close();
	file_fail_N.close();
	fail_free.close();
	fail_chains.close();
	system("pause");
	return 0;
}

std::vector<int> create_Vect_BF(std::vector<std::vector<int>> Chains, int N)
{
	size_t b = 0;
	std::vector<int> brakes;
	//проверки корректности кода
	for (size_t i = 0; i < Chains.size(); i++)
	{
		//проверка связи вход-выход
		if (Chains[i].size() > 1 && Chains[i][Chains[i].size() - 2] >= 44 && Chains[i][Chains[i].size() - 1] >= 44)
		{
			//std::cout << "Есть связь входа с выходом:\n";
			return brakes;
		}
		//проверка связей между элементами одного ряда
		for (int j = 1; j <= N; j++)
		{
			b = 0;
			for (int k = 0; k < Chains[i].size(); k++)
				if (Chains[i][k] % 10 == j)
					b++;
			if (b > 1)
			{
				//std::cout << "Есть связь между элементами одного ряда:\n";
				return brakes;
			}
		}
	}
	//определение тормозов
	for (size_t i = 0; i < Chains.size(); i++)
		if (Chains[i][Chains[i].size() - 1] < 44)
			brakes.push_back(Chains[i][0]);
	return brakes;
}	//	Проверка корректности и определение возможных расположений тормозов. Если начальный код проверку не прошел - возвращает пустой вектор, если прошел - вектор с тормозами

std::vector<std::vector<int>> create_Chains(int in, int out, const std::vector<int> &links, int N)
{
	//Создаем начальные цепочки (каждая связь делается цепочкой)
	std::vector<std::vector<int>> Chains;
	Chains.resize(links.size() + 2);
	Chains[0].push_back(in);
	Chains[0].push_back(44);
	Chains[1].push_back(out);
	Chains[1].push_back(55);
	for (int i = 0; i < links.size(); i++){
		Chains[i + 2].push_back(links[i] / 100);
		Chains[i + 2].push_back(links[i] % 100);
		std::sort(Chains[i + 2].begin(), Chains[i + 2].end());
	}
	//поиск элементов, свободных от связей и создание цепочек, которые их содержат
	size_t b;
	for (size_t i = 0; i < 3 * N; i++)
	{
		b = 0;
		for (size_t j = 0; j < links.size(); j++){
			if (links[j] / 100 == pss::pos_2_code(i) || links[j] % 100 == pss::pos_2_code(i)){
				b++;
			}
		}
		if (b == 0 && pss::pos_2_code(i) != in && pss::pos_2_code(i) != out){
			Chains.resize(Chains.size() + 1);
			Chains[Chains.size() - 1].push_back(pss::pos_2_code(i));
			b = 0;
		}
	}
	//поиск цепочек связей
	b = 0;
	for (size_t i = 0; i < Chains.size() - 1; i++){
		for (size_t j = i + 1; j < Chains.size(); j++){
			for (size_t k = 0; k < Chains[i].size(); k++){
				if (pss::in_vect(Chains[j], Chains[i][k]) != -1)
					b = Chains[i][k];
			}
			if (b != 0){
				for (size_t k = 0; k < Chains[i].size(); k++)
					Chains[j].push_back(Chains[i][k]);
				Chains[i].clear();
				Chains[i].push_back(0);
				b = 0;
			}
		}
	}
	//удаление пустых цепочек
	for (size_t i = 0; i < Chains.size(); i++){
		if (Chains[i][0] == 0){
			Chains.erase(Chains.begin() + i);
			i = i - 1;
		}
	}
	//удаление повторений
	for (size_t i = 0; i < Chains.size(); i++){
		pss::del_repetition(Chains[i]);
	}
	return Chains;
}