#include "gtest/gtest.h"
#include "fft.cpp"

vector<ll> multiplyNaive(vector<ll> &p1, vector<ll> &p2) {
    int n = 1;
    while (n < p1.size() || n < p2.size()) n *= 2;
    n *= 2;
    
    vector<ll> want(n, 0);
    int s1 = p1.size(), s2 = p2.size();
    p1.resize(n), p2.resize(n);
    rep(i, 0, n) {
        rep(j, 0, i + 1) want[i] += p1[i - j] * p2[j];
    }
    p1.resize(s1), p2.resize(s2);
    return want;
}


TEST(FFT, MultipliesSimple) {
    vector<ll> p1 = {8, 2, 1, 6, 3};
    vector<ll> p2 = {3, 4, 2};
    vector<ll> res = multiplyPolynomials(p1, p2);
    EXPECT_EQ((vector<ll> {24, 38, 27, 26, 35, 24, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0}), res);
}

TEST(FFT, MultipliesNegative) {
    vector<ll> p1 = {3, 1, -2, 2};
    vector<ll> p2 = { -5, 1};
    vector<ll> res = multiplyPolynomials(p1, p2);
    EXPECT_EQ((vector<ll> { -15, -2, 11, -12, 2, 0, 0, 0}), res);
}

TEST(FFT, MultipliesOneEmpty) {
    vector<ll> p1 = {3, 1, 2};
    vector<ll> p2 = {};
    vector<ll> res = multiplyPolynomials(p1, p2);
    EXPECT_EQ((vector<ll> {0, 0, 0, 0, 0, 0, 0, 0}), res);
}

TEST(FFT, MultipliesBothEmpty) {
    vector<ll> p1 = {};
    vector<ll> p2 = {};
    vector<ll> res = multiplyPolynomials(p1, p2);
    EXPECT_EQ((vector<ll> {0, 0}), res);
}

TEST(FFT, Multiplies) {
    rep(i, 0, 30) {
        vector<ll> p1(30 + rand() % 30), p2(30 + rand() % 30);
        rep(j, 0, p1.size()) p1[j] = rand() % 20000000 - 10000000;
        rep(j, 0, p2.size()) p2[j] = rand() % 20000000 - 10000000;
        vector<ll> want = multiplyNaive(p1, p2);
        EXPECT_EQ(want, multiplyPolynomials(p1, p2));
    }
}

TEST(FFT, Benchmark1e4) {
    int n = 1e4;
    int range = 1e5; //numbers from -range to range
    vector<ll> p1(n), p2(n);
    rep(j, 0, p1.size()) p1[j] = rand() % (2 * range) - range;
    rep(j, 0, p2.size()) p2[j] = rand() % (2 * range) - range;
    vector<ll> res = multiplyPolynomials(p1, p2);
    p1.resize(10), p2.resize(10);
    vector<ll> want = multiplyNaive(p1, p2);
    want.resize(10), res.resize(10);
    EXPECT_EQ(want, res);
}
