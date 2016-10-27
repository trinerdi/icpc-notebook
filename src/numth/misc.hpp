/* Fast exponentiation modulo mod
 * Time complexity: O(log p), space complexity: O(1) */
ll fastexp(ll a, ll p, ll mod) {
	if (p == 0)
		return 1;

	ll res = fastexp(a, p / 2, mod);
	res = (res * res) % mod;
	return (p % 2) ? (res * a) % mod : res;
}
