/**
 * Name: Interval cover
 * Author: Johan Sannemo
 * License: CC0
 * Description: Compute indices of smallest set of intervals covering another interval.
 *  Intervals should be [inclusive, exclusive). To support [inclusive, inclusive],
 *  change (A) to add \texttt{|| R.empty()}. Returns empty set on failure (or if $G$ is empty).
 * Time: $O(N \log N)$
 * Status: Tested on Kattis, intervalcover
 */
#pragma once

template<class T>
vector<int> cover(pair<T, T> G, vector<pair<T, T>> I) {
	vector<int> S(I.size()), R;
	iota(S.begin(), S.end(), 0);
	sort(S.begin(), S.end(), [&](int a, int b) { return I[a] < I[b]; });
	T cur = G.first;
	int at = 0;
	while (cur < G.second) { // (A)
		pair<T, int> mx = make_pair(cur, -1);
		while (at < I.size() && I[S[at]].first <= cur) {
			mx = max(mx, make_pair(I[S[at]].second, S[at]));
			at++;
		}
		if (mx.second == -1) return {};
		cur = mx.first;
		R.push_back(mx.second);
	}
	return R;
}
