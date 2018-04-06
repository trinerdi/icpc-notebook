#include "gtest/gtest.h"
#include "sieve.cpp"

TEST(SIEVE, BelowTwo) {
	vector<bool> primes = sieve(2);
	EXPECT_EQ((vector<bool> {false, false, true}), primes);
}

TEST(SIEVE, SizeIsInclusive) {
	vector<bool> primes = sieve(3000);
	EXPECT_EQ(primes.size(), 3001);
}

TEST(SIEVE, LastIsComposite) {
	vector<bool> primes = sieve(3000);
	EXPECT_EQ(primes[3000], false);
}

TEST(SIEVE, LastIsPrime) {
	vector<bool> primes = sieve(2999);
	EXPECT_EQ(primes[2999], true);
}

TEST(SIEVE, CutEquals) {
	vector<bool> primes = sieve(3000);
	vector<bool> bigger = sieve(30000);
	bigger.resize(3001);
	EXPECT_EQ(primes, bigger);
}
