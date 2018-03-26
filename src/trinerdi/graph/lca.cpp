#include "../base.hpp"

// Assumes a tree in adjacency list form is saved in g Call initLCA first.
// O(n log n) initialization, O(log n) query. Good constants on both.

const int N = 2e5 + 10;
const int LOG = 20;
int d[N];
int pred[N][LOG];
vector<int> g[N];

void dfs(int a) {
    for (auto b : g[a]) {
        if (b == pred[a][0]) continue;
        d[b] = d[a] + 1;
        pred[b][0] = a;
        dfs(b);
    }
}

void initLCA(int root, int n = N) {
    pred[root][0] = -1, d[root] = 0;
    dfs(root);
    rep(l, 1, LOG) rep(i, 0, n) {
        if (pred[i][l - 1] == -1) pred[i][l] = -1;
        else pred[i][l] = pred[pred[i][l - 1]][l - 1];
    }
}

int lca(int a, int b) {
    if (d[a] < d[b]) swap(a, b);
    per(l, 0, LOG) {
        if (pred[a][l] != -1 && d[pred[a][l]] >= d[b]) a = pred[a][l];
    }
    if (a == b) return a;
    per(l, 0, LOG) if (pred[a][l] != pred[b][l]) {
        a = pred[a][l];
        b = pred[b][l];
    }
    return pred[a][0];
}
