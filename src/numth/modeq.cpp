#include "../base.hpp"

/* Extended Euclid's algorithm that yields Bézout's coefficients -- numbers u,
 * v such that a * u + b * v = gcd(a, b)
 * Time complexity: O(log a + log b), space complexity: O(1) */
pair<ll, ll> extgcd(ll a, ll b) {
	ll Aa = 1, Ab = 0; // a' = Aa * a + Ab * b
	ll Ba = 0, Bb = 1; // b' = Ba * a + Bb * b

	while (b) {
		ll c = a / b;
		Aa -= c * Ba;
		Ab -= c * Bb;
		a = a % b;
		swap(Aa, Ba), swap(Ab, Bb), swap(a, b);
	}

	return {Aa, Ab};
}

/* "Regular" Euclid's algorithm that returns gcd(a, b)
 * Time complexity: O(log a + log b), space complexity: O(1) */
ll gcd(ll a, ll b) {
	ll u, v;
	tie(u, v) = extgcd(a, b);
	return u * a + v * b;
}

/* Solves the modular equality ak \equiv b (mod m), returns 0 <= k < m or -1
 * if there's no solution
 * Time complexity: O(log m), space complexity: O(1) */
ll solve_modeq(ll a, ll b, ll m) {
	// We have a * k + m * y = b for unknown k and y
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
