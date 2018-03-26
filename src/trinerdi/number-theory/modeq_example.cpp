#include "../base.hpp"
#include "modeq.cpp"

int main() {
	printf("gcd\n");
	ll d = 129352523LL * 169352, e = 129352523LL * 5293527;
	// 2270579 -72641 129352523
	ll u, v;
	tie(u, v) = extgcd(d, e);
	printf("%lld %lld %lld\n", u, v, u * d + v * e);
	rep(i, 0, 500000){
		ll f = llrand(), g = llrand();
		tie(u, v) = extgcd(f, g);
		ll div = f * u + g * v;
		if (div != gcd(f, g))
			printf("Inconsistency between extended and regular gcd: %lld != %lld", div, gcd(f, g));

		if (f % div || g % div)
			printf("%lld doesn't divide both numbers: %lld %lld\n", div, f, g);
	}

	printf("\nsolve modeq\n");
	rep(i, 0, 500000){
		ll a = rand(), b = rand(), p = max(rand(), 2);
		ll k = solve_modeq(a, b, p);
		if (k == -1)
			continue; // For now assume this is correct

		if ((a * k - b) % p)
			printf("Invalid solution: %lld * %lld \\equiv %lld (mod %lld) doesn't hold\n", a, k, b, p);
	}
}
