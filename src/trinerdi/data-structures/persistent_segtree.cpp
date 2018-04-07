/**
 * Name: Persistent segment tree
 * Author: Vaclav Volhejn
 * Description: A segment tree whose updates do not invalidate previous versions.
 *  For $N$ elements, call \verb|new Segtree(0, N)}. Exclusive right bounds.
 * Time: $O(\log N)$ per update/query
 */
#include "../base.hpp"

struct Segtree {
    int l, r;
    ll val = 0;
    Segtree *lson = NULL, *rson = NULL;

    Segtree (int _l, int _r) : l(_l), r(_r) {
        if (r - l > 1) {
            int mid = (l + r) / 2;
            lson = new Segtree(l, mid);
            rson = new Segtree(mid, r);
        }
    }
    
    ~Segtree() { delete lson; delete rson; }
    
    Segtree* rangeUpdate(int fr, int to, ll x) {
        if (fr >= r || l >= to) return this; // Range is not in the segment
        if (fr <= l && to >= r) { // Range is completely in the segment
            return new Segtree(l, r, val + x, lson, rson);
        }
        return new Segtree(l, r, val,
                           lson->rangeUpdate(fr, to, x),
                           rson->rangeUpdate(fr, to, x));
    }
    
    ll pointQuery(int i) const {
        if (r - l == 1) return val;
        int mid = (l + r) / 2;
        return val + ((i < mid) ? lson : rson)->pointQuery(i);
    }
private: // Constructor used internally, does not initialize children
    Segtree(int _l, int _r, ll _val, Segtree* _lson, Segtree* _rson) :
        l(_l), r(_r), val(_val), lson(_lson), rson(_rson) {}
};
