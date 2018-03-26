// compute distance: point A, line (B,C):
T distance_point_line(const Bod &A, const Bod &B, const Bod &C) {
  Bod N ( -imag(B-C), real(B-C) );
  normalize(N);
  T tmp = dot_product(N,B-A);
  return abs(tmp);
}

// compute distance: point A, segment [B,C]:
T distance_point_segment(const Bod &A, const Bod &B, const Bod &C) {
  T res = min( size(B-A), size(C-A) );
  Bod N ( -imag(B-C), real(B-C) );
  normalize(N);
  T tmp = dot_product(N,B-A);
  Bod paeta = A + tmp*N;
  if (is_on_segment(B,C,paeta)) res = min(res, abs(tmp));
  return res; 
}

// compute distance: line (A,B), line (C,D): 
T distance_line_line(const Bod &A, const Bod &B, const Bod &C, const Bod &D) {
  if (!colinear(B-A,D-C)) return 0.0; else return distance_point_line(A,C,D);
}

// compute distance: segment [A,B], line (C,D): 
T distance_segment_line(const Bod &A, const Bod &B, const Bod &C, const Bod &D) {
  if (! is_positive( cross_product(D-C,A-C) * cross_product(D-C,B-C) )) return 0; // they intersect
  return min( distance_point_line(A,C,D), distance_point_line(B,C,D) );
}

// compute distance: segment [A,B], segment [C,D]:
T distance_segment_segment(const Bod &A, const Bod &B, const Bod &C, const Bod &D) {
  vector<Bod> isect = intersect_segment_segment(A,B,C,D);
  if (isect.size()) return 0; // they intersect
  T res = distance_point_segment(A,C,D);
  res = min(res, distance_point_segment(B,C,D));
  res = min(res, distance_point_segment(C,A,B));
  res = min(res, distance_point_segment(D,A,B));
  return res; 
}
