#ifndef __DEF_DEC__
#define __DEF_DEC__

#include <set>
#include <deque>
#include <vector>

class Pri_Key;
class Pub_Key;

#ifdef __DBG__
class TDD;
class PublicKeyTDD;
class Encode;
#endif

class	SRVBBI;
template<typename GID>
class	GaussInt;

typedef long int t_meta_int;
#define ATO_MI	atol

class	t_int;
typedef GaussInt<t_int>				t_public_int;

class	t_public_msg;
class	t_private_msg;
class	t_private_data;

#include <big_int.hpp>
#include <intgauss.hpp>
#include <intgauss.cpp>

#endif