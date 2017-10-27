#include "gtest/gtest.h"
#include "dinic.cpp"

TEST(Dinic, OneEdge) {
    Dinic d(2);
    d.addEdge(0, 1, 123);
    EXPECT_EQ(d.getFlow(0, 1), 123);
}

TEST(Dinic, OneEdgeReverse) {
    Dinic d(2);
    d.addEdge(0, 1, 123);
    EXPECT_EQ(d.getFlow(1, 0), 0);
}

TEST(Dinic, SelfLoop) {
    Dinic d(2);
    d.addEdge(0, 0, 123);
    d.addEdge(1, 1, 123);
    d.addEdge(0, 1, 123);
    EXPECT_EQ(d.getFlow(0, 1), 123);
}

TEST(Dinic, MultipleEdges) {
    Dinic d(2);
    d.addEdge(0, 1, 100);
    d.addEdge(0, 1, 23);
    EXPECT_EQ(d.getFlow(0, 1), 123);
}

TEST(Dinic, BidirectionalEdges) {
    Dinic d(2);
    d.addEdge(0, 1, 100);
    d.addEdge(1, 0, 23);
    EXPECT_EQ(d.getFlow(0, 1), 100);
    EXPECT_EQ(d.getFlow(1, 0), 23);
}

TEST(Dinic, Capacities) {
    // We construct a graph where it is necessary to consider residual capacities
    Dinic d(8);
    vector<vector<int>> edges = {
        {0, 1, 1},
        {1, 2, 1},
        {2, 3, 1},
        {0, 4, 2},
        {4, 5, 2},
        {5, 2, 2},
        {2, 1, 1}, // the important reverse edge
        {1, 6, 2},
        {6, 7, 2},
        {7, 3, 2},
    };
    for (auto &e : edges) {
        d.addEdge(e[0], e[1], e[2]);
    }
    
    EXPECT_EQ(d.getFlow(0, 3), 3);
}

TEST(Dinic, LargeFlow) {
    Dinic d(2);
    rep(i, 0, 100) {
        d.addEdge(0, 1, 100000000000ll);
    }
    EXPECT_EQ(d.getFlow(0, 1), 10000000000000ll);
}

// from: https://www.topcoder.com/community/data-science/data-science-tutorials/maximum-flow-section-1/
TEST(Dinic, Graph1) {
    Dinic d(7);
    d.addEdge(0, 1, 3);
    d.addEdge(0, 2, 1);
    d.addEdge(1, 3, 3);
    d.addEdge(2, 3, 5);
    d.addEdge(2, 5, 4);
    d.addEdge(3, 4, 2);
    d.addEdge(5, 6, 2);
    d.addEdge(6, 4, 3);
    ll f = d.getFlow(0, 4);
    
    EXPECT_EQ(3, f);
    // e[2n] corresponds to edge n, e[2n+1] to the backwards edge
    EXPECT_EQ(2, d.e[0].flow);
    EXPECT_EQ(1, d.e[2].flow);
    EXPECT_EQ(2, d.e[4].flow);
    EXPECT_EQ(0, d.e[6].flow);
}

// from: http://www.spoj.com/problems/FASTFLOW/
TEST(Dinic, Graph2) {
    Dinic d(5);
    vector<vector<int>> edges = {
        {1, 2, 3},
        {2, 3, 4},
        {3, 1, 2},
        {2, 2, 5},
        {3, 4, 3},
        {4, 3, 3},
    };
    for (auto &e : edges) {
        d.addEdge(e[0], e[1], e[2]);
        d.addEdge(e[1], e[0], e[2]);
    }
    
    EXPECT_EQ(5, d.getFlow(1, 4));
}

TEST(Dinic, BenchmarkV100E10000) {
    srand(1);
    int n = 100;
    int m = 30000;
    int range = 1000;
    Dinic d(n);
    rep(i, 0, m) {
        d.addEdge(rand() % n, rand() % n, range + rand() % range);
    }
    ll flow = d.getFlow(0, n - 1);
}


TEST(Dinic, BenchmarkChainV1000E10000) {
    srand(1);
    int n = 1000;
    int m = 10000;
    int range = 1000;
    int perEdge = m / n; // yes, it's not exact
    Dinic d(n);
    rep(i, 0, n - 1) {
        rep(j, 0, perEdge) {
            d.addEdge(i, i + 1, range + rand() % range);
        }
    }
    ll flow = d.getFlow(0, n - 1);
    EXPECT_EQ(12375, flow);
}
