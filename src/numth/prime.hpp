#include "misc.hpp"

/* The Sieve of Eratosthenes for finding primes up to m (inclusive)
 * Time complexity: O(n log log n), space complexity: O(n) */
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

/* Deterministic version of the Miller-Rabin primality test, works for p < 3e9
 * Time complexity: O(log p), space complexity: O(1) */
bool isprime(ll p) {
	if (p < 2)
		return false;

	if (p % 2 == 0)
		return p == 2;

	if (p == 7 || p == 61)
		return true;

	int cnt = 0;
	ll d = p - 1;
	while (d % 2 == 0)
		d /= 2, cnt++;

	// It's been proven testing only these witnesses suffices for p < 4e9
	for (ll a: (vector<ll>){2, 7, 61}) {
		bool passed = false;
		ll ad = fastexp(a, d, p);
		if (ad == 1)
			passed = true;

		for (int i = 0; i < cnt; i++, ad = (ad * ad) % p)
			if (ad == p - 1)
				passed = true;

		if (!passed)
			return false;
	}

	return true;
}
