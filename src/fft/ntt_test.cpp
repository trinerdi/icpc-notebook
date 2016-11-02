#include "gtest/gtest.h"
#include "ntt.cpp"

// P is so large we need unsigned long long
ull fastexpU(ull a, ull p, ull mod) {
    a = ((a % mod) + mod) % mod;
    ull res = 1 % mod;
    for (; p; a = (a * a) % mod, p /= 2)
        if (p % 2)
            res = (res * a) % mod;
            
    return res;
}

vector<ll> multiplyNaiveNTT(vector<ll> &p1, vector<ll> &p2) {
    int n = 1;
    while (n < p1.size() || n < p2.size()) n *= 2;
    n *= 2;
    
    vector<ll> want(n, 0);
    int s1 = p1.size(), s2 = p2.size();
    p1.resize(n), p2.resize(n);
    rep(i, 0, n) {
        rep(j, 0, i + 1) want[i] = (want[i] + P + p1[i - j] * p2[j]) % P;
    }
    p1.resize(s1), p2.resize(s2);
    return want;
}

TEST(NTT, Precomputation) {
    initNTT();
    rep(i, 0, EXP + 1) ASSERT_EQ(1, fastexpU(w[i], 1 << i, P));
    rep(i, 0, EXP + 1) ASSERT_EQ(1, (w[i] * wInv[i]) % P);
    rep(i, 0, EXP + 1) ASSERT_EQ(1, ((1 << i) * inv2[i]) % P);
}

TEST(NTT, MultipliesSimple) {
    initNTT();
    vector<ll> p1 = {8, 2, 1, 6, 3};
    vector<ll> p2 = {3, 4, 2};
    vector<ll> res = multiplyPolynomialsNTT(p1, p2);
    vector<ll> want = multiplyNaiveNTT(p1, p2);
    EXPECT_EQ(res, want);
    //(vector<ll> {24, 38, 27, 26, 35, 24, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0})
}

TEST(NTT, MultipliesOneEmpty) {
    initNTT();
    vector<ll> p1 = {3, 1, 2};
    vector<ll> p2 = {};
    vector<ll> res = multiplyPolynomialsNTT(p1, p2);
    EXPECT_EQ((vector<ll> {0, 0, 0, 0, 0, 0, 0, 0}), res);
}

TEST(NTT, MultipliesBothEmpty) {
    initNTT();
    vector<ll> p1 = {};
    vector<ll> p2 = {};
    vector<ll> res = multiplyPolynomialsNTT(p1, p2);
    EXPECT_EQ((vector<ll> {0, 0}), res);
}

TEST(NTT, Multiplies) {
    initNTT();
    rep(i, 0, 100) {
        vector<ll> p1(rand() % 100), p2(rand() % 100);
        rep(j, 0, p1.size()) p1[j] = rand() % P;
        rep(j, 0, p2.size()) p2[j] = rand() % P;
        vector<ll> want = multiplyNaiveNTT(p1, p2);
        EXPECT_EQ(want, multiplyPolynomialsNTT(p1, p2));
    }
}

TEST(NTT, Benchmark1e4) {
    initNTT();
    int n = 1e4;
    vector<ll> p1(n), p2(n);
    rep(j, 0, p1.size()) p1[j] = rand() % P;
    rep(j, 0, p2.size()) p2[j] = rand() % P;
    vector<ll> res = multiplyPolynomialsNTT(p1, p2);
    p1.resize(10), p2.resize(10);
    vector<ll> want = multiplyNaiveNTT(p1, p2);
    want.resize(10), res.resize(10); // check the first few
    EXPECT_EQ(want, res);
}
