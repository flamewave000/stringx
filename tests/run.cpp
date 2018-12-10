#include "run.hpp"
#include <string>

using namespace std;

int main(int argc, const char *argv[]) {
	bool verbose = argc > 1 ? string(argv[1]) == "-v" : false;
	evaluate(strx_manip_run_set, verbose);

	return EXIT_SUCCESS;
}