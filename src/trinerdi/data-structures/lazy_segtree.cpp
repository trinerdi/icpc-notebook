/**
 * Name: Lazy segment tree
 * Author: Vaclav Volhejn
 * Description: Lazy minimum segment tree supporting range updates
 *  and queries. Exclusive right bounds.
 * Time: $O(\log N)$ per update/query
 */
#include "../base.hpp"

struct Segtree {
    const ll INF = 1e18; // Neutral element of min
    int l, r; // Exclusive righ
    ll val = 0, lazy = 0;
    Segtree *lson = NULL, *rson = NULL;

    Segtree (int _l, int _r) : l(_l), r(_r) {}
    ~Segtree() { delete lson; delete rson; }
    
    void unlazy() {
        val += lazy;
        if (l == r) return;
        if(lson == NULL) {
            int mid = (l+r)/2;
            lson = new Segtree(l, mid);
            rson = new Segtree(mid, r);
        }
        lson->lazy += lazy; // <- Propagate
        rson->lazy += lazy;
        lazy = 0;
    }

    void rangeUpdate(int fr, int to, ll x) {
        unlazy();
        if (fr >= r || l >= to) return;
        if (fr <= l && to >= r) {
            lazy += x; // <- Add lazy value
            unlazy();
        } else {
            lson->rangeUpdate(fr, to, x);
            rson->rangeUpdate(fr, to, x);
            val = min(lson->val, rson->val); // <- Combine from sons
        }
    }
    
    ll rangeQuery(int fr, int to) {
        if (fr >= r || l >= to) return INF;
        unlazy();
        if (fr <= l && to >= r) {
            return val;
        } else {
            if (lson == NULL) return 0; // default value of `val`
            return min(lson->rangeQuery(fr, to),  // <- Combine from sons
                       rson->rangeQuery(fr, to));
        }
    }
};
