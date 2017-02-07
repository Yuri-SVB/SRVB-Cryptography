#ifndef __intgauss__
#define __intgauss__

#include <iostream>
#include "big_int.hpp"
template<typename GID>
class GaussInt;
typedef GaussInt<t_int>				t_public_int;

template<typename GID>
class GaussInt
{
	GID r, i;
public:
		GaussInt();
		GaussInt(GID dr, GID di = GID(0));
		GID			   gr		   () const;
		GID			   gi		   () const;
		GID			   mod		   () const;
		GID			   mod2		   () const;
		GaussInt<GID>  conj		   () const;
static	GaussInt<GID>  itopower	   (int exp);
		GaussInt<GID>  operator +  () const;
		GaussInt<GID>  operator -  () const;
		GaussInt<GID>& operator += (const GaussInt<GID>& target);
		GaussInt<GID>  operator +  (const GaussInt<GID>& target) const;
		GaussInt<GID>& operator -= (const GaussInt<GID>& target);
		GaussInt<GID>  operator -  (const GaussInt<GID>& target) const;
		GaussInt<GID>& operator *= (const GaussInt<GID>& target);
		GaussInt<GID>  operator *  (const GaussInt<GID>& target) const;
		GaussInt<GID>& at_conj	   (const GaussInt<GID>& target);
		GaussInt<GID>  times_conj  (const GaussInt<GID>& target) const;
		GaussInt<GID>& operator /= (const GaussInt<GID>& target);
		GaussInt<GID>  operator /  (const GaussInt<GID>& target) const;
		GaussInt<GID>& adbc		   (const GaussInt<GID>& target);
		GaussInt<GID>  div_by_conj (const GaussInt<GID>& target) const;
		GaussInt<GID>& operator %= (const GaussInt<GID>& target);
		GaussInt<GID>  operator %  (const GaussInt<GID>& target) const;
		GaussInt<GID>& asrm		   (const GaussInt<GID>& target);
		GaussInt<GID>  simpleremain(const GaussInt<GID>& target) const;
		GaussInt<GID>& aspr		   (const GaussInt<GID>& target, GaussInt<GID>& q);
		GaussInt<GID>  surplusdiv  (const GaussInt<GID>& target, GaussInt<GID>& q) const;
		void  		   EuclidianDiv(const GaussInt<GID>& D, GaussInt<GID>& Q, GaussInt<GID>& R) const;	//Divisor, Quotient, Remainder
		GaussInt<GID>  GCD		   (const GaussInt<GID>& target) const;
		GaussInt<GID>  ModInv	   (const GaussInt<GID>& M) 	 const;
		int			   is_prime	   (int reps) const;	//Miller-Rabin Test
		bool		   operator == (const GaussInt<GID>& target) const;
		bool		   operator != (const GaussInt<GID>& target) const;
	std::string print_me() const {
		std::string ret = r + std::string(i>=0?" +":" ") + i + "*i";
		return ret;
	}
	friend std::istream& operator >> (std::istream& is, GaussInt<GID>& gi) {
		GID	real, imag;
		is >> real >> imag;
		gi = GaussInt(real, imag);
		return is;
	}
	friend std::ostream& operator << (std::ostream& os, const GaussInt<GID>& gi) {
		os << gi.r << std::endl << gi.i << std::endl;
		return os;
	}
};

#endif
