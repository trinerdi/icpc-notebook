#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cstring>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
typedef long long ll;

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
    inline int other(int x) {
        return (x == a) ? b : a;
    }
    inline Flow unused(int from) {
        return (a == from) ? (cap - flow) : (cap + flow);
    }
};

struct Dinic {
    int n, S, T;
    vector<Edge> e;
    vector<vector<int>> g;
    vector<Flow> vals;
    vector<int> from, d, pt;
    
    Dinic(int _N) : n(_N), g(n), vals(n, 0), from(n, 0), d(n, -1), pt(n) {}
    
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
            int cur = bfs.front();
            bfs.pop();
            for (auto x : g[cur]) {
                int remote = e[x].other(cur);
                if (d[remote] != -1 || e[x].unused(remote) == 0) continue;
                d[remote] = d[cur] + 1;
                bfs.push(remote);
            }
        }
        return d[S] != -1;
    }
    
    
    ll blocking() {
        ll res = 0;
        
        while (d[S] < n) {
            vals[S] = INF;
            from[S] = 0;
            int cur = S;
            while (d[S] < n) {
                if (cur == T) break;
                bool found = false;
                int minD = n + 10;
                for (int &i = pt[cur]; i < g[cur].size(); i++) {
                    int x = g[cur][i];
                    int remote = e[x].other(cur);
                    Flow unused = e[x].unused(cur);
                    unused = min(vals[cur], unused);
                    if (unused == 0) continue;
                    minD = min(minD, d[remote]);
                    if (d[remote] == d[cur] - 1) {
                        from[remote] = x;
                        vals[remote] = unused;
                        cur = remote;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    d[cur] = minD + 1;
                    if (cur != S) cur = e[from[cur]].other(cur);
                }
            }
            if (d[S] >= n) break;
            cur = T;
            Flow added = vals[cur];
            res += added;
            while (cur != S) {
                e[from[cur]].flow += ((cur == e[from[cur]].b) ? added : (-added));
                cur = e[from[cur]].other(cur);
            }
        }
        return res;
    }
    
    Flow getFlow(int _S, int _T) {
        S = _S, T = _T;
        Flow res = 0;
        
        while (levels()) {
            fill(pt.begin(), pt.end(), 0);
            while (ll cur = blocking()) {
                res += cur;
            }
        }
        return res;
    }
};
