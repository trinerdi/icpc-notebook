#include "../base.hpp"

typedef unsigned long long ull;

//Alternative: 998244353, 23, 15311432, 469870224, 499122177.
const ull P = 3221225473;     // = 3*2^EXP + 1
const ull EXP = 30;
const ull W = 125;            // W^(2^EXP) = 1
const ull W_INV = 2267742733; // modular inverse of W
const ull INV_2 = 1610612737;

vector<ull> w(EXP + 1), wInv(EXP + 1), inv2(EXP + 1);

void initNTT() {
    w[EXP] = W;
    wInv[EXP] = W_INV;
    per(i, 0, EXP) {
        w[i] = (w[i + 1] * w[i + 1]) % P;
        wInv[i] = (wInv[i + 1] * wInv[i + 1]) % P;
    }
    inv2[0] = 1, inv2[1] = INV_2;
    rep(i, 2, EXP + 1) inv2[i] = (inv2[i - 1] * INV_2) % P;
}

void ntt(int k, vector<ull>& v, bool inv) { // n = 2^k
    if (!k) return;
    vector<ull> even, odd;
    rep(i, 0, v.size()) ((i % 2) ? odd : even).push_back(v[i]);
    ntt(k - 1, even, inv);
    ntt(k - 1, odd, inv);
    // (2^k)-th root of unity: omega1^(2^k) = 1 (mod P here)
    ull omega1 = w[k];
    if (inv) omega1 = wInv[k];
    ull omega = 1;
    rep(i, 0, (1 << (k - 1))) {
        v[i] = (even[i] + (omega * odd[i]) % P) % P;
        v[i + (1 << (k - 1))] = (P + even[i] - (omega * odd[i]) % P) % P;
        omega = (omega1 * omega) % P;
    }
}

vector<ll> multiplyPolynomialsNTT(vector<ll> &a, vector<ll> &b) {
    int k = 0;
    while ((1 << k) < a.size() || (1 << k) < b.size()) k++;
    k++;
    
    vector<ull> v[2];
    rep(j, 0, 2) {
        for (auto x : (j ? b : a)) v[j].push_back((x + P) % P);
        v[j].resize(1 << k, 0);
        ntt(k, v[j], false);
    }
    
    rep(i, 0, 1 << k) v[0][i] = (v[0][i] * v[1][i]) % P;
    ntt(k, v[0], true);
    vector<ll> res(1 << k);
    rep(i, 0, 1 << k) res[i] = (v[0][i] * inv2[k]) % P;
    return res;
}
