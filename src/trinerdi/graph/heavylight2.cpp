/**
 * Name: HLD + LCA
 * Author: Richard Hladik
 * Source: The concept of HLD with rearranging of sons borrowed from <codeforces.com/blog/entry/53170>
 * Description: Calculates the heavy-light decomposition of given tree.
 *  Data for chains is stored in one flat structure.
 *  Also usable for lowest common ancestor.
 * Time: $O(n \log n)$
 * Usage: initHLD();
 *  // What is the value on edges on path from 1 to 2?
 *  quepdate(1, 2, false, ZERO);
 *  // Update path from 1 to 2 with value 30
 *  quepdate(1, 2, true, 30);
 */
#include "../base.hpp"

vector<vector<int>> G;
vector<int> et, in, out, subs, depth, top, par;
typedef ll T;

// Implement these four to customise behavior
T ZERO = 0; // Neutral element for operations
T combine(T a, T b) { return a + b; } // How to compose two results
// Query or update interval from a to b (0<=a,b<|V|)
T flat_quepdate(int a, int b, bool upd, T val);
void flat_init(void); // Initialize the flat data structure

void dfs_counts(int v = 0) {
	subs[v] = 1;
	for (auto &s: G[v]) {
		par[s] = v, depth[s] = depth[v] + 1;
		dfs_counts(s);
		subs[v] += subs[s];
		if (subs[s] > subs[G[v][0]]) swap(s, G[v][0]);
	}
}

int dfs_numbering(int v = 0, int t = -1) {
	in[v] = ++t, et.push_back(v);
	for (auto s: G[v])
		t = dfs_numbering(s, t);
	return out[v] = t;
}

void buildHLD(int v = 0, int c = 0) {
	top[v] = c;
	rep(i, 0, G[v].size())
		buildHLD(G[v][i], (i) ? G[v][i] : c);
}

void initHLD(void) {
	in = {}, in.resize(G.size());
	out = subs = depth = top = par = in;
	par[0] = -1, et = {}, depth[0] = 0;
	dfs_counts();
	dfs_numbering();
	buildHLD();
	flat_init();
}

// Needs dfs_counts(), buildHLD()
int lca(int a, int b) {
	for (; top[a] != top[b]; b = par[top[b]])
		if (depth[top[a]] > depth[top[b]])
			swap(a, b);
	return (depth[a] < depth[b]) ? a : b;
}

// a is an ancestor of b; a isn't included in the query
T _quepdate(int a, int b, bool upd, T val) {
	T res = ZERO;
	for (; top[a] != top[b]; b = par[top[b]])
		res = combine(res, flat_quepdate(in[top[b]], in[b], upd, val));
	return combine(res, flat_quepdate(in[a] + 1, in[b], upd, val));
}

// lca(a, b) isn't included in the query, which is desired if operating on edge weights
T quepdate(int a, int b, bool upd, T val) {
	int l = lca(a, b);
	return combine(_quepdate(l, a, upd, val), _quepdate(l, b, upd, val));
}
