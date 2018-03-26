#include "../base.hpp"

/* Extended Euclid's algorithm that yields Bézout's coefficients -- numbers u,
 * v such that a * u + b * v = gcd(a, b)
 * Time complexity: O(log a + log b), space complexity: O(1) */
pair<ll, ll> extgcd(ll a, ll b) {
	complex<ll> A = {1, 0}, B = {0, 1};
	// a' = R(A) * a + I(A) * b, b' = R(B) * b + I(B) * a

	while (b)
		A -= (a / b) * B, a %= b, swap(a, b), swap(A, B);

	return {real(A), imag(A)};
}

/* "Regular" Euclid's algorithm that returns gcd(a, b)
 * Time complexity: O(log a + log b), space complexity: O(1) */
ll gcd(ll a, ll b) {
	while (b)
		a %= b, swap(a, b);
	return a;
}

/* Solves the modular equality ak \equiv b (mod m), returns 0 <= k < m or -1
 * if there's no solution
 * TODO: doesn't work for m >= 2^32
 * Time complexity: O(log m), space complexity: O(1) */
ll solve_modeq(ll a, ll b, ll m) {
	// We have a * k + m * y = b for unknown k and y
	a %= m, b %= m;
	ll g = gcd(a, m);
	if (b % g)
		return -1;

	ll t = b / g;
	ll k = extgcd(a, m).first * t;
	return (k % m + m) % m;
}

/* Given k, returns its modular inverse, 0 < k^-1 < m, such that k * k^-1
 * \equiv 1 (mod m), or -1 if no such k^-1 exists
 * Time complexity: O(log m), space complexity: O(1) */
ll modular_inverse(ll a, ll m) {
	return solve_modeq(a, 1, m);
}
