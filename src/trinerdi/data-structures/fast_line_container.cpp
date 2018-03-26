/**
 * Author: Vaclav Volhejn, based on Simon Lindholm's code
 * Description: Container where you can add lines of the form $kx+m$,
 *  and query maximum values at points $x$. Assumes that the $k$s of the added lines
 *  are non-decreasing. Use \verb|sorted_query()} for cases where $x$ is non-decreasing.
 * Time: amortized $O(1)$ per \verb|add()} and \verb|sorted_query()}, $O(\log n)$ per \verb|query()}
 */
#include "../base.hpp"

struct Line {
    mutable ll k, m, p; // p is the position from which the line is optimal
    ll val(ll x) const { return k*x + m; }
    bool operator<(const Line& o) const { return p < o.p; }
};
ll floordiv (ll a, ll b) {
    return a / b - ((a^b) < 0 && a % b);
}
// queries and line intersections should be in range (-INF, INF)
const ll INF = 1e17;

struct LineContainer : vector<Line> {
    ll isect(const Line& a, const Line& b) {
        if (a.k == b.k) return a.m > b.m ? (-INF) : INF;
        ll res = floordiv(b.m - a.m, a.k - b.k);
        if (a.val(res) < b.val(res)) res++;
        return res;
    }

    void add(ll k, ll m) {
        Line a = {k,m,INF};
        while(!empty() && isect(a, back()) <= back().p) pop_back();
        a.p = empty() ? (-INF) : isect(a, back());
        push_back(a);
    }

    ll query(ll x) {
        assert(!empty());
        return (--upper_bound(begin(), end(), Line({0,0,x})))->val(x);
    }

    int qi = 0;
    ll sorted_query(ll x) {
        assert(!empty());
        qi = min(qi, (int)size() - 1);
        while(qi < size()-1 && (*this)[qi+1].p <= x) qi++;
        return (*this)[qi].val(x);
    }
};
