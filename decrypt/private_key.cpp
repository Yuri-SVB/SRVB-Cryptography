#ifndef __PRIVATE_KEY_CPP__
#define __PRIVATE_KEY_CPP__

Pri_Key::Pri_Key(): 
	_k(0), 
	_m(0), 
	_p(0), 
	_alpha(t_public_int()),
	_alpha_2(0),
	_theta(t_public_int()),
	_theta_ima(t_public_int()),
	_his(t_private_msg()),
	_rdtgiar(t_int())
{}

Pri_Key::Pri_Key(t_meta_int k, t_meta_int m, t_meta_int p, t_public_int alpha, t_public_int theta, t_private_msg his, std::string name): 
	_k(k), 
	_m(m), 
	_p(p), 
	_alpha(alpha),
	_alpha_2((_alpha.times_conj(_alpha)).gr()),
	_theta(theta%alpha),
	_theta_ima(theta.ModInv(alpha)),
	_his(his),
	_rdtgiar(_get_rdtgiar_from_alpha(alpha)),
	_name(name)
{}

t_int Pri_Key::_get_rdtgiar_from_alpha(t_public_int alpha) {
	return -alpha.gr()*(t_public_int(alpha.gi(),0).ModInv(t_public_int(alpha.mod2(),0))).gr()%alpha.mod2();
}

bool Pri_Key::is_valid() const {
	bool ret = true;
	ret &= (_his.size() == _k+1);
	ret &= (_k*_m % 8 == 0);	//This is a purely technical constraint that facilitates the implementation by avoiding the need to divide a byte.
	ret &= (_p % 8 == 0);		//This is a purely technical constraint that facilitates the implementation by avoiding the need to divide a byte.
	ret &= (_p < _k*_m);		//there must be strictly less padding than total bytes in each block.
	YSVB_CHECK_2(_his.size(), ==, _k+1, ret, ==, false, "_k is by definition the number of bits of each one of the _m steps.")
	t_meta_int i;
	t_int h;
	ret &= _alpha.mod2() < _his[0]*_his[0];
	for (i = 0, h = 1; i < _m; ++i) {	h *= 4;	}	//ie, h >>= (1+_m*2)
	ret &= (h * (_his[_k]) ) < (_alpha_2);
	for (h = i = 0; i <= _k; i++) {
		ret &= (h < _his[i]);
		YSVB_CHECK_2(h, <, _his[i], ret, ==, false, "Check of hyper growth of sequence")
		h += _his[i];
	}
	ret &= _alpha.fit_for_alpha();
	ret &= _theta.fit_for_theta(_alpha);
	ret &= ((_theta*_theta_ima)%_alpha) == t_public_int(1,0);
	ret &= t_public_int(_rdtgiar, 0)%_alpha == t_public_int(0, 1);

	YSVB_CHECK_2(_alpha.fit_for_alpha(), ==, false, t_public_int(_rdtgiar, 0)%_alpha, ==, t_public_int(0, 1), "If alpha's components a, b are coprime, thenthere must be real integer z whose remainder to alpha is i.")
	YSVB_CHECK_2(_theta.fit_for_theta(_alpha), ==, false, ((_theta*_theta_ima)%_alpha), ==, t_public_int(1,0), "If theta is invertible mod alpha, then its inverse is well defined.")

	YSVB_CHECK_2(_alpha.fit_for_alpha(), ==, 0, _alpha.GCD(_theta).mod2(), ==, t_int(1), "If alpha is prime, than GCD must be one.")
	YSVB_CHECK_2(_alpha.fit_for_alpha(), ==, 0, (_theta*_theta_ima)%_alpha, ==, t_public_int(1,0), "if alpha is prime, theta has a well defined inverse.")
	YSVB_CHECK_2((_theta*_theta_ima)%_alpha, !=, t_public_int(1,0), _alpha.GCD(_theta).mod2(), ==, t_int(1), "if theta has inverse, GCD(alpha, theta) is a uni.")

	YSVB_CHECK_2(ret, ==, true, _alpha.gr(), !=, _alpha.gi(),	"That might not be necessary, but solves more easily the case of deciding upon the sign of the remainder bellow.")
	YSVB_CHECK_2(ret, ==, true, _alpha.gr(), !=, t_int(0),		"Ring degenerates into real Integers. TODO: GIVE SECOND THOUGHTS ON THIS POSSIBILITY. IS IT LEGAL?")
	YSVB_CHECK_2(ret, ==, true, _alpha.gi(), !=, t_int(0),		"Ring degenerates into real Integers. TODO: GIVE SECOND THOUGHTS ON THIS POSSIBILITY. IS IT LEGAL?")
	YSVB_CHECK_2(
		ret, ==, 0,
		t_public_int(1, 0) % _alpha, ==, t_public_int(1, 0),
		"Mathematical consistency. These properties will be important to the decoding."
	)
	YSVB_CHECK_2(
		ret, ==, 0,
		t_public_int(_alpha_2 - t_int(1), t_int(0)) % _alpha, ==, t_public_int(-1, 0),
		"Mathematical consistency. These properties will be important to the decoding."
	)
#if defined(__DBG__)
	if (_alpha.gr()*_alpha.gr() > _alpha.gi()*_alpha.gi()) {
		YSVB_CHECK_2(
			ret, ==, 0,
			t_public_int(_alpha.gr(), 0) % _alpha, ==, t_public_int(0, -_alpha.gi()),
			"Mathematical consistency. These properties will be important to the decoding."
		)
		YSVB_CHECK_2(
			ret, ==, 0,
			t_public_int(_alpha_2 - _alpha.gr(), 0) % _alpha, ==, t_public_int(0, +_alpha.gi()),
			"Mathematical consistency. These properties will be important to the decoding."
		)
	} else {
		YSVB_CHECK_2(
			ret, ==, 0,
			t_public_int(_alpha.gi(), 0) % _alpha, ==, t_public_int(0, _alpha.gr()),
			"Mathematical consistency. These properties will be important to the decoding."
		)
		YSVB_CHECK_2(
			ret, ==, 0,
			t_public_int(_alpha_2 - _alpha.gi(), 0) % _alpha, ==, t_public_int(0, -_alpha.gr()),
			"Mathematical consistency. These properties will be important to the decoding."
		)
	}
#endif
	return ret;
}

