#include "experiments.hpp"
#include "system_timer.cpp"


int main(int argc, char** argv) {
	using namespace experiment;
	using namespace std;
	string input_file_name = argv[1];
	ifstream in_file(input_file_name);
	std::string txt((std::istreambuf_iterator<char>(in_file)),(std::istreambuf_iterator<char>()));
	string output_dir_name = "./output/";
	//filesystem::create_directory(output_dir_name);
	SingleNF instance{txt, output_dir_name};

	bool extract_all = false;
	if(argc > 2 &&  "-a" == string(argv[2]) )
		extract_all = true;

	sys_timer t = sys_timer();
	t.start();
	if(extract_all){
		std::cerr << "pos" << '\t' << "len" << '\n';
		instance.asa->all_nf(true);
		cout << "Time for all_nf " << t.stop_and_get() << endl; t.reset_and_start();
	} else {
		std::cerr << "suf_arr.sa[lb]" << '\t' << "len" << '\t' << "nf" << '\n';
		instance.asa->all_nf_stack(true);
		cout << "Time for all_nf_stack " << t.stop_and_get() << endl; t.reset_and_start();
	}
	return 0;
}
