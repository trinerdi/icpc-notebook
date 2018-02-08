/**
 * Author: Chen Xing
 * Date: 2009-04-14
 * License: CC0
 * Source: folklore
 * Description: Eulerian undirected/directed path/cycle algorithm.
 *  Returns a list of nodes in the Eulerian path/cycle with src at both start and end,
 *  or empty list if no cycle/path exists. To get edge indices back,
 *  also put {\tt it->second} in {\tt s} (and then ret).
 * Time: $O(E)$
 * Status: tested
 */
#pragma once

struct V {
	vector<pair<int,int>> outs; // (dest, edge index)
	int nins = 0;
};

vector<int> euler_walk(vector<V>& nodes, int nedges, int src=0) {
	int c = 0;
	for(auto& n : nodes) c += abs(n.nins - n.outs.size());
	if (c > 2) return {};
	vector<vector<pair<int,int>>::iterator> its;
	for(auto& n : nodes)
		its.push_back(n.outs.begin());
	vector<bool> eu(nedges);
	vector<int> ret, s = {src};
	while(!s.empty()) {
		int x = s.back();
		auto& it = its[x], end = nodes[x].outs.end();
		while(it != end && eu[it->second]) ++it;
		if(it == end) { ret.push_back(x); s.pop_back(); }
		else { s.push_back(it->first); eu[it->second] = true; }
	}
	if(ret.size() != nedges+1)
		ret.clear(); // No Eulerian cycles/paths.
	// else, non-cycle if ret.front() != ret.back()
	reverse(ret.begin(), ret.end());
	return ret;
}
