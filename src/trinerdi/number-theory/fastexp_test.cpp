#include "gtest/gtest.h"
#include "fastexp.cpp"
#include "../test.hpp"

TEST(FASTEXP, BaseZero) {
	EXPECT_EQ((vector<ll> {fastexp(0, 1, 5), fastexp(0, 10, 51234), fastexp(0, 205123, 51235603), fastexp(0, 523182342, 729384275)}), (vector<ll> {0, 0, 0, 0}));
}

TEST(FASTEXP, PowerZero) {
	EXPECT_EQ((vector<ll> {fastexp(1, 0, 5), fastexp(10, 0, 62853), fastexp(1247393725, 0, 523492342)}), (vector<ll> {1, 1, 1}));
}

TEST(FASTEXP, ZeroZero) {
	EXPECT_EQ(fastexp(0, 0, 192837583), ((ll) 1));
}

TEST(FASTEXP, ModOne) {
	EXPECT_EQ(fastexp(523819523, 839275932, 1), ((ll) 0));
	EXPECT_EQ(fastexp(52321524, 0, 1), ((ll) 0));
}

TEST(FASTEXP, BigExp) {
	EXPECT_EQ(fastexp(159235238, 159328549238105492LL, 529385237), 481182887LL);
}

TEST(FASTEXP, BigBoth) {
	EXPECT_EQ(fastexp(182934582734019238LL, 529384572361245923LL, 528391432), 300567920LL);
}

TEST(FASTEXP, Negative) {
	rep(i, 0, 5000){
		ll a = llrand(), b = llrand(), c = max(rand(), 1);
		EXPECT_EQ(fastexp(a, b, c), fastexp((a % c) - c, b, c));
	}
}

TEST(FASTEXP, Benchmark1e5) {
	rep(i, 0, 100000)
		fastexp(llrand(), llrand(), max(rand(), 1));
}
