#ifndef PHI_HPP
#define PHI_HPP
#include <vector>

// This algorithm is based on the following paper:
// Juha Karkkainen, Giovanni Manzini & Simon J. Puglisi
// Permuted longest-common-prefix array
// Proceedings of the 20th Annual Symposium on Combinatorial Pattern Matching (CPM '09)
// G. Kucherov and E. Ukkonen (Eds.)
// LNCS 5577, pp. 181-192. Springer, Heidelberg (2009)


template<class text_t, class sa_t, class lcp_t>
void PHI(text_t& text, sa_t& sa, lcp_t& lcp)
{
	uint64_t n = text.size();
	std::vector<uint32_t> phi(n);
	phi[0] = sa[n-1];
	for(uint64_t i=1; i<n; ++i)
	{
		phi[sa[i]] = sa[i-1];
	}
	for(uint64_t i=0, len=0; i<n; ++i)
	{
		uint64_t j = phi[i];
		while(text[j+len] == text[i+len])
		{
			++len;
		}
		phi[i] = len;
		if(len)
		{
			--len;
		}
	}
	lcp[0] = -1;
	for(uint64_t i=1; i<n; ++i)
	{
		lcp[i] = phi[sa[i]];
	}
	lcp[n] = -1;
}

#endif