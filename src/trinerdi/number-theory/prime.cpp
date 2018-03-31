/**
 * Name: Prime sieve, primality test
 * Author: Richard Hladik
 * Description: Sieve of Eratosthenes for finding primes up to m (inclusive).
 *  Deterministic Miller-Rabin primality test, works for $p \leq 2^{32}$.
 * Time: Sieve: $O(n \log \log n)$, Miller-Rabin: $O(\log p)$
 */
#include "misc.cpp"

vector<bool> sieve(int m) {
	m++;
	vector<bool> is_p(m, true);
	is_p[0] = is_p[1] = false;
	rep(i, 2, m)
		if (is_p[i])
			for (int j = 2 * i; j < m; j += i)
				is_p[j] = false;
	return is_p;
}

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
