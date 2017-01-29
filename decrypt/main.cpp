#include "decryptor.cpp"

int main (int argc, char **argv) {
	YSVB_TIMED_PUT("SRVB encryption starting...")
	std::string key_file_name(argv[1]), encrypted_file_name(argv[2]), decrypted_file_name(argv[3]);
	YSVB_TIMED_SHOW(key_file_name)
	YSVB_TIMED_SHOW(encrypted_file_name)
	YSVB_TIMED_SHOW(decrypted_file_name)
	YSVB_TIMED_PUT("")
	Decryptor decryptor_obj(key_file_name);
	decryptor_obj.decrypt(encrypted_file_name, decrypted_file_name);
	YSVB_TIMED_PUT("SRVB decryption ran successfully!")
}