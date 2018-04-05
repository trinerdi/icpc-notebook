/**
 * Name: $\O(\sqrt VE)$ maximum matching (Hopkroft--Karp)
 * Author: Chen Xing
 * Date: 2009-10-13
 * License: CC0
 * Source: N/A
 * Description: Find a maximum matching in a bipartite graph. $g$ must {\bf
 *  only} contain edges from left to right.
 * Status: Tested on oldkattis.adkbipmatch and SPOJ:MATCHING
 * Usage: vector<int> ba(m, -1); hopcroftKarp(g, ba);
 * Time: $O(\sqrt{V}E)$
 */
#pragma once

bool dfs(int a, int layer, const vector<vector<int>>& g, vector<int>& btoa,
			vector<int>& A, vector<int>& B) {
	if (A[a] != layer) return 0;
	A[a] = -1;
	for(auto& b : g[a]) if (B[b] == layer + 1) {
		B[b] = -1;
		if (btoa[b] == -1 || dfs(btoa[b], layer+2, g, btoa, A, B))
			return btoa[b] = a, 1;
	}
	return 0;
}

int hopcroftKarp(const vector<vector<int>>& g, vector<int>& btoa) {
	int res = 0;
	vector<int> A(g.size()), B(btoa.size()), cur, next;
	for (;;) {
		fill(A.begin(), A.end(), 0);
		fill(B.begin(), B.end(), -1);
		/// Find the starting nodes for BFS (i.e. layer 0).
		cur.clear();
		for(auto& a : btoa) if(a != -1) A[a] = -1;
		rep(a,0,g.size()) if(A[a] == 0) cur.push_back(a);
		/// Find all layers using bfs.
		for (int lay = 1;; lay += 2) {
			bool islast = 0;
			next.clear();
			for(auto& a : cur) for(auto& b : g[a]) {
				if (btoa[b] == -1) {
					B[b] = lay;
					islast = 1;
				}
				else if (btoa[b] != a && B[b] == -1) {
					B[b] = lay;
					next.push_back(btoa[b]);
				}
			}
			if (islast) break;
			if (next.empty()) return res;
			for(auto& a : next) A[a] = lay+1;
			cur.swap(next);
		}
		/// Use DFS to scan for augmenting paths.
		rep(a,0,g.size()) {
			if(dfs(a, 0, g, btoa, A, B))
				++res;
		}
	}
}
