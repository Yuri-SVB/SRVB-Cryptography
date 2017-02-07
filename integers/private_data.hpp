#if !defined(__private_data__)
#define __private_data__

#include "big_int.hpp"

class	t_private_data : public std::vector<bool> {
	t_meta_int	_data_size;
	char		_last_byte;
public:
	char		set_lb(char lb)			  {	return _last_byte = lb;	}
	char		get_lb()				  {	return _last_byte;	}
	t_meta_int	less_eight()			  {	return (_data_size -= 8);	}
	t_meta_int	set_size(t_meta_int size) {	return (_data_size = size);	}
	t_meta_int 	get_size() 			const {	return _data_size;	}
	t_private_data(t_meta_int size = 0, t_meta_int data_size = 0) : 
		std::vector<bool>(size),
		_data_size(data_size)
	{}

	inline char get_byte(t_meta_int pos) const {
		char ret = 0;
		ret |= (*this)[pos++] << 0;
		ret |= (*this)[pos++] << 1;
		ret |= (*this)[pos++] << 2;
		ret |= (*this)[pos++] << 3;
		ret |= (*this)[pos++] << 4;
		ret |= (*this)[pos++] << 5;
		ret |= (*this)[pos++] << 6;
		ret |= (*this)[pos  ] << 7;
		return ret;
	}

	std::string string_bits() const {
		t_meta_int i, N = this->size();
		std::string ret(N, 0);
		for (i = 0; i < N; i++) {
			ret[i] = (*this)[i]?'1':'0';
		}
		return ret;
	}

	void add_padding(const char* padding) {
		t_meta_int i, j, N;
		for (i = _data_size, j = 0, N = this->size(); i < N; i++, j++) {
			(*this)[i] = padding[j/8]&(1 << (j%8));
		}
	}

	void padding_hash() {
		YSVB_TIMED_PUT("Applying Hash")
		t_meta_int i, j, N = (this->size()-_data_size);
		if (N) {
			for (	//Apply invertible padding based hash to each byte 
				i = 0, j = _data_size, N;
				i < _data_size;
				i++, j = ((j+1)%N)+_data_size
			) {
				(*this)[i] = (*this)[i] ^ (*this)[j];
			}
		}
	}

	friend std::istream& operator >>   (std::istream& is, t_private_data& tpd)	{
		YSVB_CHECK_1(tpd.size() % 8, ==, 0, "first version constraint")
		YSVB_CHECK_1(tpd._data_size % 8, ==, 0, "first version constraint")
		t_meta_int i, N = tpd._data_size, buffer_size = N/8;
		char	buffer[buffer_size];
		YSVB_CHECK_1(is.good(), ==, true, "need to be good")
		is.read(buffer, buffer_size);
		char holder;
		if (is.gcount() != buffer_size) {
			YSVB_CHECK_1(is.gcount(), <, buffer_size, "Would not make any sense to be greater.")
			for (
				i = is.gcount(), buffer[i] = holder = (i?buffer[i-1]:tpd.get_lb()), i++;
				i < buffer_size;
				i++
			) {
				buffer[i] = ++holder;
			}
		}
		for (i = 0; i < N; i++) {
			tpd[i] = (buffer[i/8] & (1 << (i%8)));
		}
		tpd.set_lb(buffer[buffer_size-1]);
		return is;
	}

	friend std::ostream& operator <<   (std::ostream& os, const t_private_data& tpd)	{
		YSVB_CHECK_1(tpd.size() % 8, ==, 0, "first version constraint")
		int i, N = tpd._data_size, buffer_size = N/8;
		char	buffer[buffer_size];
		for (i = 0; i < buffer_size; i++) {
			buffer[i] = 0;
		}
		for (i = 0; i < N; i++) {
			buffer[i/8] |= (tpd[i] << i%8);
		}
		YSVB_CHECK_1(os.good(), ==, true, "need to be good")
		os.write(buffer, buffer_size);
		return os;
	}
};

#endif
