/**
 * Name: Tree compression
 * Author: Simon Lindholm
 * Date: 2016-01-14
 * License: CC0
 * Status: Tested at CodeForces
 * Description: Given a rooted tree and a subset S of nodes, compute the minimal
 *  subtree that contains all the nodes by adding all (at most $|S|-1$)
 *  pairwise LCA's and compressing edges.
 *  Returns a list of $(par, orig\_index)$ representing a tree rooted at 0.
 *  The root points to itself.
 * Time: $O(|S| \log |S|)$
 */
#pragma once

#include "LCA.h"

vpi compressTree(LCA& lca, const vector<int>& subset) {
	static vector<int> rev; rev.resize(lca.dist.size());
	vector<int> li = subset, &T = lca.time;
	auto cmp = [&](int a, int b) { return T[a] < T[b]; };
	sort(li.begin(), li.end(), cmp);
	int m = li.size()-1;
	rep(i,0,m) {
		int a = li[i], b = li[i+1];
		li.push_back(lca.query(a, b));
	}
	sort(li.begin(), li.end(), cmp);
	li.erase(unique(li.begin(), li.end()), li.end());
	rep(i,0,li.size()) rev[li[i]] = i;
	vpi ret = {pair<int,int>(0, li[0])};
	rep(i,0,li.size()-1) {
		int a = li[i], b = li[i+1];
		ret.emplace_back(rev[lca.query(a, b)], b);
	}
	return ret;
}
