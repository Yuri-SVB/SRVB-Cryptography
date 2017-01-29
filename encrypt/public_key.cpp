#ifndef __PUBLIC_KEY_CPP__
#define __PUBLIC_KEY_CPP__

Pub_Key::Pub_Key() : _k(0), _m(0), _p(0), _giv(t_public_msg()) {}
Pub_Key::Pub_Key(t_meta_int k, t_meta_int m, t_meta_int p, t_public_msg	giv, std::string name) : _k(k), _m(m), _p(p), _giv(giv), _name(name) {}

t_public_msg Pub_Key::encode(const t_private_data& block) const {
	YSVB_CHECK_1(block.size(), ==, _k*_m, "Consistency of size of block.")
	t_meta_int 	i, j;
	t_int 	h;
	t_public_msg ret = _giv;
	YSVB_CHECK_1(ret.size(), ==, _giv.size(), "Consistency")
	YSVB_CHECK_1(ret.size(), ==, _k+1, "Consistency")
	for (
		i = 0, _m;
		i < _m;
		i++, ret.pop_front()
	) {
		ret.push_back(t_public_int(0,0));
		for (
			ret[_k+1] += ret[0], j = 1;// + (j = 1);
			j <= _k;
			j++
		) {
			ret[_k+1] += t_public_int(t_int(block[_k*i+j-1]?2:1))*ret[j];
		}
	}
	YSVB_CHECK_1(ret.size(), ==, _k+1, "Design")
	return ret;
}

std::string	Pub_Key::summary() const {
	std::stringstream ret;
	ret << std::endl;
	ret << "NAME            = " << _name << "_pub" << std::endl;
	ret << "K               = " << _k << std::endl;
	ret << "M               = " << _m << std::endl;
	ret << "P               = " << _p << std::endl;
	ret << "BLOCK SIZE      = " << _k * _m / 8 << std::endl;
	ret << "PADDING SIZE    = " << _p / 8 << std::endl;
	return ret.str();
}

std::istream& operator >> (std::istream& key_file, Pub_Key& PUBLIC_KEY) {
	if (key_file.good()) {
		YSVB_TIMED_PUT("LOADING PUBLIC KEY")
		t_meta_int		i, k, m, p;
		t_int			real, imag;
		std::string		line, name;
		for (
			std::getline(key_file, line);
			line.find('#') != std::string::npos;
			std::getline(key_file, line)
		) {}

		std::getline(key_file, line);
		name = line.substr(0,line.rfind("_pub"));

		k = stoi(line);

		std::getline(key_file, line);
		m = stoi(line);

		std::getline(key_file, line);
		p = stoi(line);

		t_public_msg	giv(k+1);
		for (i = 0; i <= k; i++) {
			std::getline(key_file, line);	real = mpz_class(line);
			std::getline(key_file, line);	imag = mpz_class(line);
			giv[i] = t_public_int(real, imag);
		}
		PUBLIC_KEY = Pub_Key(k, m, p, giv);
		YSVB_TIMED_PUT("PUBLIC KEY LOADING COMPLETE")
		YSVB_TIMED_SHOW(PUBLIC_KEY.summary())
	} else {
		YSVB_TIMED_PUT("ERROR IN LOADING OF PUBLIC KEY")
	}
	return key_file;
}

std::ostream& operator << (std::ostream& os, const Pub_Key& pk){
	if (os.good()) {
		os << "#Add '#' containing lines at the beginning of the file for comments." << std::endl;
		os << pk._name << "_pub" << std::endl;
		os << pk._k << std::endl;
		os << pk._m << std::endl;
		os << pk._p << std::endl;
		for (t_meta_int i = 0; i <= pk._k; i++) {
			os << pk._giv[i].gr() << std::endl;
			os << pk._giv[i].gi() << std::endl;
		}
	} else {
		YSVB_TIMED_PUT("ERROR IN STREAMING PUBLIC KEY")
	}
	return os;
}

#endif