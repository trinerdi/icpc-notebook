#include "gtest/gtest.h"
#include "lca.cpp"

void generateTree(int n) {
    rep(i, 0, n) g[i].clear();
    rep(a, 1, n) {
        int b = rand() % a;
        g[a].push_back(b);
        g[b].push_back(a);
    }
}

TEST(LCA, InitialDFS) {
    int n = 50;
    rep(tests, 0, 10) {
        generateTree(n);
        function<void(int, int, int)> dfs = [&](int a, int from, int depth) {
            EXPECT_EQ(depth, d[a]);
            EXPECT_EQ(pred[a][0], from);
            for (auto b : g[a]) {
                if (b == from) continue;
                dfs(b, a, depth + 1);
            }
        };
        rep(i, 0, n) {
            initLCA(i, n);
            dfs(i, -1, 0);
        }
    }
}

TEST(LCA, Predecessors) {
    int n = 50;
    rep(tests, 0, 10) {
        generateTree(n);
        initLCA(0, n);
        rep(a, 0, n) {
            int cur = a;
            rep(l, 0, LOG) {
                if (pred[a][l] == -1) {
                    EXPECT_LT(d[cur], (1 << l));
                } else {
                    int move = l ? (1 << (l - 1)) : 1; // 1 1 2 4 8 ...
                    rep(i, 0, move) cur = pred[cur][0];
                    EXPECT_EQ(cur, pred[a][l]);
                }
            }
        }
    }
}

TEST(LCA, LCA) {
    int n = 50;
    rep(tests, 0, 10) {
        generateTree(n);
        initLCA(0, n);
        rep(a, 0, n) rep(b, 0, n) {
            int aa = a, bb = b;
            while (aa != bb) {
                if (d[aa] >= d[bb]) {
                    aa = pred[aa][0];
                } else {
                    bb = pred[bb][0];
                }
            }
            EXPECT_EQ(aa, lca(a, b));
        }
    }
}

// making the graph a chain does not seem to slow the algorithm down (on the contrary, actually)
TEST(LCA, BenchmarkN100000Q100000) {
    srand(1);
    int n = 100000;
    int q = 100000;
    generateTree(n);
    initLCA(0, n);
    rep(i, 0, q) {
        lca(rand() % n, rand() % n);
    }
}
