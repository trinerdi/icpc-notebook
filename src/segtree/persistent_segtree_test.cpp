#include "gtest/gtest.h"
#include "persistent_segtree.cpp"

struct Naive {
    vector<ll> vals;
    
    Naive(int n) : vals(n) {}
    
    Naive* rangeUpdate(int fr, int to, ll x) const {
        auto res = new Naive(vals.size());
        res->vals = vals;
        rep(i, fr, to) {
            res->vals[i] += x;
        }
        return res;
    }
    
    ll pointQuery(int i) const {
        return vals[i];
    }
};

vector<ll> getAllValues(const Segtree* s) {
    vector<ll> res;
    rep(i, s->l, s->r) {
        res.push_back(s->pointQuery(i));
    }
    return res;
}

void compare(const Segtree* a, const Naive* b) {
    vector<ll> va, vb;
    rep(i, 0, b->vals.size()) {
        va.push_back(a->pointQuery(i));
        vb.push_back(b->pointQuery(i));
    }
    EXPECT_EQ(va, vb);
}

TEST(PersistentSegtree, BasicUsage) {
    int n = 10;
    vector<Segtree*> trees;
    vector<Naive*> naives;
    trees.push_back(new Segtree(0, n));
    naives.push_back(new Naive(n));
    compare(trees.back(), naives.back());
    
    vector<vector<int>> updates = {
        {2, 5, 2},
        {0, 1, 1},
        {0, 10, 4},
        {4, 8, 1},
    };
    
    for (auto &u : updates) {
        naives.push_back(naives.back()->rangeUpdate(u[0], u[1], u[2]));
        trees.push_back(trees.back()->rangeUpdate(u[0], u[1], u[2]));
        compare(trees.back(), naives.back());
    }
    // Check that the updates are non-destructive
    rep(i, 0, trees.size()) {
        compare(trees[i], naives[i]);
    }
}

TEST(PersistentSegtree, Branching) {
    int n = 3;
    vector<Segtree*> trees;
    trees.push_back(new Segtree(0, n));
    trees.push_back(trees[0]->rangeUpdate(0, 2, 1));
    trees.push_back(trees[0]->rangeUpdate(1, 3, 2));
    trees.push_back(trees[1]->rangeUpdate(1, 3, 2));
    EXPECT_EQ(getAllValues(trees[1]), vector<ll>({1, 1, 0}));
    EXPECT_EQ(getAllValues(trees[2]), vector<ll>({0, 2, 2}));
    EXPECT_EQ(getAllValues(trees[3]), vector<ll>({1, 3, 2}));
}

TEST(PersistentSegtree, BenchmarkN100000Q100000) {
    int n = 100000;
    int q = 100000;
    int margin = 50;
    
    vector<Segtree*> trees;
    trees.push_back(new Segtree(0, n));
    ll tot = 0;
    rep(qi, 0, q) {
        if (qi % 2 == 0) {
            auto t = trees[rand() % trees.size()];
            t->pointQuery(rand() % n);
        } else {
            int fr = rand() % margin;
            int to = n - rand() % margin;
            ll val = rand() % 1000000;
            tot += val;
            trees.push_back(trees.back()->rangeUpdate(fr, to, val));
        }
    }
    EXPECT_EQ(tot, trees.back()->pointQuery(n / 2));
}
