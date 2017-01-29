#ifndef __INT_GAUSS_CPP__
#define __INT_GAUSS_CPP__

template<typename GID>
GaussInt<GID>::GaussInt() {}

template<typename GID>
GaussInt<GID>::GaussInt(GID dr, GID di) : r(dr), i(di) {}

template<typename GID>
GID GaussInt<GID>::gr() const {
	return r;
}

template<typename GID>
GID GaussInt<GID>::gi() const {
	return i;
}

template<typename GID>
GID GaussInt<GID>::mod() const {
	return mod2().sqrt();
}

template<typename GID>
GID GaussInt<GID>::mod2() const {
	return this->r*this->r + this->i*this->i;
}

template<typename GID>
GaussInt<GID>  GaussInt<GID>::conj() const {
	return GaussInt<GID>(this->r, -this->i);
}

template<typename GID>
GaussInt<GID> GaussInt<GID>::itopower(int exp) {
	return exp&1?
		exp&2?
			GaussInt<GID>(0,-1)
		:
			GaussInt<GID>(0,1)
	:
		exp&2?
			GaussInt<GID>(-1,0)
		:
			GaussInt<GID>(1,0)
	;
}

template<typename GID>
GaussInt<GID>  GaussInt<GID>::operator +  () const	{	return *this;	}

template<typename GID>
GaussInt<GID>  GaussInt<GID>::operator -  () const {	return GaussInt<GID>(-r, -i);	}

#define ASSIGN_OP(OP) template<typename GID>\
GaussInt<GID>& GaussInt<GID>::operator OP (const GaussInt<GID>& target)\
{\
	this->r OP target.r;\
	this->i OP target.i;\
	return *this;\
}

ASSIGN_OP(+=)
ASSIGN_OP(-=)

template<typename GID>
GaussInt<GID>& GaussInt<GID>::operator *= (const GaussInt<GID>& target)
{
	GID holder  = this->r;
	    // this->r = this->r * target.r - this->i * target.i;
	    this->r *= target.r; this->r -= this->i * target.i;
	    // this->i = holder  * target.i + this->i * target.r;
	    this->i *= target.r; this->i += holder  * target.i;
	return *this;
}

template<typename GID>
GaussInt<GID>& GaussInt<GID>::at_conj (const GaussInt<GID>& target)
{
	GID holder  = this->r;
	    // this->r = this->r * target.r - this->i * target.i;
	    this->r *= target.r; this->r += this->i * target.i;
	    // this->i = holder  * target.i + this->i * target.r;
	    this->i *= target.r; this->i -= holder  * target.i;
	return *this;
}

template<typename GID>
GaussInt<GID>& GaussInt<GID>::operator /= (const GaussInt<GID>& target)
{
	GID holder	= this->r,
		mod2	= target.mod2();
		this->r = (this->r * target.r + this->i * target.i) / (mod2);
		this->i = (this->i * target.r - holder  * target.i) / (mod2);
	return *this;
}

template<typename GID>
GaussInt<GID>& GaussInt<GID>::operator %= (const GaussInt<GID>& target)
{
	// return *this -= (*this/target)*target;
	GaussInt<GID> dummy;
	this->EuclidianDiv(target, dummy, *this);
	return *this;
}

template<typename GID>
GaussInt<GID>& GaussInt<GID>::asrm (const GaussInt<GID>& target)
{
	GaussInt<GID> D(this->times_conj(target)), d(target.mod2()), q(D/d);
	return *this -= target*q;
}

template<typename GID>
GaussInt<GID>  GaussInt<GID>::simpleremain(const GaussInt<GID>& target) const
{
	GaussInt<GID> ret(*this);
	return ret.asrm(target);
}

