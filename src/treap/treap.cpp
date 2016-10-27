#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Higher weights are higher.
// Primarily used as a set able to get the k-th element

struct Treap {
    Treap *lson = NULL, *rson = NULL;
    ll val;
    int weight;
    int size = 0;
    
    Treap(ll _val) : val(_val), weight(rand()), size(1) {}
    
    ~Treap() {
        delete lson;
        delete rson;
    }
    
    void setSon(bool right, Treap *newSon) {
        Treap *&upd = right ? (rson) : (lson);
        upd = newSon;
        size = 1 + (lson ? (lson->size) : 0) + (rson ? (rson->size) : 0);
    }
};

Treap* merge(Treap *l, Treap *r) {
    assert(l || r);
    if (!l) return r;
    if (!r) return l;
    if (l->weight > r->weight) {
        l->setSon(true, merge(l->rson, r));
        return l;
    } else {
        r->setSon(false, merge(l, r->lson));
        return r;
    }
}

pair<Treap*, Treap*> split(Treap *a, ll val) {
    if (!a) return {NULL, NULL};
    if (a->val <= val) {
        pair<Treap*, Treap*> res = split(a->rson, val);
        a->setSon(true, res.first);
        return {a, res.second};
    } else {
        pair<Treap*, Treap*> res = split(a->lson, val);
        a->setSon(false, res.second);
        return {res.first, a};
    }
}

void insert(Treap *&a, ll val) {
    if (!a) {
        a = new Treap(val);
    } else {
        pair<Treap*, Treap*> spl = split(a, val);
        a = merge(spl.first, new Treap(val));
        a = merge(a, spl.second);
    }
}

ll getKth(Treap *a, int k) { //zero-indexed
    int lsize = (a->lson ? (a->lson->size) : 0);
    if (lsize == k) {
        return a->val;
    } else if (lsize > k) {
        return getKth(a->lson, k);
    } else {
        assert(a->rson); //when k >= size
        return getKth(a->rson, k - lsize - 1);
    }
}

int indexOf(Treap *a, ll val) {
    if (!a) return -1;
    int lsize = (a->lson ? (a->lson->size) : 0);
    if (a->val == val) {
        return lsize;
    } else if (val < a->val) {
        return indexOf(a->lson, val);
    } else {
        int res = indexOf(a->rson, val);
        if (res == -1) return -1;
        else return res + lsize + 1;
    }
}

int main() { // Tests the treap
    srand(time(0));
    Treap* t = NULL;
    int n = 1000000; // n = 10^6 takes about 5 seconds on my machine
    unordered_set<ll> used; // Elements must be different for the test to work
    for (int i = 0; i < n; i++) {
        ll x = rand();
        while (used.count(x)) x = rand();
        used.insert(x);
        insert(t, x);
    }
    ll last = 0;
    for (int i = 0; i < n; i++) {
        ll x = getKth(t, i);
        assert(x >= last);
        assert(indexOf(t, x) == i);
        last = x;
        //cout << "element " << i << ": " << x << endl;
    }
    return 0;
}
