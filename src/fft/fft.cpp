#include "../base.hpp"

typedef complex<ld> C;
const ld PI = 3.14159265358979323;
const ld EPS = 1e-9;

// precise for numbers to ~|1e5| for two polynomials of size 1e4
// precise for numbers to ~|1e7| for two polynomials of size 100
// takes about 4 seconds for two 1e5 polynomials on my machine

void fft(int n, vector<C>& v, bool inv) {
    if (n == 1) return;
    vector<C> even, odd;
    rep(i, 0, v.size()) ((i % 2) ? odd : even).push_back(v[i]);
    fft(n / 2, even, inv);
    fft(n / 2, odd, inv);
    C omega1 = polar((ld) 1.0, 2 * PI / n);
    if (inv) omega1 = conj(omega1);
    C omega = 1;
    rep(i, 0, n / 2) {
        v[i] = even[i] + omega * odd[i];
        v[i + n / 2] = even[i] - omega * odd[i];
        omega *= omega1;
    }
}

vector<ll> multiplyPolynomials(vector<ll> &a, vector<ll> &b) {
    int n = 1;
    while (n < a.size() || n < b.size()) n *= 2;
    n *= 2;
    
    vector<C> v[2];
    rep(j, 0, 2) {
        for (auto x : (j ? b : a)) v[j].push_back(x);
        v[j].resize(n, 0);
        fft(n, v[j], false);
    }
    
    rep(i, 0, n) v[0][i] *= v[1][i];
    fft(n, v[0], true);
    vector<ll> res(n);
    rep(i, 0, n) res[i] = llround(v[0][i].real() / n);
    return res;
}
