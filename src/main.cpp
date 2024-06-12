#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <divsufsort.h>

#include "lib/phi.hpp"
#include "lib/system_timer.cpp"
#include "nf.cpp"

using namespace std;

static const int REPORT_WITNESSES = 0;
static const int REPORT_NET_FREQUENCIES = 1;

int REPORT = REPORT_NET_FREQUENCIES;



vector<uint8_t> load_from_file(string file_name){
	vector<uint8_t> text;
	ifstream input(file_name, std::ios::in|std::ios::binary|std::ios::ate);
	size_t n = input.tellg();
	input.seekg(0);
	text.resize(n+1);
	input.read((char*)text.data(), n);
	// Append Sentinal
	text[n] = 0;
	return text;
}

vector<uint32_t> generate_sa(vector<uint8_t> & text){
	vector<uint32_t> sa(text.size());
	divsufsort((const sauchar_t*)text.data(), (int32_t*)sa.data(), text.size());
	return sa;
}

vector<int32_t> generate_lcp(vector<uint8_t> & text, vector<uint32_t> & sa){
	vector<int32_t> lcp(sa.size()+1, 0);
	PHI(text, sa, lcp);
	return lcp;
}

vector<uint8_t> generate_bwt(vector<uint8_t> & text, vector<uint32_t> & sa){
	vector<uint8_t> bwt(text.size());
	for(uint64_t i=0; i<bwt.size(); i++)
		bwt[i] = (sa[i]>0)? text[sa[i]-1] : text.back();
	return bwt;
}

int main(int argc, char **argv){
	std::ios::sync_with_stdio(false); // faster cout!
	
	// Check Parameters
	if(argc < 2){
		cerr << "Programm calculates all net-frequencies." << endl;
		cerr << "[1] Input file" << endl;
		cerr << "Optional:" << endl;
		cerr << "-a\tProgram outputs all strings-positions with nf > 0" << endl;
		return 1;
	}
	if(argc > 2 &&  "-a" == string(argv[2]) )
		nf::REPORT_ALL = true;


	sys_timer t = sys_timer();
	t.start();


	vector<uint8_t> text 	= load_from_file(argv[1]);
	cerr << "Time for loading string " << t.stop_and_get() << endl;t.reset_and_start();

	vector<uint32_t> sa 	= generate_sa(text);
	cerr << "Time for generating  sa " << t.stop_and_get() << endl; t.reset_and_start();

	vector<int32_t> lcp 	= generate_lcp(text,sa);
	cerr << "Time for generating lcp " << t.stop_and_get() << endl; t.reset_and_start();

	vector<uint8_t> bwt 	= generate_bwt(text,sa);
	cerr << "Time for generating bwt " << t.stop_and_get() << endl; t.reset_and_start();

	nf::run(lcp, bwt, sa);
	cerr << "Time for net-freqs      " << t.stop_and_get() << endl; t.reset_and_start();

	return 0;
}
