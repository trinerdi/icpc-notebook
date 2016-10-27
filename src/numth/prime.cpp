#include "../base.hpp"
#include "prime.hpp"

int main() {
	int N = 2e6;
	vector <int> primes = sieve(N);
	printf("%d %d %d %d\n", primes.size(), primes[0], primes[1], primes.back());
	// 148933 2 3 1999993
	primes.push_back(N + 1);
	int pos = 0;

	// Check if the sieve algorithm is consistent with isprime
	rep(i, 1, N + 1) {
		while (primes[pos] < i)
			pos++;

		if ((primes[pos] == i) != isprime(i))
			printf("Inconsistency: %d: sieve %d, isprime %d\n", i, (int)(primes[pos] == i), (int)(isprime(i)));
	}
}
