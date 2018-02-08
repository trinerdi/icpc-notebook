/**
 * Author: Johan Sannemo
 * Date: 2017-03-12
 * License: CC0
 * Source: Wikipedia
 * Description: Calculates the max squared distance of a set of points.
 * Status: Tested.
 */
#pragma once

#include "ConvexHull.h"

vector<pair<int,int>> antipodal(const vector<P>& S, vector<int>& U, vector<int>& L) {
	vector<pair<int,int>> ret;
	int i = 0, j = L.size() - 1;
	while (i < U.size() - 1 || j > 0) {
		ret.emplace_back(U[i], L[j]);
		if (j == 0 || (i != U.size()-1 && (S[L[j]] - S[L[j-1]])
					.cross(S[U[i+1]] - S[U[i]]) > 0)) ++i;
		else --j;
	}
	return ret;
}

pair<int,int> polygonDiameter(const vector<P>& S) {
	vector<int> U, L; tie(U, L) = ulHull(S);
	pair<ll, pair<int,int>> ans;
	for(auto& x : antipodal(S, U, L))
		ans = max(ans, {(S[x.first] - S[x.second]).dist2(), x});
	return ans.second;
}