t_private_msg	Pri_Key::dt_to_his(const t_private_data& block) const {
	YSVB_CHECK_1(block.size(), ==, _k*_m, "Consistency of size of block.")
	t_meta_int 	i, j;
	t_int 	h;
	t_private_msg ret = _his;
	YSVB_CHECK_1(ret.size(), ==, _his.size(), "Consistency")
	YSVB_CHECK_1(ret.size(), ==, _k+1, "Consistency")
	for (
		i = 0, _m;
		i < _m;
		i++, ret.pop_front()
	) {
		ret.push_back(0);
		for (
			ret[_k+1] += ret[0], j = 1;// + (j = 1);
			j <= _k;
			j++
		) {
			ret[_k+1] += (block[_k*i+j-1]?t_int(2):t_int(1))*ret[j];
		}
	}
	YSVB_CHECK_1(ret.size(), ==, _k+1, "Design")
	return ret;
}

t_private_msg Pri_Key::pub_to_his(const t_public_msg& pub_msg) const {
	YSVB_CHECK_1(pub_msg.size(), ==, _k+1, "compatibility of key to message")
	t_meta_int i;
	t_private_msg ret(_k+1);
	t_public_int holder;
	for (i = 0; i <= _k; ++i) {
		holder  = pub_msg[i];
		holder *= _theta_ima;
		holder %= _alpha;
		ret[i]  = holder.gi() * _rdtgiar + holder.gr();
		ret[i] %= _alpha_2;
		ret[i] += _alpha_2;
		ret[i] %= _alpha_2;
	}
	return ret;
}

