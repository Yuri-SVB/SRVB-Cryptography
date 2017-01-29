#include <string>
#include <time.h>
#include "encryptor.cpp"

int main (int argc, char **argv) {
	YSVB_TIMED_PUT("SRVB encryption starting...")
	std::string key_file_name(argv[1]), secret_file_name(argv[2]), encrypted_file_name(argv[3]);
	YSVB_TIMED_SHOW(key_file_name)
	YSVB_TIMED_SHOW(secret_file_name)
	YSVB_TIMED_SHOW(encrypted_file_name)
	YSVB_TIMED_PUT("")
	Encryptor encryptor_obj(key_file_name);
	encryptor_obj.encrypt(secret_file_name, encrypted_file_name);
	YSVB_TIMED_PUT("SRVB encryption ran successfully!")
}