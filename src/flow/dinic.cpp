#include "../base.hpp"

// Assumes undirected graph - capacities are equal in both directions
// Add edges using addEdge(), then call getFlow(source, sink)
// Can only be called once in this state (values are not cleared)
// O(|V|^2 |E|), but much faster in practice: V=5000, E=30000 in 0.27s (SPOJ FASTFLOW)

typedef long long Flow;
const ll INF = 1e15;

struct Edge {
    Flow flow = 0;
    int a, b;
    Flow cap = 1;
    Edge(int _a, int _b, Flow _cap) : a(_a), b(_b), cap(_cap) {}
    int other(int x) { return (x == a) ? b : a; }
    Flow unused(int x) { return (x == a) ? (cap - flow) : (cap + flow); }
};

struct Dinic {
    int n, S, T;
    vector<Edge> e;
    vector<vector<int>> g;
    vector<int> d, pt;
    
    Dinic(int _N) : n(_N), g(n), d(n, -1), pt(n) {}
    
    void addEdge(int a, int b, Flow cap) {
        e.emplace_back(Edge(a, b, cap));
        g[a].push_back(e.size() - 1);
        g[b].push_back(e.size() - 1);
    }
    
    bool levels() {
        fill(d.begin(), d.end(), -1);
        d[T] = 0;
        queue<int> bfs;
        bfs.push(T);
        while (!bfs.empty()) {
            int a = bfs.front();
            bfs.pop();
            if (a == S) break;
            for (auto x : g[a]) {
                int b = e[x].other(a);
                if (d[b] != -1 || e[x].unused(b) == 0) continue;
                d[b] = d[a] + 1;
                bfs.push(b);
            }
        }
        return d[S] != -1;
    }
    
    Flow blocking(int a, Flow val) {
        if (a == T || val == 0) return val;
        for (int &i = pt[a]; i < g[a].size(); i++) {
            int &x = g[a][i];
            int b = e[x].other(a);
            if (d[b] == d[a] - 1) {
                Flow unused = min(val, e[x].unused(a));
                if (Flow added = blocking(b, unused)) {
                    e[x].flow += ((a == e[x].a) ? added : (-added));
                    return added;
                }
            }
        }
        return 0;
    }
    
    Flow getFlow(int _S, int _T) {
        S = _S, T = _T;
        Flow res = 0;
        
        while (levels()) {
            fill(pt.begin(), pt.end(), 0);
            while (ll cur = blocking(S, INF)) {
                res += cur;
            }
        }
        return res;
    }
};
