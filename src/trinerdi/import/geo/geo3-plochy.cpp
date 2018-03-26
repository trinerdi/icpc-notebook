#include <geo.cpp>

T twice_signed_poly_area(const vector<Bod> &V) { 
  T res = 0; 
  rep(i, 0, V.size()) res += cross_product( V[i], V[(i+1)%V.size()] );
  return res; 
}

Bod center_of_mass(const vector<Bod> &V ) {
  Bod sum(0,0);
  T twice_area = 0.0;
  rep(i, 0, V.size()) {
    sum += cross_product( V[i], V[(i+1)%V.size()] ) * ( V[i] + V[(i+1)%V.size()] );
    twice_area += cross_product( V[i], V[(i+1)%V.size()] );
  }
  sum *= 1.0 / (3.0 * twice_area);
  return sum;
}

// compute a CCW convex hull with no unnecessary points:
vector<Bod> convex_hull( vector<Bod> V ) { 
  // handle boundary cases
  if (V.size() == 2) if (are_equal(V[0],V[1])) V.pop_back();
  if (V.size() <= 2) return V;
  // find the bottommost point -- this can be optimized!
  sort(V.begin(), V.end(), compare_YX<COORD_TYPE> );
  Bod offset = V[0];
  rep(i, 0, V.size()) V[i] -= offset;
  sort(V.begin()+1, V.end(), compare_arg<COORD_TYPE> );

  int count = 2;
  vector<int> hull(V.size()+2);
  rep(i, 0, 2) hull[i]=i;
  rep(i, 2, V.size()) {
    while (count>=2 && !counterclockwise( V[hull[count-2]], V[hull[count-1]], V[i] ) ) count--;
    hull[count++]=i;
  }
  vector<Bod> res;
  rep(i, 0, count) res.push_back( V[hull[i]] + offset );
  if (res.size()==2) if (are_equal(res[0],res[1])) res.pop_back();
  return res;
}

// winding number of a poly around a point (not on its boundary):
int winding_number( const Bod &bod, const vector<Bod> &V ) {
  int wn = 0;
  rep(i, 0, V.size()) {
    if (! is_positive( imag(V[i]) - imag(bod) )) {
      if (is_positive( imag(V[(i+1)%V.size()]) - imag(bod) ))
        if (counterclockwise( V[i], V[(i+1)%V.size()], bod )) ++wn;
    } else {
      if (! is_positive( imag(V[(i+1)%V.size()]) - imag(bod) ))
        if (clockwise( V[i], V[(i+1)%V.size()], bod )) --wn;
    }
  }
  return wn;
}

// test whether a point is inside a polygon
int is_inside( const Bod &bod, const vector<Bod> &V ) { 
  rep(i, 0, V.size()) if (is_on_segment(V[i],V[(i+1)%V.size()],bod)) return true;
  return winding_number(bod,V) != 0; 
}

bool is_poly_convex(const vector<Bod> &V) {
  int cw=0, ccw=0;
  unsigned int N = V.size();
  rep(i, 0, N) if (clockwise(V[i],V[(i+1)%N],V[(i+2)%N])) { cw=1; break; }
  rep(i, 0, N) if (counterclockwise(V[i],V[(i+1)%N],V[(i+2)%N])) { ccw=1; break; }
  return (! (cw && ccw));
}
