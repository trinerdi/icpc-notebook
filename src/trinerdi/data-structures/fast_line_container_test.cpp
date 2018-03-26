#include "gtest/gtest.h"
#include "fast_line_container.cpp"

ll naiveQuery(vector<Line>& lines, ll x) {
    ll res = -INF;
    for(auto& l : lines) {
        res = max(res, l.val(x));
    }
    return res;
}

int randrange(int fr, int to) {
    return rand() % (to - fr) + fr;
}

void sortLines(vector<Line>& lines) {
    sort(lines.begin(), lines.end(),
        [](const Line& a, const Line& b) {
            return a.k < b.k;
        });
}

vector<Line> genLines(int n, int kf, int kt, int mf, int mt) {
    vector<Line> res;
    rep(it, 0, n) {
        res.push_back({randrange(kf, kt), randrange(mf, mt), 0});
    }
    return res;
}

void queryTest(int absBound) {
    LineContainer lc;
    vector<Line> linesToAdd = genLines(100, -absBound,absBound,-absBound,absBound),
                 lines;
    
    sortLines(linesToAdd);
    for(auto & l : linesToAdd) {
        lines.push_back(l);
        lc.add(l.k, l.m);
        rep(qit, 0, 10) {
            int x = randrange(-1000, 1000);
            EXPECT_EQ(naiveQuery(lines, x), lc.query(x));
        }
    }
}

TEST(FastLineContainer, Query) {
    srand(1);
    queryTest(5);
}

TEST(FastLineContainer, BigQuery) {
    srand(2);
    queryTest(1000);
}

void sortedQueryTest(int absBound) {
    LineContainer lc;
    int it = 100, queriesPerIt = 10;
    vector<Line> linesToAdd = genLines(100, -absBound,absBound,-absBound,absBound), lines;
    vector<int> queries;
    rep(i, 0, it*queriesPerIt) queries.push_back(randrange(-10000,10000));
    sort(queries.begin(), queries.end());
    sortLines(linesToAdd);
    //for(auto& q : queries) cout << q << " "; cout << endl;
    
    int qi = 0;
    for(auto & l : linesToAdd) {
        lines.push_back(l);
        lc.add(l.k, l.m);
        rep(qit, 0, queriesPerIt) {

            EXPECT_EQ(
                naiveQuery(lines, queries[qit+qi]),
                lc.sorted_query(queries[qit+qi])
            );
        }
        qi += queriesPerIt;
    }
}

TEST(FastLineContainer, SortedQuery) {
    srand(3);
    sortedQueryTest(5);
}

TEST(FastLineContainer, BigSortedQuery) {
    srand(4);
    sortedQueryTest(1000);
}
