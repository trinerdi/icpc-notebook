#include "../base.hpp"
#include "prime.hpp"

int main() {
	int N = 2e6;
	vector<bool> primes = sieve(N);
	int cnt = 0;
	for (int p: primes)
		cnt += p;

	printf("%d %d %d %d %d\n", cnt, (int) primes[0], (int) primes[1], (int) primes[1999993], (int) primes[1999994]);
	// 148933 0 0 1 0

	// Check if the sieve algorithm is consistent with isprime
	rep(i, 0, N + 1)
		if (primes[i] != isprime(i))
			printf("Inconsistency: %d: sieve %d, isprime %d\n", i, (int)primes[i], (int)isprime(i));
}
