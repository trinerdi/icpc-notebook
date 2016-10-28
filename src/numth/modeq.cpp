#include "../base.hpp"
#include "modeq.hpp"

ll llrand() {
	return max((((ll)lrand48()) << 31) + lrand48(), 1LL);
}

int main() {
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
}
