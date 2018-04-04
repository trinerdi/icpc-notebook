/**
 * Name: Minimum vertex cover
 * Author: Johan Sannemo, Simon Lindholm
 * Date: 2016-12-15
 * License: CC0
 * Description: Finds a minimum vertex cover in a bipartite graph.
 *  The size is the same as the size of a maximum matching, and
 *  the complement is an independent set.
 * Status: fuzz-tested
 */
#pragma once

#include "DFSMatching.h"

vector<int> cover(vector<vector<int>>& g, int n, int m) {
	int res = dfs_matching(g, n, m);
	seen.assign(m, false);
	vector<bool> lfound(n, true);
	for(auto& it : match) if (it != -1) lfound[it] = false;
	vector<int> q, cover;
	rep(i,0,n) if (lfound[i]) q.push_back(i);
	while (!q.empty()) {
		int i = q.back(); q.pop_back();
		lfound[i] = 1;
		for(auto& e : g[i]) if (!seen[e] && match[e] != -1) {
			seen[e] = true;
			q.push_back(match[e]);
		}
	}
	rep(i,0,n) if (!lfound[i]) cover.push_back(i);
	rep(i,0,m) if (seen[i]) cover.push_back(n+i);
	assert(cover.size() == res);
	return cover;
}
