#if !defined(__public_msg__)
#define __public_msg__

#include <intgauss.hpp>
#include <intgauss.cpp>
#include "def.hpp"

class t_public_msg : public std::deque<t_public_int> {
public:
	t_public_msg(int size = 0) : std::deque<t_public_int>(size) {}
	friend std::istream& operator >>   (std::istream& is, t_public_msg& tpm)	{//			{	return this->mpz_class::
		for (int i = 0, N = tpm.size(); i < N && is; i++) {
			// YSVB_CHECK_1(is.good(), ==, true, "need to be good")
			is >> tpm[i];
		}
		return is;
	}
	friend std::ostream& operator <<   (std::ostream& os, const t_public_msg& tpm)	{//			{	return this->mpz_class::
		for (int i = 0, N = tpm.size(); i < N; i++) {
			os << tpm[i].gr() << std::endl;
			os << tpm[i].gi() << std::endl;
		}
		return os;
	}
};

#endif