/**
 * Name: Point-line orientation
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description: Returns where $p$ is as seen from $s$ towards $e$.
 *  1/0/-1 $\Leftrightarrow$ left/on line/right. If the optional argument $eps$ is given,
 *  0 is returned if $p$ is within distance $eps$ from the line.
 *  {\tt P} is supposed to be {\tt Point<T>} where {\tt T} is e.g. double or long long. It uses products in intermediate steps so watch out for overflow if using int or long long.
 * Status: tested
 * Usage:
 * 	bool left = sideOf(p1,p2,q)==1;
 */
#pragma once

#include "Point.h"

template <class P>
int sideOf(const P& s, const P& e, const P& p) {
	auto a = (e-s).cross(p-s);
	return (a > 0) - (a < 0);
}
template <class P>
int sideOf(const P& s, const P& e, const P& p, double eps) {
	auto a = (e-s).cross(p-s);
	double l = (e-s).dist()*eps;
	return (a > l) - (a < -l);
}
