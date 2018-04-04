/**
 * Name: 2D Fenwick tree
 * Author: Simon Lindholm
 * Date: 2017-05-11
 * License: CC0
 * Source: folklore
 * Description: Computes sums $a[i\ldots j]$ for all $i<I$, $j<J$, and increases single elements $a[i\ldots j]$.
 *  Requires that the elements to be updated are known in advance
 *  (call {\tt fakeUpdate()} before {\tt init()}).
 * Time: $O(\log^2 N)$. (Use persistent segment trees for $O(\log N)$.)
 */
#pragma once

#include "FenwickTree.h"

struct FT2 {
	vector<vector<int>> ys; vector<FT> ft;
	FT2(int limx) : ys(limx) {}
	void fakeUpdate(int x, int y) {
		for (; x < ys.size(); x |= x + 1) ys[x].push_back(y);
	}
	void init() {
		for(auto& v : ys) sort(v.begin(), v.end()), ft.emplace_back(v.size());
	}
	int ind(int x, int y) {
		return (int)(lower_bound(ys[x].begin(), ys[x].end(), y) - ys[x].begin()); }
	void update(int x, int y, ll dif) {
		for (; x < ys.size(); x |= x + 1)
			ft[x].update(ind(x, y), dif);
	}
	ll query(int x, int y) {
		ll sum = 0;
		for (; x; x &= x - 1)
			sum += ft[x-1].query(ind(x-1, y));
		return sum;
	}
};
