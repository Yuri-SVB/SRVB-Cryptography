#include "1/1.hpp"

int main (int argc, char **argv) {
	YSVB_TIMED_PUT("SRVB Key generation starting...")
	int k = ATO_MI(argv[1]), m = ATO_MI(argv[2]), p = ATO_MI(argv[3]);
	std::string name(argv[4]);
	YSVB_TIMED_SHOW(k)
	YSVB_TIMED_SHOW(m)
	YSVB_TIMED_SHOW(p)
	YSVB_TIMED_SHOW(name)
	YSVB_TIMED_PUT("")
	Key_Gen(k, m, p, name);
	YSVB_TIMED_PUT("SRVB Key generation ran successfully!")
}

