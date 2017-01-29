#if !defined(__ENCRYPTOR_HPP__)
#define __ENCRYPTOR_HPP__

#include "public_key.hpp"
#include "public_key.cpp"
#include <random_input.hpp>

#include <fstream>
#include <string>

class Encryptor {
	Pub_Key					_pub_k;
	std::string				_key_name;
	std::ifstream			_file;
	Random_Input_Source		_RIS;
inline static std::string default_output_file_name_flag() {	return "!@#$_MY_HARD_TO_GUESS_STRING_$#@!";	}
public:
	Encryptor(const std::string& file_name);
	~Encryptor();
	void	encrypt(
		const std::string secret_file_name,
		const std::string output_file_name = default_output_file_name_flag()
	);
	// _MY_HARD_TO_GUESS_STRING_public_msg	encode(const char* block) const;
};

#endif