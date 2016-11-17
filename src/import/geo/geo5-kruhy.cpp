// intersect circles (C1,r1) and (C2,r2), 3 pts returned if \equiv:
vector<Bod> intersect_circle_circle(const Bod &C1, T r1, const Bod &C2, T r2) {
  vector<Bod> res;

  if (are_equal(C1,C2)) {
    // 2x the same point
    if (is_zero(r1) && is_zero(r2)) { res.push_back(C1); return res; } 
    // identical circles -- return 3 points
    if (is_zero(r1-r2)) { res.push_back(C1); res.push_back(C1); res.push_back(C1); return res; }
    // no intersection
    return res;
  }
    
  T d = sqrt(square_size(C2-C1));
  // check for no intersection
  if (is_positive(d-r1-r2) || is_positive(r1-r2-d) || is_positive(r2-r1-d)) return res; 
  // check for a single intersection
  if (is_zero(d-r1-r2)) { res.push_back( (1.0/d) * ( r2*C1 + r1*C2 ) ); return res; }
  if (is_zero(r1-r2-d)) { res.push_back( C1 + (r1/d) * (C2-C1) ); return res; }
  if (is_zero(r2-r1-d)) { res.push_back( C2 + (r2/d) * (C1-C2) ); return res; }
  // general case: compute x and y offset of the intersections    
  T x = ( d*d - r2*r2 + r1*r1 ) / (2*d);
  T y = sqrt( 4*d*d*r1*r1 - ( d*d - r2*r2 + r1*r1 )*( d*d - r2*r2 + r1*r1 ) ) / (2*d);
  // I = (C1,C2) \cap chord, N = normal vector
  Bod I = (1.0/d) * ( (d-x)*C1 + x*C2 );
  Bod N( imag(C2-C1), -real(C2-C1) );
  T Nsize = sqrt(square_size(N));
  N = N * (1/Nsize);
  // compute and return the points in lexicographic order
  Bod I1 = I + y*N, I2 = I - y*N;
  if (is_positive(real(I1)-real(I2))) swap(I1,I2);
  if (is_zero(real(I1)-real(I2))) if (is_positive(imag(I1)-imag(I2))) swap(I1,I2);
  res.push_back(I1);
  res.push_back(I2);
  return res;
}

// circle through three points A,B,C (smallest enclosing circle for colinear):
Bod circumcircle_center(const Bod &A, const Bod &B, const Bod &C) {
  T a = 0, bx = 0, by = 0;
  a += real(A) * imag(B) + real(B) * imag(C) + real(C) * imag(A);
  a -= real(B) * imag(A) + real(C) * imag(B) + real(A) * imag(C);
  if (is_zero(a)) { 
    if (is_on_segment(A,B,C)) return 0.5*(A+B); 
    if (is_on_segment(A,C,B)) return 0.5*(A+C); 
    return 0.5*(B+C); 
  }
  bx += square_size(A) * imag(B) + square_size(B) * imag(C) + square_size(C) * imag(A);
  bx -= square_size(B) * imag(A) + square_size(C) * imag(B) + square_size(A) * imag(C);
  by -= square_size(A) * real(B) + square_size(B) * real(C) + square_size(C) * real(A);
  by += square_size(B) * real(A) + square_size(C) * real(B) + square_size(A) * real(C);
  return Bod ( bx / (2*a) , by / (2*a) );
}

// rotate(point,center,CCW angle):
Bod rotate_point(const Bod &bod, const Bod &stred, T uhol) { 
  Bod mul(cos(uhol),sin(uhol));
  return ((bod-stred)*mul)+stred; 
}

// angle on the left side of B in polyline A->B->C:
T left_side_angle(const Bod &A, const Bod &B, const Bod &C) {
  double a1 = atan2( imag(A-B), real(A-B) );
  double a2 = atan2( imag(C-B), real(C-B) );
  double u = a1 - a2;
  if (u < 0) u += 2*M_PI;
  if (u >= 2*M_PI) u -= 2*M_PI;
  return u;
}
