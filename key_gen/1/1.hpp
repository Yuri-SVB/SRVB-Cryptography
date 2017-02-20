#if !defined(__1__)
#define __1__

#include <def.hpp>

#include <iostream>
#include <fstream>
#include <string>

#include <private_key.hpp>
#include <private_key.cpp>

#include <random_input.hpp>

class Key_Gen {
	Pri_Key* 			_pk;
	Random_Input_Source	_ris;
public:
	void make_key(int k, int m, int p, std::string name) {
		int i, j, expdbe = (m+4*k)/4 + 1;		//exponent (of two) divided by eight (number of bits of a byte) of the inferior quote of modulus of alpha
		t_int real, imag, sob, msob;	//size of ball, maximum size of ball
		
		t_public_int alpha, theta;
		bool found;

		YSVB_TIMED_PUT("Generating ALPHA...")
		real = _ris.get(expdbe, 1);
		imag = _ris.get(expdbe, 0);

		for (msob = 0, found = false; !found; msob++) {
			for (sob = 0, alpha = t_public_int(real, imag+msob); sob <= msob; sob++, alpha.rpp()) {
				if ( alpha.fit_for_alpha() ) {
					found = true;
					break;
				}
			}
			if (found) {	break;	}
			for (sob = 0, alpha = t_public_int(real+msob, imag); sob < msob; sob++, alpha.ipp()) {
				if ( alpha.fit_for_alpha() ) {
					found = true;
					break;
				}
			}
		}
		if (_ris.get_int() & 1) {
			alpha = alpha.conj();
		}
		alpha *= t_public_int::itopower(_ris.get_int() & 3);
		YSVB_TIMED_SHOW(alpha)

		YSVB_TIMED_PUT("Generating THETA...")
		for (found = false; !found; ) {
			real = _ris.get(2*expdbe, 0);
			imag = _ris.get(2*expdbe, 0);
			theta = t_public_int(real, imag);
			found = theta.fit_for_theta(alpha);
		}
		theta %= alpha;
		YSVB_TIMED_SHOW(theta)

		YSVB_TIMED_PUT("Generating HYPER INCREASING SEQUENCE...")
		t_private_msg his(k+1);

		for (expdbe = 0, msob = alpha.mod(); msob > 0; expdbe++, msob /= 2) {}
		expdbe /= 8;
		expdbe++;

		his[0] = alpha.mod();

		for (msob = i = 0; i < k; i++) {
			his[i] = (msob += (_ris.get(expdbe,0) + 1));
			for (j = 0; j < i; j++) {
				msob += his[i];
			}
		}
			his[i] = (msob += (_ris.get(expdbe,0) + 1));


		if (_pk) {	delete _pk;	}
		if (name == "") {
			_pk = new Pri_Key(k, m, p, alpha, theta, his);
		} else {
			_pk = new Pri_Key(k, m, p, alpha, theta, his, name);			
		}
	}

	void print_pri(const std::string& pri_kfn = std::string("pri_key.srvb")) {
		if (_pk) {
			std::ofstream out(pri_kfn);
			if (out.good()) {
				if (!_pk->is_valid()) {
					YSVB_TIMED_PUT("WARNIG: KEY SEEMS NOT TO BE VALID!")
				}
				out << *_pk;
			}
			out.close();
		} else {
			YSVB_TIMED_PUT("ERROR: WHILE TRYING TO ACCESS KEY")
		}
	}	
	void print_pub(const std::string& pub_kfn = std::string("pub_key.srvb")) {
		if (_pk) {
			std::ofstream out(pub_kfn);
			if (out.good()) {
				if (!_pk->is_valid()) {
					YSVB_TIMED_PUT("WARNIG: KEY SEEMS NOT TO BE VALID!")
				}
				Pub_Key _pub = _pk->get_Public();
				out << _pub;
			}
			out.close();
		} else {
			YSVB_TIMED_PUT("ERROR: WHILE TRYING TO ACCESS KEY")
		}
	}	
	void print_keys(
		const std::string& pri_kfn, 
		const std::string& pub_kfn
	) {
		print_pri(pri_kfn);
		print_pub(pub_kfn);
	}
	Key_Gen(int k, int m, int p, std::string name) : _pk(NULL) {
		make_key(k, m, p, name);
		print_keys(name + "_pri_key.srvb", name + "_pub_key.srvb");
	}
	~Key_Gen() {
		if (_pk) {	delete _pk;	}
	}
};

#endif
