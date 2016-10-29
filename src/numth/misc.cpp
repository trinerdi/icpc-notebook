#include "../base.hpp"

/* Fast exponentiation modulo mod
 * Time complexity: O(log p), space complexity: O(1) */
ll fastexp(ll a, ll p, ll mod) {
	a = ((a % mod) + mod) % mod;
	ll res = 1 % mod;
	for (; p; a = (a * a) % mod, p /= 2)
		if (p % 2)
			res = (res * a) % mod;

	return res;
}
