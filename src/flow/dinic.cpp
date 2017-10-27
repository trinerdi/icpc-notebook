#include "../base.hpp"

// Add directed edges using addEdge(), then call getFlow(source, sink)
// O(|V|^2 |E|), but much faster in practice: V=5000, E=30000 in 0.27s (SPOJ FASTFLOW)
// The edges with flow>0 were used in the resulting flow.
// Based heavily on the Stanford implementation:
// https://github.com/jaehyunp/stanfordacm/blob/master/code/Dinic.cc

typedef long long Flow;
const ll INF = 1e15;

struct Edge {
    Flow flow = 0;
    int a, b;
    Flow cap = 1;
    Edge(int _a, int _b, Flow _cap) : a(_a), b(_b), cap(_cap) {}
    Flow unused() { return cap - flow; }
};

struct Dinic {
    int n, S, T;
    vector<Edge> e;
    vector<vector<int>> g;
    vector<int> d, pt;
    
    Dinic(int _N) : n(_N), g(n), d(n), pt(n) {}
    
    void addEdge(int a, int b, Flow cap) {
        e.push_back(Edge(a, b, cap));
        g[a].push_back(e.size() - 1);
        e.push_back(Edge(b, a, 0));
        g[b].push_back(e.size() - 1);
    }
    
    bool levels() {
        fill(d.begin(), d.end(), -1);
        d[S] = 0;
        queue<int> bfs({S});
        while (!bfs.empty()) {
            int a = bfs.front();
            bfs.pop();
            if (a == T) break;
            for (auto x : g[a]) {
                int b = e[x].b;
                if (d[b] != -1 || e[x].unused() == 0) continue;
                d[b] = d[a] + 1;
                bfs.push(b);
            }
        }
        return d[T] != -1;
    }
    
    Flow blocking(int a, Flow val) {
        if (a == T || val == 0) return val;
        for (int &i = pt[a]; i < g[a].size(); i++) {
            int x = g[a][i];
            int b = e[x].b;
            if (d[b] == d[a] + 1) {
                if (Flow added = blocking(b, min(val, e[x].unused()))) {
                    e[x].flow += added;
                    e[x ^ 1].flow -= added;
                    return added;
                }
            }
        }
        return 0;
    }
    
    Flow getFlow(int _S, int _T) {
        S = _S, T = _T;
        Flow res = 0;
        for (auto &x : e) x.flow = 0;
        while (levels()) {
            fill(pt.begin(), pt.end(), 0);
            while (ll cur = blocking(S, INF))
                res += cur;
        }
        return res;
    }
};
