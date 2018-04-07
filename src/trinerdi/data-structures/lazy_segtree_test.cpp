#include "gtest/gtest.h"
#include "lazy_segtree.cpp"

struct Naive {
    vector<ll> vals;
    
    Naive(int n) : vals(n) {}
    
    void rangeUpdate(int fr, int to, ll x) {
        rep(i, fr, to) {
            vals[i] += x;
        }
    }
    
    ll rangeQuery(int fr, int to) const {
        ll best = 1e18;
        rep(i,fr,to) best = min(best, vals[i]);
        return best;
    }
};

void compare(Segtree& a, Naive& b) {
    vector<ll> va, vb;
    rep(i, 0, b.vals.size()) {
        va.push_back(a.rangeQuery(i,i+1));
        vb.push_back(b.rangeQuery(i,i+1));
    }
    EXPECT_EQ(va, vb);
}

TEST(LazySegtree, BasicUsage) {
    int n = 10;
    Segtree tree(0,n);
    Naive naive(n);
    compare(tree, naive);

    vector<vector<int>> updates = {
        {2, 5, 2},
        {0, 1, 1},
        {0, 10, 4},
        {4, 8, 1},
    };
    
    for (auto &u : updates) {
        tree.rangeUpdate(u[0], u[1], u[2]);
        naive.rangeUpdate(u[0], u[1], u[2]);
        compare(tree, naive);
    }
}

TEST(LazySegtree, LotsOfQueries) {
    int n = 100;
    Segtree tree(0,n);
    Naive naive(n);
    compare(tree, naive);
    
    rep(it1,0,100) {
        rep(it2,0,10) {
            int fr = rand() % (n-1);
            int to = rand() % (n-1-fr) + 1 + fr;
            int val = rand() % 100;

            tree.rangeUpdate(fr, to, val);
            naive.rangeUpdate(fr, to, val);
        }
        compare(tree, naive);
    }
}


TEST(LazySegtree, BenchmarkN100000Q100000) {
    int n = 100000;
    int q = 100000;
    int margin = 50;

    Segtree tree(0,n);
    ll tot = 0;
    rep(qi, 0, q) {
        if (qi % 2 == 0) {
            int fr = rand() % margin;
            int to = n - rand() % margin;
            tree.rangeQuery(fr, to);
        } else {
            int fr = rand() % margin;
            int to = n - rand() % margin;
            ll val = rand() % 1000000;
            tot += val;
            tree.rangeUpdate(fr, to, val);
        }
    }
    EXPECT_EQ(tot, tree.rangeQuery(n/2, n/2+1));
}
