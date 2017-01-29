#if !defined(__DECRYPTOR_CPP__)
#define __DECRYPTOR_CPP__

#include "decryptor.hpp"

#include <fstream>
#include <string>
#include <sstream>

Decryptor::Decryptor(const std::string& file_name) : 
	_pri_k(),
	_key_name(file_name.substr(0,file_name.find('.')))
{
	YSVB_TIMED_PUT("BUILDING DECRYPTOR OBJECT")
	std::ifstream key_file(file_name);
	key_file >> _pri_k;
	YSVB_TIMED_PUT("DECRYPTOR OBJECT BUILDING COMPLETE")
}
		/*
		WARNING: THERE IS ONE CASE IN WICH THIS ALGORITHM FAILS. NAMELY A FILE WITH 0 BYTES.
		*/
Decryptor::~Decryptor() {}
	
void	Decryptor::decrypt(
	const std::string  input_file_name,
	const std::string decryptet_file_name
) const {
	YSVB_TIMED_PUT("BEGINNING SRVB DECRYPTION")
	std::ifstream in(input_file_name);
	std::ofstream out;

	if (decryptet_file_name == default_output_file_name_flag() ) {
		out.open(input_file_name.substr(0, input_file_name.find('_')), std::ios::binary | std::ios::out);
	} else {
		out.open(decryptet_file_name, std::ios::binary | std::ios::out);
	}

	if (in.good() && out.good()) {
		t_meta_int N = (_pri_k.g_k() * _pri_k.g_m() - _pri_k.g_p()) / 8, i = N-1;
		char		lbb, lb, lf;	//last block's byte, last byte, loop flag
		std::stringstream last_block_str_stream;
		char 	  		  last_block_c_str[N];
		char SAMPLE_FILE_BYTE, SAMPLE_PADDING_BYTE;
		t_meta_int	ENCRYPTING_BLOCK_NUMBER;
		t_public_msg public_node_buffer(_pri_k.g_k()+1);
		t_private_data buffer(_pri_k.g_k() * _pri_k.g_m(), _pri_k.g_k() * _pri_k.g_m() - _pri_k.g_p());
		in.close();
		in.open(input_file_name);
		for (
			in >> public_node_buffer, lf = 1, ENCRYPTING_BLOCK_NUMBER = 0;
			lf;
			ENCRYPTING_BLOCK_NUMBER++
		) {
			YSVB_TIMED_SHOW(ENCRYPTING_BLOCK_NUMBER)
			*(static_cast<std::vector<bool> *>(&buffer)) = _pri_k.decode(public_node_buffer);
			buffer.padding_hash();
			in >> public_node_buffer;
			if (!in) {
				YSVB_CHECK_1(in.gcount(), ==, 0, "encrypted file must have an integer number of blocks, and nothing more but its header")
				for (
					lb  = buffer.get_byte(buffer.set_size(buffer.get_size() - 8));
					
					lb != (buffer.get_size()>0?buffer.get_byte(buffer.get_size() - 8):lbb) && 
					buffer.get_size() >= 0;
					
					buffer.less_eight(),
					lb = (buffer.get_size()>0?buffer.get_byte(buffer.get_size()):lbb)
				) {}
				YSVB_CHECK_2(buffer.get_size(), >=, 0, buffer.get_size(), ==, -8, "Size must be multiple of 8 and the last byte of one before last block is the only possible end byte if it is not one of the last block's.")
				YSVB_CHECK_1(lf, ==, 1, "it must be 1 until here")
				lf = 0;
			} else {
				lbb = buffer.get_byte(buffer.get_size()-8);
			}
				#if defined(__SHOW__)
				SAMPLE_FILE_BYTE = buffer.get_byte(0);
				YSVB_TIMED_SHOW(SAMPLE_FILE_BYTE)
				SAMPLE_PADDING_BYTE = buffer.get_byte(buffer.get_size());
				YSVB_TIMED_SHOW(SAMPLE_PADDING_BYTE)
				#endif
			out << buffer;
		}
		YSVB_TIMED_PUT("CLOSING FILES")
		in.close();
		out.close();
		YSVB_TIMED_PUT("SRVB ENCRYPTION FINISHED")
	} else {
		YSVB_TIMED_PUT("ERROR: COULD NOT ACCESS FILE TO BE DECRYPTED")
	}
}

#endif