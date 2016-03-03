#include <iostream>
#include <fstream>
#include <vector>
#include "../Libraries/func_lib.h"
#include "../Libraries/TCode.h"
#include "../Libraries/TK.h"
#include "../Libraries/TI.h"
#include "DefK.h"
//#include "DefK_intel.h"

int main(float eps, float dk, float beginNegative, float endNegative, float beginPositive, float endPositive)
{
	// Debug init
	beginNegative = -6.0f;
	endNegative = -2.0f;
	beginPositive = -2.0f;
	endPositive = -2.0f;
	dk = 0.05f;
	eps = 0.1;

	//Open file
	//std::cout << "Enter file name" << std::endl;
	char filename[20] = "pkp_db.pkp";
	//std::cin >> filename;
	std::ifstream f_in(filename);
	std::ofstream f_out("done.pkp");
	//Read and calculate
	pss::TI i({ 5.75, 33.0625 }, 0.05f);
	pss::TCode code;
	code.loadParametersFromFile(f_in);
	pss::TK K(code.getN(), beginNegative, endNegative, beginPositive, endPositive, dk);
	pss::DefK DK(i);
	while (!f_in.eof()){		
		code.loadCodeFromFile(f_in);
		pss::TK ans = DK.Run(code,K);
		if (ans.getFinded())
		{
			std::cout << "DONE!!!!!!\n";
			//Write to file
			code.writeCodeToFile(f_out);
			ans.writeToFile(f_out);
			f_out << std::endl;
			f_out.flush();
		}
	}
	f_out.close();
	f_in.close();
	system("pause");

	return 0;
}