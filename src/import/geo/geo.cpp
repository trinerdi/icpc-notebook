#define EPSILON (1e-7)
// epsilon used for computations involving doubles ; dec to 1e-9 for %Lf

typedef ll T;
typedef Bod complex<T>;

const double PI = acos(-1);
// Chceme pouzivat complex<ll> misto complex<int> kvuli cross productu a square_size
bool is_negative(double x) { return x < -EPSILON; }
bool is_zero(double x) { return abs(x) <= EPSILON; }
bool is_positive(double x) { return x > EPSILON; }
int signum(const T &A) {
	return (is_zero(A)) ? 0 : (is_negative(A)) ? -1 : 1;
}

bool are_equal(const Bod &A, const Bod &B) {
	return is_zero(real(B) - real(A)) && is_zero(imag(B) - imag(A));
}

T square_size(const Bod &A) { return real(A)*real(A) + imag(A)*imag(A); }
T size(const Bod &A) { return sqrt(real(A)*real(A) + imag(A)*imag(A)); }
T dot_product(const Bod &A, const Bod &B) {
	return real(A)*real(B) + imag(A)*imag(B);
}
T cross_product(const Bod &A, const Bod &B) {
	return real(A)*imag(B) - real(B)*imag(A);
}
void normalize(Bod &A) { T Asize = size(A); A *= (1/Asize); }
bool clockwise(const Bod &A, const Bod &B, const Bod &C) {
	return is_negative( cross_product( B-A, C-A ));
}
bool counterclockwise(const Bod &A, const Bod &B, const Bod &C) {
	return clockwise(C, B, A);
}

// Pokud nas netrapi kolinearita a [0, 0] (+ztrata presnosti u ll), staci porovnat atan2
bool compare_arg(const Bod &A, const Bod &B) { //ok
	// [0,0] ide uplne na zaciatok
	if (are_equal(B,Bod(0,0))) return 0;
	if (are_equal(A,Bod(0,0))) return 1;
	// chceme poradie: pod osou x zlava doprava, kladna poloos, nad osou sprava dolava, zaporna poloos
	int sgnA = signum(imag(A));
	int sgnB = signum(imag(B));
	if (sgnA == 0 && signum(real(A))<0) sgnA = 2;
	if (sgnB == 0 && signum(real(B))<0) sgnB = 2;
	if (sgnA != sgnB) return (sgnA < sgnB);
	// v ramci polroviny sortime podla clockwise
	if (counterclockwise(Bod(0, 0), A,B)) return 1;
	if (clockwise(Bod(0, 0), A,B)) return 0;
	// a ak sa este nerozhodlo, podla vzdialenosti, blizsie skor
	return square_size(A) < square_size(B);
}
bool compare_XY(const Bod &A, const Bod &B) {
	if (!is_zero(real(A)-real(B))) return is_negative(real(A)-real(B));
	return is_negative(imag(A)-imag(B));
}
bool compare_YX(const Bod &A, const Bod &B) { //pouziva convex_hull
	if (!is_zero(imag(A)-imag(B))) return is_negative(imag(A)-imag(B));
	return is_negative(real(A)-real(B));
}

bool colinear(const Bod &A, const Bod &B, const Bod &C) {
	return is_zero(cross_product(B-A, C-A));
}

// safe test whether a point C \in [A,B], C \in (A,B)
bool is_on_segment(const Bod &A, const Bod &B, const Bod &C) {
	if (!colinear(A,B,C)) return 0;
	return !is_positive(dot_product(A-C, B-C));
}
bool is_inside_segment(const Bod &A, const Bod &B, const Bod &C) {
	if (!colinear(A,B,C)) return 0;
	return is_negative(dot_product(A-C,B-C));
}

int main() {
	srand(time(NULL));


	return 0;
}
