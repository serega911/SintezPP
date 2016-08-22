#pragma once

#include "../Libraries/GlobalDefines.h"

#include <vector>

#include "Defines.h"

NS_ARI_START

class Jacobi
{
private:
	size_t										m_size;
	std::vector<std::vector<Equation>>			m_determinant;
public:

	Jacobi();

	void										setSize( size_t size );
	void										setEquation( size_t i, size_t j, const Equation & eq );
	size_t										size() const;

	const std::vector<Equation>&				operator[]( size_t i ) const;

};

NS_ARI_END