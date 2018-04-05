/**
 * Name: $\O(EV)$ maximum matching (DFS)
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source:
 * Description: This is a simple matching algorithm but should be just fine in
 *  most cases. Graph $g$ should be a list of neighbours of the left partition,
 *  there must {\bf not} be edges from the right partition to the left. $n$ is
 *  the size of the left partition and $m$ is the size of the right partition.
 *  If you want to get the matched pairs, $match[i]$ contains match for vertex
 *  $i$ on the right side or $-1$ if it's not matched.
 * Time: $O(EV)$
 * Status: works
 */
#pragma once

vector<int> match;
vector<bool> seen;
bool find(int j, const vector<vector<int>>& g) {
	if (match[j] == -1) return 1;
	seen[j] = 1; int di = match[j];
	for(auto& e : g[di])
		if (!seen[e] && find(e, g)) {
			match[e] = di;
			return 1;
		}
	return 0;
}
int dfs_matching(const vector<vector<int>>& g, int n, int m) {
	match.assign(m, -1);
	rep(i,0,n) {
		seen.assign(m, 0);
		for(auto& j :g[i])
			if (find(j, g)) {
				match[j] = i;
				break;
			}
	}
	return m - (int)count(match.begin(), match.end(), -1);
}
