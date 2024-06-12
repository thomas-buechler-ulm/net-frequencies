#include <stack>

using namespace std;

namespace nf{
bool REPORT_ALL = false;

const size_t UNDEF = -1;

struct lcp_iv{
	int64_t lcp;
	size_t lb;
	vector<size_t> list;//NEW
	lcp_iv(int64_t lcp, size_t lb) : lcp(lcp), lb(lb) { }
};

void run(const vector<int32_t>& lcp, const vector<uint8_t>& bwt, vector<uint32_t> & sa){
	if(REPORT_ALL)	cout << "pos" << '\t' << "len" << endl;
	else			cout << "pos" << '\t' << "len" << '\t' << "freq" << endl;
	vector<size_t> penultimate	(257, UNDEF);
	vector<size_t> last			(257, UNDEF);
	last[bwt.front()] = 0;
	stack<lcp_iv,vector<lcp_iv>> stack;
	stack.push(lcp_iv(-1, 0));

	for(size_t k = 1; k < lcp.size(); k++){

		bool dealt_with = false;
		if( lcp[k] <= stack.top().lcp ){
			stack.top().list.push_back(k-1);
			dealt_with = true;
		}

		//POP INTERVALS
		size_t lb = k-1;
		while(lcp[k] < stack.top().lcp){
			lcp_iv cur 	= stack.top(); stack.pop();
			lb = cur.lb;

			if( cur.lcp > 0){ //COMPUTE NET FREQUENCY
				size_t nf 	= 0;
				for(auto i : cur.list){
					auto c 	= bwt[i];
					if( i == last[c] && (penultimate[c] < lb || penultimate[c]==UNDEF )   ){
						if(REPORT_ALL)	cout << sa[i] <<'\t' << cur.lcp << '\n';
						else			nf++;
					}
				}
				if(!REPORT_ALL && nf)	cout << sa[lb] << '\t'<< cur.lcp << '\t'<< nf << '\n';
			}
		}

		//PUSH INTERVAL
		if(lcp[k] > stack.top().lcp){
			stack.push(lcp_iv(lcp[k], lb));
			if(!dealt_with)
				stack.top().list.push_back(k-1);
		}

		//SET LAST AND PENULTIMATE
		if(k < bwt.size()){ // IN LAST ITERATION BWT[k] IS UNDEFINED, AS |BWT| = |LCP|-1
			uint8_t c 		= bwt[k];
			penultimate[c] 	= last[c];
			last[c] 			= k;
		}
	}
}
}
