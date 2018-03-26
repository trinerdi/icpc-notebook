/**
 * Author: Richard Hladik
 * Description: Returns $a^p\ \%\ mod$.
 * Time: $O(\log p)$
 */
#include "../base.hpp"

ll fastexp(ll a, ll p, ll mod) {
	a = ((a % mod) + mod) % mod; /// so many mod's because of corner cases
	ll res = 1 % mod;
	for (; p; a = (a * a) % mod, p /= 2)
		if (p % 2)
			res = (res * a) % mod;
	return res;
}
