#if !defined(__DECRYPTOR_HPP__)
#define __DECRYPTOR_HPP__

#include "private_key.hpp"
#include "private_key.cpp"

#include <fstream>
#include <string>

class Decryptor {
	Pri_Key			_pri_k;
	std::string		_key_name;
	std::ifstream	_file;
inline static std::string default_output_file_name_flag() {	return "!@#$_MY_HARD_TO_GUESS_STRING_$#@!";	}
public:
	Decryptor(const std::string& file_name);
	~Decryptor();
	void	decrypt(
		const std::string  input_file_name,
		const std::string secret_file_name = default_output_file_name_flag()
	) const;
	// t_public_msg	decode(const char* block) const;
};

#endif