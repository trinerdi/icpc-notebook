/**
 * Author: Johan Sannemo
 * License: CC0
 * Description: Compute indices for the longest increasing subsequence.
 * Status: Tested on Kattis, longincsubseq
 * Time: $O(N \log N)$
 */
#pragma once

template<class I> vector<int> lis(vector<I> S) {
	vector<int> prev(S.size());
	typedef pair<I, int> p;
	vector<p> res;
	rep(i,0,S.size()) {
		p el { S[i], i };
		//S[i]+1 for non-decreasing
		auto it = lower_bound(res.begin(), res.end(), p { S[i], 0 });
		if (it == res.end()) res.push_back(el), it = --res.end();
		*it = el;
		prev[i] = it==res.begin() ?0:(it-1)->second; 
	}
	int L = res.size(), cur = res.back().second;
	vector<int> ans(L);
	while (L--) ans[L] = cur, cur = prev[cur];
	return ans;
}
