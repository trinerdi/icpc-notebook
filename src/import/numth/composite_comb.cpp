#define MAXC 111111
#define MAX_PRIMES 20
ll MOD = 1000000007;
int fac[MAX_PRIMES][MAXC], ifac[MAX_PRIMES][MAXC];

int PRIMES = 4, primes[5] = {3, 11, 29, 1609261};

ll get_comb(int n, int k, int p) {
    if (n < k) return 0;
    ll ans = 1;
    int pr = primes[p];
    while (n) {
        // Lucas theorem (binomial mod prime) - decompose n, k on digits in base p
        int nn = n % pr, kk = k % pr;
        n /= pr; k /= pr;
        // ans *= comb(nn, kk)
        ans = ans * fac[p][nn] % pr * ifac[p][kk] % pr * ifac[p][nn - kk] % pr;
    }
    return ans;
}

ll get_comb(int n, int k) {
    ll ans = 0, mod = 1;
    FOR(p, PRIMES) {
        ll a1 = ans, n1 = mod, a2 = get_comb(n, k, p), n2 = primes[p];
        mod = n1 * n2;
        // Chinese remainder theorem
        // x = a1 (mod n1) && x = a2 (mod n2)  =>  x = ans (mod n1 * n2)
        ans = (((a1 * n2) % mod * power(n2, n1 - 2, n1)) % mod +
               ((a2 * n1) % mod * power(n1, n2 - 2, n2)) % mod) % mod;
    }
    return ans;
}

int composite_comb(int N, int K, int mod) {
    MOD = mod;

    // TODO: Factorize mod and create primes

    FOR(p, PRIMES) { // Precalculates factorials and inverses
        int pr = primes[p];
        fac[p][0] = 1;
        FOR(i, pr) fac[p][i + 1] = ((ll)fac[p][i] * (i+1)) % pr;
        ifac[p][pr - 1] = power(fac[p][pr - 1], pr - 2, pr);
        per(i, pr - 1, 0) ifac[p][i] = ((ll)ifac[p][i+1]*(i+1)) % pr;
    }

    int ans = 0;
    FOR(i, 2 * N) {
        int n = min(K, i), k = N - 1;
        ans = (ans + get_comb(n, k)) % MOD;
    }
    return (((ll)ans * N) % MOD * N) % MOD;
}