t_private_data Pri_Key::his_to_dt(t_private_msg node) const {
	YSVB_CHECK_1(node.size(), ==, _k+1, "compatibility of key to message")
	t_meta_int 	i, j;
	t_int 	h;
	t_private_data ret(_k*_m);
	for (
		i = _m - 1;
		i >= 0;
		i--, /*h--,*/ node.pop_back(), node.push_front(h)
	) {
		YSVB_CHECK_1(node.size(), ==, _k+1, "Design")
		for (
			h = node[j = _k], j--;
			j >= 0;
			j--
		) {
			h -= node[j];
		}
		for (
			j = _k, j--;
			j >= 0;
			j--
		) {
			YSVB_CHECK_1(h, >, 0, "positivity of h")
			h -= (	(	(ret[_k*i+j] = (h > node[j]))	?t_int(1):t_int(0))*node[j]	);	//There is a reason for the use of the ternary operator in stead of an if clause that would save a subtraction half of times: to void timing attack
		}
	}
	#if defined(__DBG__)
	for (j = 0; j <= _k; j++) {
		YSVB_CHECK_1(node[j], ==, _his[j], "Original key node must be recovered.")
	}
	#endif
	YSVB_CHECK_1(node.size(), ==, _k+1, "Design")
	return ret;
}

t_private_data Pri_Key::decode(const t_public_msg& pub_msg) const {
	return this->his_to_dt(this->pub_to_his(pub_msg));
}

Pub_Key	Pri_Key::get_Public() const {
	t_meta_int i, N;
	t_public_msg gis;
	for (i = 0, N = _his.size(); i < N; i++) {
		gis.push_back(	(t_public_int(_his[i], 0) * _theta) % _alpha	);
	}
	return Pub_Key(_k, _m, _p, gis, _name);
}

std::string	Pri_Key::summary() const {
	std::stringstream ret;
	ret << std::endl;
	ret << "NAME            = " << _name << "_pri" << std::endl;
	ret << "K               = " << _k << std::endl;
	ret << "M               = " << _m << std::endl;
	ret << "P               = " << _p << std::endl;
	ret << "BLOCK SIZE      = " << _k * _m / 8 << std::endl;
	ret << "PADDING SIZE    = " << _p / 8 << std::endl;
	return ret.str();
}

std::istream& operator >> (std::istream& key_file, Pri_Key& PRIVATE_KEY) {
	if (key_file.good()) {
		YSVB_TIMED_PUT("LOADING PRIVATE KEY")
		t_meta_int				i, k, m, p;
		t_int			real, imag;
		t_public_int	alpha, theta;
		std::string		line, name;
		for (
			std::getline(key_file, line);
			line.find('#') != std::string::npos;
			std::getline(key_file, line)
		) {}
		name = line.substr(0,line.rfind("_pri"));

		std::getline(key_file, line);
		k = stoi(line);

		std::getline(key_file, line);
		m = stoi(line);

		std::getline(key_file, line);
		p = stoi(line);

		std::getline(key_file, line);
		real = mpz_class(line);
		std::getline(key_file, line);
		imag = mpz_class(line);
		alpha = t_public_int(real, imag);

		std::getline(key_file, line);
		real = mpz_class(line);
		std::getline(key_file, line);
		imag = mpz_class(line);
		theta = t_public_int(real, imag);

		t_private_msg	his(k+1);
		for (i = 0; i <= k; i++) {
			std::getline(key_file, line);
			his[i] = mpz_class(line);
		}
		PRIVATE_KEY = Pri_Key(k, m, p, alpha, theta, his);
		YSVB_TIMED_PUT("PRIVATE KEY LOADING COMPLETE")
		YSVB_TIMED_SHOW(PRIVATE_KEY.summary())
	} else {
		YSVB_TIMED_PUT("ERROR IN LOADING OF PRIVATE KEY")
	}
	return key_file;
}

std::ostream& operator << (std::ostream& os, const Pri_Key& PRIVATE_KEY) {
	os << "#Add '#' containing lines at the beginning of the file for comments." << std::endl;
	os << PRIVATE_KEY._name << "_pri" << std::endl;
	os << PRIVATE_KEY._k << std::endl;
	os << PRIVATE_KEY._m << std::endl;
	os << PRIVATE_KEY._p << std::endl;
	os << PRIVATE_KEY._alpha.gr() << std::endl;
	os << PRIVATE_KEY._alpha.gi() << std::endl;
	os << PRIVATE_KEY._theta.gr() << std::endl;
	os << PRIVATE_KEY._theta.gi() << std::endl;
	for (t_meta_int i = 0; i <= PRIVATE_KEY._k; i++) {
		os << PRIVATE_KEY._his[i] << std::endl;
	}
	return os;
}

#endif
