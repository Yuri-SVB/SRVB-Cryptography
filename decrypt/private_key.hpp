#ifndef __PRIVATE_KEY_HPP__
#define __PRIVATE_KEY_HPP__

#include <sstream>
#include <string>
#include <def.hpp>
#include <private_msg.hpp>
#include <public_msg.hpp>
#include <public_key.hpp>
#include <public_key.cpp>

class Pri_Key {
#ifdef __DBG__
public:
#endif
	t_meta_int			_k;
	t_meta_int			_m;
	t_meta_int			_p;
	t_public_int		_alpha;
	t_int				_alpha_2;
	t_public_int		_theta;
	t_public_int		_theta_ima;	//theta inverted mod alpha
	t_private_msg		_his;			//hyper increasing sequence
	t_int				_rdtgiar;		//real dividend that gives i as remainder
	std::string			_name;
static t_int		 _get_rdtgiar_from_alpha(t_public_int alpha);
public:
	void			s_k(t_meta_int k)		{	_k = k;	}
	t_meta_int		g_k()		const		{	return _k;	}
	void			s_m(t_meta_int m)		{	_m = m;	}
	t_meta_int		g_m()		const		{	return _m;	}
	void			s_p(t_meta_int p)		{	_p = p;	}
	t_meta_int		g_p()		const		{	return _p;	}
	void			s_alpha(t_public_int a)	{	_alpha_2 = ((_alpha = a)*a).gr();	}
	t_public_int	g_alpha()	const		{	return _alpha;	}
	t_public_int	g_alpha_2()	const		{	return _alpha_2;	}
	void			s_theta(t_public_int t)	{	_theta = t;	_theta_ima = _theta.ModInv(_alpha);	}
	t_public_int	g_theta()	const		{	return _theta;	}
	void			s_his(t_private_msg m)	{	_his = m;	}
	t_private_msg	g_his()		const		{	return _his;	}
	bool			is_valid() const;
	t_private_data	decode(const t_public_msg& pub_msg) const;
	t_private_msg	pub_to_his(const t_public_msg& pub_msg) const;
	t_private_data	his_to_dt(t_private_msg node) const;
	t_private_msg	dt_to_his(const t_private_data& block) const;
	Pri_Key();
	Pri_Key(t_meta_int k, t_meta_int m, t_meta_int p, t_public_int alpha, t_public_int theta, t_private_msg his, std::string name = "SRVB_key");
	Pub_Key			get_Public() const;
	std::string		summary() const;
friend std::ostream& operator << (std::ostream& os, const Pri_Key& sk);
friend std::istream& operator >> (std::istream& key_file, Pri_Key& sk);

};

#endif