#pragma once
#include "../Libraries/TElement.h"
#include "../Libraries/TLink.h"
#include <set>

namespace pss
{
	class TChain
	{
	private:
		std::set<TElement>						m_elements;
	public:
		void									addLinkToChain(const TLink & link);
		void									addElementToChain(const TElement & elem);
		void									addChainToChain(const TChain & chain);
		void									clear();
		bool									find(const TElement & element) const;
		bool									checkElemByOnePlanetarySet() const;
		const TElement&							getFirst() const;
		int										size() const;
		bool									intersect(const TChain& chain);

		const std::set<TElement>&				getElements() const;

		friend bool operator<(const TChain& chain1, const TChain& chain2);
	};
}