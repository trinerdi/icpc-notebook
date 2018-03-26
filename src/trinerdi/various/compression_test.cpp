#include "gtest/gtest.h"
#include "compression.cpp"

vector<ll> populateVector(int n) {
    vector<ll> v;
    rep(i,0,n) {
        v.push_back(rand() - RAND_MAX/2);
    }
    return v;
}

TEST(COMPRESSION, ManualCase) {
    vector<ll> v = {-3, 8, 2, 4, 4, 2, 4, -10};
    compress(v);
    EXPECT_EQ(v, vector<ll>({1, 4, 2, 3, 3, 2, 3, 0}));
}

void check(vector<ll>& v) {
    vector<ll> v0 = v;
    compress(v);
    vector<bool> seen(v.size(), false);
    for(auto x : v) {
        EXPECT_LE(0, x);
        EXPECT_LT(x, v.size());
        seen[x] = true;
    }
    rep(i,0,v.size()-1) {
        if(!seen[i]) {
            EXPECT_EQ(seen[i], seen[i+1]);
        }
    }
    rep(i,0,v.size()) rep(j,0,v.size()) {
        EXPECT_EQ(v[i] < v[j], v0[i] < v0[j]);
    }
}

TEST(COMPRESSION, Works) {
    srand(123);
    rep(i,0,100) {
        const int SZ = 100;
        auto v = populateVector(SZ);
        check(v);
    }
}

TEST(COMPRESSION, WorksDuplicate) {
    srand(123);
    rep(i,0,100) {
        const int SZ = 50;
        auto v = populateVector(SZ);
        rep(i,0,SZ) {
            int times = rand() % 5;
            rep(j,0,times) v.push_back(v[i]);
        }
        random_shuffle(v.begin(), v.end());
        check(v);
    }
}
