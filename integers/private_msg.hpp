#if !defined(__private_msg__)
#define __private_msg__

#include "big_int.hpp"

class	t_private_msg : public std::deque<t_int> {
public:
	t_private_msg(int size = 0) : std::deque<t_int>(size) {}
	// friend std::istream& operator >>   (std::istream& is, const t_private_msg& tpm)	{
	// 	for (int i = 0, N = tpm.size(); i < N; i++) {
	// 		is << tpm[i] << std::endl;
	// 	}
	// 	return is;
	// }
	friend std::ostream& operator <<   (std::ostream& os, const t_private_msg& tpm)	{
		for (int i = 0, N = tpm.size(); i < N; i++) {
			os << tpm[i] << std::endl;
		}
		return os;
	}
};

#endif