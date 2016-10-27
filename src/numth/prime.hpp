#include "misc.hpp"

/* The Sieve of Eratosthenes for finding primes up to m (inclusive)
 * Time complexity: O(n log log n), space complexity: O(n) */
vector<int> sieve(int m) {
	m++;
	vector<bool> is_p(m, true);
	vector<int> primes;
	rep(i, 2, m) {
		if (!is_p[i])
			continue;

		primes.push_back(i);
		for (int j = 2 * i; j < m; j += i)
			is_p[j] = false;
	}

	return primes;
}
