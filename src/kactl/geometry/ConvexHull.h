/**
 * Name: Convex hull
 * Author: Johan Sannemo
 * Date: 2017-04-16
 * License: CC0
 * Source: Basic algorithm knowledge
 * Description:
 *  %\\\begin{minipage}{75mm}
 *  \figure{kactl/geometry/ConvexHull.pdf}
 *  Returns a vector of indices of the convex hull in counter-clockwise order.
 *  Points on the edge of the hull between two other points are not considered part of the hull.
 *  %\end{minipage}
 *  %\begin{minipage}{15mm}
 *  %\vspace{-6mm}
 *  %\includegraphics[width=\textwidth]{../content/geometry/ConvexHull}
 *  %\vspace{-6mm}
 *  %\end{minipage}
 * Status: tested with Kattis problems convexhull
 * Usage:
 * 	vector<P> ps, hull;
 *  for(auto& i : convexHull(ps)) hull.push_back(ps[i]);
 * Time: $O(N \log N)$
 */
#pragma once

#include "Point.h"

typedef Point<ll> P;
pair<vector<int>, vector<int>> ulHull(const vector<P>& S) {
	vector<int> Q(S.size()), U, L;
	iota(Q.begin(), Q.end(), 0);
	sort(Q.begin(), Q.end(), [&S](int a, int b){ return S[a] < S[b]; });
	for(auto& it : Q) {
#define ADDP(C, cmp) while (C.size() > 1 && S[C[C.size()-2]].cross(\
	S[it], S[C.back()]) cmp 0) C.pop_back(); C.push_back(it);
		ADDP(U, <=); ADDP(L, >=);
	}   
	return {U, L}; 
}

vector<int> convexHull(const vector<P>& S) {
	vector<int> u, l; tie(u, l) = ulHull(S);
	if (S.size() <= 1) return u;
	if (S[u[0]] == S[u[1]]) return {0};
	l.insert(l.end(), u.rbegin()+1, u.rend()-1);
	return l;
}
