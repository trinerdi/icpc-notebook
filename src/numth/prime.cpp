#include "misc.cpp"

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

/* Deterministic version of the Miller-Rabin primality test, works for p <=
 * 2<<31 (for greater p, signed ll overflow may occur).
 * Time complexity: O(log p), space complexity: O(1) */
bool isprime(ll p) {
	if (p == 2 || p == 7 || p == 61)
		return true;

	if (p < 2 || !(p % 2))
		return false;

	int cnt = 0;
	ll d = p - 1;
	while (d % 2 == 0)
		d /= 2, cnt++;

	// It's been proven testing only these witnesses suffices for all p that
	// concern us
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
