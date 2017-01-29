#ifndef __pub_key__
#define __pub_key__

#include <sstream>
#include <string>
#include <public_msg.hpp>
#include <private_data.hpp>
class Encryptor;

class Pub_Key
{
	friend	Encryptor;
#ifdef __PRIVATE_KEY_HPP__
	friend	Pri_Key;
#endif

#ifdef __DBG__
	public:
#endif
	t_meta_int			_k;
	t_meta_int			_m;
	t_meta_int			_p;
	t_public_msg		_giv;	//Gauss t_meta_integers vector (that technically is actually a std::deque
	std::string			_name;
	Pub_Key();
	Pub_Key(t_meta_int k, t_meta_int m, t_meta_int p, t_public_msg	giv, std::string name = "SRVB_key");
public:
	// ~Pub_key();
	t_public_msg	encode(const t_private_data& block) const;
	std::string		summary() const;
friend std::ostream& operator << (std::ostream& os, const Pub_Key& sk);
friend std::istream& operator >> (std::istream& key_file, Pub_Key& sk);

};

#endif