/**
 * Author: Václav Volhejn
 * Description: Compress vector $v$ into $v'$ such that $v_i < v_j \iff v'_i < v'_j$
 *  and elements are integers bounded by $0 \leq v'_i < |v|$. Mutates $v$.
 * Status: tested
 * Usage:
 *  vector<ll> v = {6, 2, -3, 2};
 *  compress(v); // v == {2, 1, 0, 1}
 */
#include "../base.hpp"

void compress(vector<ll>& v) {
    vector<ll> w = v;
    sort(w.begin(), w.end());
    w.erase(unique(w.begin(), w.end()), w.end());
    for(auto& x : v)
        x = lower_bound(w.begin(), w.end(), x) - w.begin();
}