template<typename GID>
GaussInt<GID>& GaussInt<GID>::aspr (const GaussInt<GID>& target, GaussInt<GID>& q)
{
	GID holder	= this->r,
		mod2	= target.mod2(),
		D		= (this->r * target.r + this->i * target.i),
		dummy;
		q.r = D / (mod2);
		if (D > 0) {
			if (dummy > 0) {}
			if (q.r * mod2 == D) {
				++dummy;
			} else {
				YSVB_CHECK_1(q.r * mod2, <, D, "quotient of integer division times its dividor is not bigger in modulus than dividend.")
				++q.r;
			}
		} else if (D < 0) {
			if (q.r * mod2 == D) {
				--dummy;
			} else {
				YSVB_CHECK_1(q.r * mod2, >, D, "quotient of integer division times its dividor is not bigger in modulus than dividend.")
				--q.r;
			}
		} else {
			YSVB_CHECK_1(D, ==, 0, "tricotomy of integers")
			if (q.r * mod2 == dummy) {
				++dummy;
			} else {
				--dummy;
			}
		}
		q.i = (D = this->i * target.r - holder  * target.i) / (mod2);
		if (D > 0) {
			if (dummy > 0) {}
			if (q.i * mod2 == D) {
				++dummy;
			} else {
				YSVB_CHECK_1(q.i * mod2, <, D, "quotient of integer division times its dividor is not bigger in modulus than dividend.")
				++q.i;
			}
		} else if (D < 0) {
			if (q.i * mod2 == D) {
				--dummy;
			} else {
				YSVB_CHECK_1(q.i * mod2, >, D, "quotient of integer division times its dividor is not bigger in modulus than dividend.")
				--q.i;
			}
		} else {
			YSVB_CHECK_1(D, ==, 0, "tricotomy of integers")
			if (q.i * mod2 == dummy) {
				dummy = --dummy*mod2-D;
				--dummy;
			} else {
				++dummy;
			}
		}
	return *this = q*target-*this;
}

template<typename GID>
GaussInt<GID>  GaussInt<GID>::surplusdiv  (const GaussInt<GID>& target, GaussInt<GID>& q) const {
	GaussInt<GID> ret(*this);
	return ret.aspr(target, q);
}

template<typename GID>
GaussInt<GID>  GaussInt<GID>::operator + (const GaussInt<GID>& target) const
{
	GaussInt<GID> ret(*this);
	return ret += target;
}

template<typename GID>
GaussInt<GID>  GaussInt<GID>::operator - (const GaussInt<GID>& target) const
{
	GaussInt<GID> ret(*this);
	return ret -= target;
}

template<typename GID>
GaussInt<GID>  GaussInt<GID>::operator * (const GaussInt<GID>& target) const
{
	GaussInt<GID> ret(*this);
	return ret *= target;
}

template<typename GID>
GaussInt<GID>  GaussInt<GID>::times_conj (const GaussInt<GID>& target) const
{
	GaussInt<GID> ret(*this);
	return ret.at_conj(target);
}

template<typename GID>
GaussInt<GID>  GaussInt<GID>::operator / (const GaussInt<GID>& target) const
{
	GaussInt<GID> ret(*this);
	return ret /= target;
}

template<typename GID>
GaussInt<GID>& GaussInt<GID>::adbc		  (const GaussInt<GID>& target)
{
	GID holder	= this->r,
		mod2	= target.mod2();
		this->r = (this->r * target.r - this->i * target.i) / (mod2);
		this->i = (this->i * target.r + holder  * target.i) / (mod2);
	return *this;
}

template<typename GID>
GaussInt<GID>  GaussInt<GID>::div_by_conj (const GaussInt<GID>& target) const
{
	GaussInt<GID> ret(*this);
	return ret.adbc(target);
}	

template<typename GID>
GaussInt<GID>  GaussInt<GID>::operator % (const GaussInt<GID>& target) const
{
	GaussInt<GID> ret(*this);
	return ret %= target;
}

