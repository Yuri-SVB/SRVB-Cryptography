#include "1/1.hpp"

int main (int argc, char **argv) {
	int k = ATO_MI(argv[1]), m = ATO_MI(argv[2]), p = ATO_MI(argv[3]);
	std::string name(argv[4]);
	Key_Gen(k, m, p, name);
	#if defined(__TDD__)
	Input_Check();
	#endif
}