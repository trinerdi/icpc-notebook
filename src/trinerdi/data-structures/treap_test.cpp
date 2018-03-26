#include "gtest/gtest.h"
#include "treap.cpp"

TEST(Treap, BenchmarkInsertAndIndex1e5) {
    Treap* t = NULL;
    int n = 100000; // n = 10^6 takes about 5 seconds on my machine
    unordered_set<ll> used; // Elements must be different for the test to work
    for (int i = 0; i < n; i++) {
        ll x = rand();
        while (used.count(x)) x = rand();
        used.insert(x);
        insert(t, x);
    }
    ll last = 0;
    for (int i = 0; i < n; i++) {
        ll x = getKth(t, i);
        EXPECT_GT(x, last);
        EXPECT_EQ(indexOf(t, x), i);
        last = x;
    }
}
