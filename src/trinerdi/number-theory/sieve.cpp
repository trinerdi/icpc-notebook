/**
 * Name: Sieve of Eratosthenes
 * Author: Richard Hladik
 * Description: Sieve of Eratosthenes for finding primes up to m (inclusive).
 * Time: $O(n \log \log n)$
 */
#include "../base.hpp"

vector<bool> sieve(int m) {
    m++;
    vector<bool> is_p(m, true);
    is_p[0] = is_p[1] = false;
    rep(i, 2, m)
        if (is_p[i])
            for (int j = 2 * i; j < m; j += i)
                is_p[j] = false;
    return is_p;
}
