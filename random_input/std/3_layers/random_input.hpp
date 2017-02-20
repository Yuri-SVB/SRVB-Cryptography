#ifndef __RANDOM_INPUT_SOURCE__
#define __RANDOM_INPUT_SOURCE__

#include <chrono>
#include <random>
#include <iostream>

#define FNM		15		//FIRST NIBBLE
#define SNM		240		//SECOND NIBBLE MASK
#define RLS 	256		//RANDOM LIMB SIZE
#define RLSMO	255		//RANDOM LIMB SIZE MINUS ONE
#define SRLS	65536	//SQUARED RANDOM LIMB SIZE
#define SRLSMO	65535	//SQUARED RANDOM LIMB SIZE  MINUS ONE

class Random_Input_Source {
	std::random_device	_rd;
	std::minstd_rand0	_generator;
public:
	Random_Input_Source() {//: _generator(std::chrono::system_clock::now().time_since_epoch().count()) {
		std::string user_input;
		YSVB_TIMED_PUT("Please, enter a random string to serve as seed (avoid obvious stuff):")
		std::getline(std::cin,user_input);
		std::seed_seq user_seed (user_input.begin(),user_input.end());
		_generator = std::minstd_rand0(user_seed);
	}

	t_int get(int n_limbs = 0, t_int initial = 0) {
		int		i;
		// std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
		for (i = 0; i < n_limbs; i++) {
			_generator.discard(
				(std::chrono::system_clock::now().time_since_epoch().count()+i)
				& RLSMO
			);

			initial *= RLS;
			std::uniform_int_distribution<int> distribution(0,RLSMO);
			// initial += distribution(_generator);
			initial += distribution(_generator) ^ _generator() & RLSMO;
		}
		return initial;
	}
	int get_int() {
		_generator.discard(
			std::chrono::system_clock::now().time_since_epoch().count()
			& SRLSMO
		);

		// std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<int> distribution(0,RLSMO);
		return distribution(_generator) ^ _generator() & RLSMO;
	}
	void get_c_str(char* c_str_data, int n) {
		int i;
		// std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
		for (i = 0; i < n; i++) {
			_generator.discard(
				(std::chrono::system_clock::now().time_since_epoch().count()+i)
				& RLSMO
			);

			std::uniform_int_distribution<int> distribution(0,RLSMO);
			c_str_data[i] = distribution(_generator) ^ _generator() & RLSMO;
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
