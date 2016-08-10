#pragma once
#include<vector>

class TWave
{
public:

	TWave(void);

	~TWave(void);

	int Run(const std::vector<int> &MasField, int LStr, int Start, int Finish);

	std::vector<int> Road;

private:

	int Direction;

};

