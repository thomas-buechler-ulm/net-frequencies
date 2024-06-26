#include <cstdint>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

namespace nf{
bool REPORT_ALL = false;

template <typename lcp_t, typename ix_t>
struct lcp_iv_t{
	lcp_t lcp;
	ix_t lb;
	ix_t list_start;
	lcp_iv_t(lcp_t lcp, ix_t lb, ix_t ls) : lcp(lcp), lb(lb), list_start(ls) { }
};

template <bool REPORT_ALL, typename lcp_t = int32_t, typename ix_t = uint32_t>
void _run(const vector<lcp_t>& lcp, const vector<uint8_t>& bwt, vector<ix_t> & sa){
	constexpr ix_t UNDEF = std::numeric_limits<ix_t>::max();

	if(REPORT_ALL)			cout << "pos" << '\t' << "len" << endl;
	else				cout << "pos" << '\t' << "len" << '\t' << "freq" << endl;
	vector<ix_t> penultimate	(257, UNDEF);
	vector<ix_t> last		(257, UNDEF);
	vector<ix_t> list;
	using lcp_iv 			= lcp_iv_t<lcp_t, ix_t>;
	stack<lcp_iv, vector<lcp_iv>> 	stack;
	stack				.emplace(-1, 0, list.size());

	for(ix_t k = 1; k < lcp.size(); k++){
		//SET LAST AND PENULTIMATE
		{
			uint8_t c 	= bwt[k - 1];
			penultimate[c] 	= last[c];
			last[c] 	= k - 1;
		}

		list.emplace_back(k - 1);
		if (lcp[k] == stack.top().lcp) {
			continue;
		}
		ix_t lb = k-1;
		const bool dealt_with = lcp[k] < stack.top().lcp;
		//POP INTERVALS
		while(lcp[k] < stack.top().lcp){
			const lcp_iv& cur = stack.top();
			lb = cur.lb;

			if( cur.lcp > 0){ //COMPUTE NET FREQUENCY
				size_t nf = 0;
				for (size_t j = cur.list_start; j < list.size(); j++) {
					const auto i = list[j];
					auto c = bwt[i];
					if( i == last[c] && (penultimate[c] < lb || penultimate[c]==UNDEF )   ){
						if(REPORT_ALL) cout << sa[i] <<'\t' << cur.lcp << '\n';
						else nf++;
					}
				}
				if(!REPORT_ALL && nf) cout << sa[lb] << '\t'<< cur.lcp << '\t'<< nf << '\n';
			}
			list.resize(cur.list_start);
			stack.pop();
		}

		//PUSH INTERVAL
		if(lcp[k] > stack.top().lcp){
			stack.emplace(lcp[k], lb, list.size() - !dealt_with);
		}
	}
}
template <typename lcp_t = int32_t, typename ix_t = uint32_t>
void run(const vector<lcp_t>& lcp, const vector<uint8_t>& bwt, vector<ix_t> & sa){
	if (REPORT_ALL)
		_run<true, lcp_t, ix_t>(lcp, bwt, sa);
	else
		_run<false, lcp_t, ix_t>(lcp, bwt, sa);
}

}
