
template<class T> T twice_signed_poly_area(const vector< complex<T> > &V) { 
  T res = 0; 
  for (unsigned int i=0; i<V.size(); i++) res += cross_product( V[i], V[(i+1)%V.size()] );
  return res; 
}

template<class T> complex<T> center_of_mass(const vector< complex<T> > &V ) {
  complex<T> sum(0,0);
  T twice_area = 0.0;
  for (unsigned i=0; i<V.size(); i++) {
    sum += cross_product( V[i], V[(i+1)%V.size()] ) * ( V[i] + V[(i+1)%V.size()] );
    twice_area += cross_product( V[i], V[(i+1)%V.size()] );
  }
  sum *= 1.0 / (3.0 * twice_area);
  return sum;
}

// compute a CCW convex hull with no unnecessary points:
template<class T> vector< complex<T> > convex_hull( vector< complex<T> > V ) { 
  // handle boundary cases
  if (V.size() == 2) if (are_equal(V[0],V[1])) V.pop_back();
  if (V.size() <= 2) return V;
  // find the bottommost point -- this can be optimized!
  sort(V.begin(), V.end(), compare_YX<COORD_TYPE> );
  complex<T> offset = V[0];
  for (unsigned int i=0; i<V.size(); i++) V[i] -= offset;
  sort(V.begin()+1, V.end(), compare_arg<COORD_TYPE> );

  int count = 2;
  vector<int> hull(V.size()+2);
  for (unsigned int i=0; i<2; i++) hull[i]=i;
  for (unsigned int i=2; i<V.size(); i++) {
    while (count>=2 && !counterclockwise( V[hull[count-2]], V[hull[count-1]], V[i] ) ) count--;
    hull[count++]=i;
  }
  vector< complex<T> > res;
  for (int i=0; i<count; i++) res.push_back( V[hull[i]] + offset );
  if (res.size()==2) if (are_equal(res[0],res[1])) res.pop_back();
  return res;
}

// winding number of a poly around a point (not on its boundary):
template<class T> int winding_number( const complex<T> &bod, const vector< complex<T> > &V ) {
  int wn = 0;
  for (unsigned int i=0; i<V.size(); i++) {
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
template<class T> int is_inside( const complex<T> &bod, const vector< complex<T> > &V ) { 
  for (unsigned i=0; i<V.size(); i++) if (is_on_segment(V[i],V[(i+1)%V.size()],bod)) return true;
  return winding_number(bod,V) != 0; 
}

template<class T> bool is_poly_convex(const vector< complex<T> > &V) {
  int cw=0, ccw=0;
  unsigned int N = V.size();
  for (int i=0; i<N; i++) if (clockwise(V[i],V[(i+1)%N],V[(i+2)%N])) { cw=1; break; }
  for (int i=0; i<N; i++) if (counterclockwise(V[i],V[(i+1)%N],V[(i+2)%N])) { ccw=1; break; }
  return (! (cw && ccw));
}
