#include "gtest/gtest.h"
#include "prime.cpp"

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



TEST(ISPRIME, Negative) {
	vector<bool> res = {isprime(-1), isprime(-5237), isprime(-15723953), isprime(-2)};
	EXPECT_EQ(res, (vector<bool> {false, false, false, false}));
}

TEST(ISPRIME, BelowTwo) {
	EXPECT_EQ(isprime(0), false);
	EXPECT_EQ(isprime(1), false);
}

vector<bool> run(vector<int> a) {
	vector<bool> ret;
	for (int b: a)
		ret.push_back(isprime(b));

	return ret;
}

TEST(ISPRIME, Constants) {
	EXPECT_EQ(run({2, 3, 7, 61}), (vector<bool> {true, true, true, true}));
}

TEST(ISPRIME, Hundreds) {

	EXPECT_EQ(run({641, 642, 643, 644, 645, 646, 647}), (vector<bool> {true, false, true, false, false, false, true}));
}

TEST(ISPRIME, Millions) {
	EXPECT_EQ(run({1000847, 1000848, 1000849, 1000850, 1000851}), (vector<bool> {true, false, true, false, false}));
}

TEST(ISPRIME, Billions) {
	EXPECT_EQ(run({2000000086, 2000000087, 2000000088, 2000000089}), (vector<bool> {false, true, false, true}));
}


void consistency(int n) {
	vector<bool> sieved = sieve(n), tested;
	int cna = 0, cnb = 0;
	for (int i=0; i<=n; i++) {
		tested.push_back(isprime(i));
		cna += tested[i], cnb += sieved[i];
	}

	EXPECT_EQ(cna, cnb);
	EXPECT_EQ(sieved, tested);
}

TEST(PRIMES, Consistent) {
	consistency(1000);
}

TEST(PRIMES, Benchmark) {
	consistency(100000);
}
