#include "gtest/gtest.h"
#include "../../kactl/number-theory/ModSqrt.cpp"
#include "../../kactl/number-theory/eratosthenes.h"

TEST(MOD_SQRT, SmallValues) {
    auto primes = eratosthenes_sieve(300);
    for(int p : primes) {
        unordered_set<int> sqrtable;
        rep(a,0,p) sqrtable.insert(a*a);
        for(int a : sqrtable) {
            int s = sqrt(a, p);
            EXPECT_EQ((s*s)%p, a % p);
        }
    }
}
