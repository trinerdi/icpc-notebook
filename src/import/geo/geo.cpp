#define EPSILON (1e-7) // epsilon used for computations involving doubles ; dec to 1e-9 for %Lf 
const double PI = acos(-1);
// Chceme pouzivat complex<long long> misto complex<int> kvuli cross productu a square_size
bool is_negative(double x) { return x < -EPSILON; } 
bool is_zero(double x) { return abs(x) <= EPSILON; } 
bool is_positive(double x) { return x > EPSILON; }
template<class T> int signum(const T &A) { 
  if (is_zero(A)) return 0; if (is_negative(A)) return -1; return 1; 
}
template<class T> bool are_equal(const complex<T> &A, const complex<T> &B) { 
  return is_zero(real(B)-real(A)) && is_zero(imag(B)-imag(A)); 
}

template<class T> T square_size(const complex<T> &A) { return real(A)*real(A) + imag(A)*imag(A); }
template<class T> T size(const complex<T> &A) { return sqrt(real(A)*real(A) + imag(A)*imag(A)); }
template<class T> T dot_product(const complex<T> &A, const complex<T> &B) { 
  return real(A)*real(B) + imag(A)*imag(B); 
}
template<class T> T cross_product(const complex<T> &A, const complex<T> &B) { 
  return real(A)*imag(B) - real(B)*imag(A); 
}
template<class T> void normalize(complex<T> &A) { T Asize = size(A); A *= (1/Asize); }
template<class T> bool clockwise(const complex<T> &A, const complex<T> &B, const complex<T> &C) { 
  return is_negative( cross_product( B-A, C-A )); 
}
template<class T> bool counterclockwise(const complex<T> &A, const complex<T> &B, const complex<T> &C) {
	return clockwise(C, B, A);
}

// Pokud nas netrapi kolinearita a [0, 0] (+ztrata presnosti u ll), staci porovnat atan2
template<class T> bool compare_arg(const complex<T> &A, const complex<T> &B) { //ok
  // [0,0] ide uplne na zaciatok
  if (are_equal(B,complex<T>(0,0))) return 0;
  if (are_equal(A,complex<T>(0,0))) return 1;
  // chceme poradie: pod osou x zlava doprava, kladna poloos, nad osou sprava dolava, zaporna poloos
  int sgnA = signum(imag(A));
  int sgnB = signum(imag(B));
  if (sgnA == 0) if (signum(real(A))<0) sgnA = 2;
  if (sgnB == 0) if (signum(real(B))<0) sgnB = 2;
  if (sgnA != sgnB) return (sgnA < sgnB);
  // v ramci polroviny sortime podla clockwise
  if (counterclockwise(complex<T>(0, 0), A,B)) return 1;
  if (clockwise(complex<T>(0, 0), A,B)) return 0;
  // a ak sa este nerozhodlo, podla vzdialenosti, blizsie skor
  return (square_size(A) < square_size(B));
}
template<class T> bool compare_XY(const complex<T> &A, const complex<T> &B) { 
  if (!is_zero(real(A)-real(B))) return (is_negative(real(A)-real(B))); 
  return (is_negative(imag(A)-imag(B))); 
}
template<class T> bool compare_YX(const complex<T> &A, const complex<T> &B) { //pouziva convex_hull
  if (!is_zero(imag(A)-imag(B))) return (is_negative(imag(A)-imag(B))); 
  return (is_negative(real(A)-real(B))); 
}

template<class T> bool colinear(const complex<T> &A, const complex<T> &B, const complex<T> &C) { 
  return is_zero( cross_product( B-A, C-A )); 
}

// safe test whether a point C \in [A,B], C \in (A,B)
template<class T> bool is_on_segment(const complex<T> &A, const complex<T> &B, const complex<T> &C) { 
  if (!colinear(A,B,C)) return 0; 
  return ! is_positive( dot_product(A-C,B-C) ); 
}
template<class T> bool is_inside_segment(const complex<T> &A, const complex<T> &B, const complex<T> &C) { 
  if (!colinear(A,B,C)) return 0; 
  return is_negative( dot_product(A-C,B-C) ); 
}

typedef complex<int> cd;
#define REP(i, n) for(int i = 0; i < n; i++)
int main() {
	srand(time(NULL));


	return 0;
}
