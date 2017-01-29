#if !defined(__ENCRYPTOR_CPP__)
#define __ENCRYPTOR_CPP__

#include "encryptor.hpp"

#include <fstream>
#include <string>
#include <random_input.hpp>

Encryptor::Encryptor(const std::string& file_name) : 
	_pub_k(),
	_key_name(file_name.substr(0,file_name.find('.')))
{
	YSVB_TIMED_PUT("BUILDING ENCRYPTOR OBJECT")
	std::ifstream key_file(file_name);
	key_file >> _pub_k;
	YSVB_TIMED_PUT("ENCRYPTOR OBJECT BUILDING COMPLETE")
}

Encryptor::~Encryptor() {}
	
void	Encryptor::encrypt(
	const std::string secret_file_name,
	const std::string output_file_name
) {
	YSVB_TIMED_PUT("BEGINNING SRVB ENCRYPTION")
	std::ifstream in(secret_file_name, std::ifstream::binary);
	std::ofstream out;
	if (output_file_name == default_output_file_name_flag() ) {
		out.open(secret_file_name + "_KEY_" + _key_name + ".srvb");
	} else {
		out.open(output_file_name);
	}
	if (in.good()) {
		t_private_data buffer(_pub_k._k*_pub_k._m, _pub_k._k*_pub_k._m - _pub_k._p);
		t_meta_int ps = _pub_k._p / 8, ENCRYPTING_BLOCK_NUMBER;
		char SAMPLE_FILE_BYTE, SAMPLE_PADDING_BYTE;
		char padding[ps];
		for (ENCRYPTING_BLOCK_NUMBER = 0; in.good() && out.good(); ENCRYPTING_BLOCK_NUMBER++) {
			YSVB_TIMED_SHOW(ENCRYPTING_BLOCK_NUMBER)
			in >> buffer;
			_RIS.get_c_str(padding, ps);
			std::string padding_str(padding, ps);
			buffer.add_padding(padding);
				#if defined(__SHOW__)
				SAMPLE_FILE_BYTE = buffer.get_byte(0);
				YSVB_TIMED_SHOW(SAMPLE_FILE_BYTE)
				SAMPLE_PADDING_BYTE = buffer.get_byte(buffer.get_size());
				YSVB_TIMED_SHOW(SAMPLE_PADDING_BYTE)
				#endif
			buffer.padding_hash();
			out << _pub_k.encode(buffer);
		}

		YSVB_TIMED_PUT("CLOSING FILES")
		in.close();
		out.close();
		YSVB_TIMED_PUT("SRVB ENCRYPTION FINISHED")
	} else {
		YSVB_TIMED_PUT("ERROR: COULD NOT ACCESS FILE TO BE ENCRYPTED")
	}
}

#endif