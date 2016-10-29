#include "gtest/gtest.h"
#include "modeq.cpp"
#include "../test.hpp"

TEST(GCD, One) {
	rep(i, 0, 100)
		EXPECT_EQ(gcd(llrand(), 1), 1);
}

TEST(GCD, Zero) {
	rep(i, 0, 1000) {
		ll a = max(llrand(), 1LL);
		EXPECT_EQ(gcd(a, 0), a);
	}
}

TEST(GCD, Commutative) {
	rep(i, 0, 1000) {
		ll a = max(llrand(), 1LL), b = llrand();
		EXPECT_EQ(gcd(a, b), gcd(b, a));
	}
}

TEST(GCD, ProofSmall) {
	rep(i, 0, 1000) {
		ll a = max(rand(), 1), b = rand();
		ll u, v;
		tie(u, v) = extgcd(a, b);
		EXPECT_EQ(gcd(a, b), a * u + b * v);
		EXPECT_EQ(a % gcd(a, b), 0);
		EXPECT_EQ(b % gcd(a, b), 0);
	}
}

TEST(GCD, ProofBig) {
	rep(i, 0, 1000) {
		ll a = max(llrand(), 1LL), b = llrand();
		ll u, v;
		tie(u, v) = extgcd(a, b);
		EXPECT_EQ(gcd(a, b), a * u + b * v);
		EXPECT_EQ(a % gcd(a, b), 0);
		EXPECT_EQ(b % gcd(a, b), 0);
	}
}

TEST(GCD, GcdIsBig) {
	rep(i, 0, 1000) {
		ll a = max(lrand48(), 1L), b = lrand48(), c = lrand48();
		ll u, v;
		tie(u, v) = extgcd(a * c, b * c);
		ll g = gcd(a * c, b * c);
		EXPECT_EQ(g, a * u * c + b * v * c);
		EXPECT_EQ((a * c) % g, 0);
		EXPECT_EQ((b * c) % g, 0);
	}

	EXPECT_EQ(gcd(2000000000000000000LL, 3000000000000000000LL), 1000000000000000000LL);
}