template<typename GID>
void  GaussInt<GID>::EuclidianDiv (const GaussInt<GID>& D, GaussInt<GID>& Q, GaussInt<GID>& R) const
{
	Q = this->times_conj(D);	Q.r /= D.mod2();	Q.i /= D.mod2();
	R = *this - Q*D;

	GaussInt<GID>	DD = D.times_conj(D),
					RR = R.times_conj(D),
					zero = GaussInt<GID>(0,0);

	GID m = GID(2)*(DD.mod2()), mc;	//minimum and minimum candidate

	GaussInt<GID> A, OQ = Q, HR, dummy;	//'Ajust' and 'Original quotient', Holder of Remainder

	GID rv, iv;
	for (rv = 1; rv >= -1; --rv) {
		for (iv = 1; iv >= -1; --iv) {
			A = GaussInt<GID>(rv, iv);
			A = (R != zero)?A:zero;
			if (	m > (	mc = (	(HR = (RR + A*DD).div_by_conj(D)).mod2()	)	)	)	{
				Q = OQ - A;
				R = HR;
				m = mc;
			} else {
				dummy = OQ - A;
				dummy = HR;
				mc = mc;
			}
		}
	}
}

template<typename GID>
GaussInt<GID>  GaussInt<GID>::GCD (const GaussInt<GID>& target) const
{
	GaussInt<GID> D, d, r, zero;	//Dividend, divisor, remainder and zero
	int count = 0;
	for (
		r = *this % (d = target),		zero = GaussInt<GID>(0,0);
		;
		D = d,		d = r,		r = (D % d)
	) {
		if (r == zero) {
			return d;
		}
	}
}

template<typename GID>
GaussInt<GID>  GaussInt<GID>::ModInv(const GaussInt<GID>& M) const
{
	GaussInt<GID> B, q, d, r, dummy;	//Multiplicative Coefficient of *this (in Bezout's theorem), Holder, Dividend, divisor, remainder, one and zero
	const GaussInt<GID> one(1, 0), mone(-1, 0), I(0, 1), mI(0, -1), zero(0, 0);
	for (
		M.EuclidianDiv(d = (*this%M), B, r)
	;;
		d = r,
		M.EuclidianDiv(d, q, r),
		B *= q,
		B.EuclidianDiv(M, dummy, B)
	) {
		if (
			r == one	|| 
			r == I		|| 
			r == mone	|| 
			r == mI
		) {
			(B * *this).EuclidianDiv(M, q, dummy);
			if (dummy.r == GID(1)) {
				if (dummy.r == GID(1)) {}
				if (dummy.r == GID(1)) {}
				YSVB_CHECK_1(dummy, ==, one, "Only the four unities are expected to possibly result here.")
				return B * one;
			} else if (dummy.r == GID(-1)) {
				if (dummy.r == GID(1)) {}
				YSVB_CHECK_1(dummy, ==, mone, "Only the four unities are expected to possibly result here.")
				return B * mone;
			} else if (dummy.i == GID(1)) {
				YSVB_CHECK_1(dummy, ==, I, "Only the four unities are expected to possibly result here.")
				return B * mI;
			} else {
				YSVB_CHECK_1(dummy, ==, mI, "Only the four unities are expected to possibly result here.")
				return B * I;
			}
		} else if (r == zero) {
			if ( d.mod2() == GID(1) ) {
				return d.conj();
			} else {
				return zero;				//error flag
			}
		}
	}
}

template<typename GID>
int GaussInt<GID>::is_prime(int reps) const
{
	t_int mymod2	= this->mod2();
	int ret			= mymod2.is_prime(reps);
	if (
		(this->gr() == t_int(1) || this->gr() == t_int(-1))
	&&
		(this->gi() == t_int(1) || this->gi() == t_int(-1))
	) {
		//waste time with dummy operations
		return 2;
	}
	mymod2 %= t_int(4);
	if (mymod2 == t_int(1)) {
		return (this->gr() != t_int(0) && this->gi() != t_int(0)) ?
		ret : 0;
	} else if (mymod2 == t_int(3)) {
		return (this->gr() == t_int(0) || this->gi() == t_int(0)) ?
		ret : 0;
	} else {
		return 0;
	}
}

template<typename GID>
bool GaussInt<GID>::operator == (const GaussInt<GID>& target) const
{
	return this->r == target.r && this->i == target.i;
}

template<typename GID>
bool GaussInt<GID>::operator != (const GaussInt<GID>& target) const
{
	return !(*this == target);
}

#endif