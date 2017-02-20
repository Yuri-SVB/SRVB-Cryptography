#if !defined(__BIG_INT__)
#define __BIG_INT__

#include <ysvb_bug_proof.hpp>
#include <gmp.h>
#include <gmpxx.h>

class t_int {	//SRVB Big Integer
	mpz_class _data;
public:
	t_int(const mpz_class& data = mpz_class())	: _data(data) {}
	t_int(int data) 							: _data(data) {}
	t_int(long int data)						: _data(data) {}
	t_int(unsigned int data) 					: _data(data) {}
	t_int(unsigned long int data)				: _data(data) {}
	int is_prime(int reps = 15) {	//Miller_Rabin_test
		return mpz_probab_prime_p(_data.get_mpz_t(), reps);
	}

	t_int  operator +   () const					{	return t_int(this->_data);						}//TODO IMPLEMENT DUMMY OPERATION THAT DEMANDS THE SAME OF UNARY MINUS	//this->mpz_class::operator+();			}
	t_int  operator -   () const					{	return t_int(-this->_data);						}//this->mpz_class::operator-();			}
	t_int  operator ++	(int)						{	return _data++;									}
	t_int  operator --	(int)						{	return _data--;									}
	t_int& operator ++	()							{	_data++;	return *this;						}
	t_int& operator --	()							{	_data--;	return *this;						}
	t_int& operator +=  (const t_int& target)		{	this->_data += target._data;	return *this;	}	//this->mpz_class::operator+=(target);		}
	t_int  operator +   (const t_int& target) const	{	return t_int(this->_data +  target._data);		}	//this->mpz_class::operator+(target);		}
	t_int& operator -=  (const t_int& target)		{	this->_data -= target._data;	return *this;	}	//this->mpz_class::operator-=(target);		}
	t_int  operator -   (const t_int& target) const	{	return t_int(this->_data -  target._data);		}	//this->mpz_class::operator-(target);		}
	t_int& operator *=  (const t_int& target)		{	this->_data *= target._data;	return *this;	}	//this->mpz_class::operator*=(target);		}
	t_int  operator *   (const t_int& target) const	{	return t_int(this->_data *  target._data);		}	//this->mpz_class::operator*(target);		}
	t_int& operator /=  (const t_int& target)		{	this->_data /= target._data;	return *this;	}	//this->mpz_class::operator/=(target);		}
	t_int  operator /   (const t_int& target) const	{	return t_int(this->_data /  target._data);		}	//this->mpz_class::operator/(target);		}
	t_int& operator %=  (const t_int& target)		{	this->_data %= target._data;	return *this;	}	//this->mpz_class::operator %=(target);	}
	t_int  operator %   (const t_int& target) const	{	return t_int(this->_data %  target._data);		}	//this->mpz_class::operator %(target);		}
	t_int  sqrt			() const {
		mpz_t ret;
		mpz_init(ret);
		mpz_sqrt(ret, this->_data.get_mpz_t());
		return mpz_class(ret);
	}

	t_int GCD (const t_int& target) const {
		t_int D, d, r, zero;	//Dividend, divisor, remainder and zero
		int count = 0;
		for (
			r = *this % (d = target),	zero = 0;
			;
			D = d,		d = r,		r = (D % d)
		) {
			//YSVB_TIMED_SHOW(D)
			//YSVB_TIMED_SHOW(d)
			//YSVB_TIMED_SHOW(r)
			if (r == zero) {
				return d;
			}
		}
	}

	bool   operator ==  (const t_int& target) const	{	return this->_data == target._data;				}	//this->mpz_class::operator==(target);		}
	bool   operator !=  (const t_int& target) const	{	return this->_data != target._data;				}	//this->mpz_class::operator!=(target);		}
	bool   operator >   (const t_int& target) const	{	return this->_data >  target._data;				}	//this->mpz_class::operator==(target);		}
	bool   operator <   (const t_int& target) const	{	return this->_data <  target._data;				}	//this->mpz_class::operator!=(target);		}
	bool   operator >=  (const t_int& target) const	{	return this->_data >= target._data;				}	//this->mpz_class::operator==(target);		}
	bool   operator <=  (const t_int& target) const	{	return this->_data <= target._data;				}	//this->mpz_class::operator!=(target);		}

	friend std::istream& operator >>   (std::istream& is, t_int& bi)	{
		std::string buffer;
		// YSVB_CHECK_1(is.good(), ==, true, "need to be true to work")
		is >> buffer;
		if (!buffer.empty()) {	bi = mpz_class(buffer);	}
		return is;
	}
	friend std::ostream& operator <<   (std::ostream& os, const t_int& bi)	{
		return os << bi._data;
	}
};

#endif
