#include "gtest/gtest.h"
#include "heavylight.cpp"

void generateTree(int n) {
    rep(a, 1, n) {
        int b = rand() % a;
        g[a].push_back(b);
        g[b].push_back(a);
    }
}

void reset(int n) {
    rep(i, 0, n) g[i].clear();
    chains.clear();
}

TEST(HeavyLight, Chains) {
    srand(1);
    int n = 50;
    rep(tests, 0, 10) {
        reset(n);
        generateTree(n);
        initHLD(0, n);
        for (auto &c : chains) {
            per(i, 1, c.size()) {
                EXPECT_EQ(c[i - 1], pred[c[i]][0]);
            }
        }
    }
}

TEST(HeavyLight, Queries) {
    srand(1);
    int n = 10;
    rep(tests, 0, 10) {
        reset(n);
        generateTree(n);
        initHLD(0, n);
        rep(a, 0, n) rep(b, a, n) {
            query(a, b);
        }
        break;
    }
}
