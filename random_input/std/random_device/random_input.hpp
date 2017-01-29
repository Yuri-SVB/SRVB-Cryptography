#ifndef __RANDOM_INPUT_SOURCE__
#define __RANDOM_INPUT_SOURCE__

// #include <chrono>
#include <random>
#include <iostream>

#define RLS 	256		//RANDOM LIMB SIZE
#define RLSMO	255		//RANDOM LIMB SIZE MINUS ONE
#define SRLS	65536	//SQUARED RANDOM LIMB SIZE
#define SRLSMO	65535	//SQUARED RANDOM LIMB SIZE  MINUS ONE

class Random_Input_Source {
  std::random_device _generator;
public:
	Random_Input_Source() {}

	t_int get(int n_limbs = 0, t_int initial = 0) {
		int		i;
		for (i = 0; i < n_limbs; i++) {
			initial *= RLS;
			initial += _generator() & RLSMO;
		}
		return initial;
	}
	int get_int() {
		return _generator();
	}
	void get_c_str(char* c_str_data, int n) {
		int i;
		for (i = 0; i < n; i++) {
			c_str_data[i] = _generator();
		}
		//Explanation
		#if defined(__DBG__)
		char a;
		int b = 255;
		a = b;
		YSVB_CHECK_1(a, ==, -1, "This is to say: when an int is assigned to a char, what happens is that its last byte is assinged.")
		#endif
	}
};

#endif