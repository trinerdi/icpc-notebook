/* Extended Euclid's algorithm that yields Bézout's coefficients -- numbers u,
 * v such that a * u + b * v = gcd(a, b)
 * Time complexity: O(log a + log b), space complexity: O(1) */
pair<ll, ll> extgcd(ll a, ll b) {
	ll Aa = 1, Ab = 0; // a' = Aa * a + Ab * b
	ll Ba = 0, Bb = 1; // b' = Ba * a + Bb * b
	if (a < b)
		swap(a, b), swap(Aa, Ab), swap(Ba, Bb);

	while (b) {
		ll c = a / b;
		Aa -= c * Ba;
		Ab -= c * Bb;
		a = a % b;
		swap(Aa, Ba), swap(Ab, Bb), swap(a, b);
	}

	return {Aa, Ab};
}
