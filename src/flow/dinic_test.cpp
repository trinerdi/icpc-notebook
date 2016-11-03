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
    EXPECT_EQ(d.getFlow(1, 0), 123);
}

TEST(Dinic, MultipleEdges) {
    Dinic d(2);
    d.addEdge(0, 1, 100);
    d.addEdge(0, 1, 23);
    EXPECT_EQ(d.getFlow(1, 0), 123);
}

TEST(Dinic, LargeFlow) {
    Dinic d(2);
    rep(i, 0, 100) {
        d.addEdge(0, 1, 100000000000ll);
    }
    EXPECT_EQ(d.getFlow(1, 0), 10000000000000ll);
}

// from: https://www.topcoder.com/community/data-science/data-science-tutorials/maximum-flow-section-1/
// here we consider undirected (unlike the example)
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
    
    EXPECT_EQ(4, f);
    EXPECT_EQ(3, d.e[0].flow);
    EXPECT_EQ(1, d.e[1].flow);
    EXPECT_EQ(3, d.e[2].flow);
    EXPECT_EQ(-1, d.e[3].flow);
}

// from: http://www.spoj.com/problems/FASTFLOW/
TEST(Dinic, Graph2) {
    Dinic d(5);
    d.addEdge(1, 2, 3);
    d.addEdge(2, 3, 4);
    d.addEdge(3, 1, 2);
    d.addEdge(2, 2, 5);
    d.addEdge(3, 4, 3);
    d.addEdge(4, 3, 3);
    
    EXPECT_EQ(5, d.getFlow(1, 4));
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
