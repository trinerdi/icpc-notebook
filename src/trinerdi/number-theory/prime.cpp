/**
 * Name: Primality test
 * Author: Richard Hladik
 * Description: Deterministic Miller-Rabin primality test, works for $p \leq 2^{32}$.
 * Time: $O(\log p)$
 */
#include "fastexp.cpp"

bool isprime(ll p) {
	if (p == 2 || p == 7 || p == 61)
		return true;
	if (p < 2 || !(p % 2))
		return false;
	int cnt = 0;
	ll d = p - 1;
	while (d % 2 == 0)
		d /= 2, cnt++;
	/// It's been proven testing only these witnesses suffices for all p that
	/// concern us
	for (ll a: (vector<ll>){2, 7, 61}) {
		bool passed = false;
		ll ad = fastexp(a, d, p);
		passed |= ad == 1;
		for (int i = 0; i < cnt; i++, ad = (ad * ad) % p)
			passed |= ad == p - 1;
		if (!passed)
			return false;
	}
	return true;
}
