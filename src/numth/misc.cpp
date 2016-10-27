#include "../base.hpp"
#include "misc.hpp"

int main() {
	int a = 563982, b = 25934821, c = 179523;
	printf("%d\n", (int) fastexp(a, b, c));
	// 22302

	rep(i, 0, 1000000)
		fastexp(rand(), rand(), rand());
}
