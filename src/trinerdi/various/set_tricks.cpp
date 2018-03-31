/**
 * Name: Closest lower element in a set
 * Author: Václav Volhejn
 * Description: Functions to get the closest lower element in a set.
 *  Given $S$, $k$, returns $\max \{x \mid x \in S; x \leq k\}$, or $-\infty$
 *  if there is no suitable element. Strict version replaces $\leq$ with $<$.
 * Status: tested
 */
#include "../base.hpp"
const ll INF = 1e18;

ll closestLower(set<ll>& s, ll k) {
    auto it = s.upper_bound(k);
    return (it == s.begin()) ? -INF : *(--it);
}

ll closestLowerStrict(set<ll>& s, ll k) {
    auto it = s.lower_bound(k);
    return (it == s.begin()) ? -INF : *(--it);
}
