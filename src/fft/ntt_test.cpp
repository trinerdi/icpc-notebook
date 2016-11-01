#include "gtest/gtest.h"
#include "ntt.cpp"

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

TEST(NTT, MultipliesSimple) {
    initNTT();
    vector<ll> p1 = {8, 2, 1, 6, 3};
    vector<ll> p2 = {3, 4, 2};
    vector<ll> res = multiplyPolynomialsNTT(p1, p2);
    vector<ll> want = multiplyNaiveNTT(p1, p2);
    EXPECT_EQ(res, want);
    //(vector<ll> {24, 38, 27, 26, 35, 24, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0})
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