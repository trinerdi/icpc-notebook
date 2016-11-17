#include "../base.hpp"
#include "lca.cpp"

// Assumes a tree in adjacency list form is saved in g Call initLCA first.
// O(n log n) initialization, O(log n) query. Good constants on both.

int sub[N];
vector<vector<int>> chains;
int chainOf[N], chainPos[N];

// Can be merged with dfs() from LCA
int dfsHLD(int a) {
    sub[a] = 1;
    for (auto b : g[a]) {
        if (b == pred[a][0]) continue;
        sub[a] += dfsHLD(b);
    }
    return sub[a];
}

void buildHLD(int a, int c) {
    chainOf[a] = c, chainPos[a] = chains[c].size();
    chains[c].push_back(a);
    if (g[a].size() - (pred[a][0] != -1) == 0) return; // root is a special case
    int best = -1;
    for (auto b : g[a]) {
        if (b == pred[a][0]) continue;
        if (best == -1 || sub[b] > sub[best]) best = b;
    }
    buildHLD(best, c);
    for (auto b : g[a]) {
        if (b == pred[a][0] || b == best) continue;
        chains.push_back(vector<int>());
        buildHLD(b, chains.size() - 1);
    }
}

void initHLD(int root, int n = N) {
    initLCA(root, n);
    dfsHLD(root);
    chains.push_back(vector<int>());
    buildHLD(root, 0);
    // TODO: initialize per-chain data structures
}

void changeChain(int ci, int from, int to, int value) {
    // cout << chains[ci][from] << "-" << chains[ci][to] << ": " << value << endl;
}

void change(int a, int b, int value) { // a is an ancestor of b
    int ci = chainOf[b];
    if (chainOf[a] == chainOf[b]) {
        changeChain(ci, chainPos[a], chainPos[b], value);
    } else {
        changeChain(ci, 0, chainPos[b], value);
        change(a, pred[chains[ci][0]][0], value);
    }
}

void query(int a, int b) {
    int l = lca(a, b);
    change(l, a, 1), change(l, b, 1), change(l, l, -1);
}
