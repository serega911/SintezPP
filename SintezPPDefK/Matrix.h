#pragma once

#include "../Libraries/GlobalDefines.h"

#include "Defines.h"


NS_ARI_START

class Matrix
{
private:

	MatrixTable									m_matrix;



public:

	explicit Matrix( const MatrixTable & table );
	explicit Matrix( size_t size );

	const MatrixTable&							getMatrix() const;
	const MatrixLine&							operator[]( size_t i ) const;

	const CellType&								at( size_t i, size_t j ) const;
	CellType&									at( size_t i, size_t j );

	void										setSize( size_t size );
	size_t										getSize() const;

};

NS_ARI_END
