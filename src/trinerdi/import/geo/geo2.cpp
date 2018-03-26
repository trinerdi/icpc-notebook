#include "geo.cpp"
// intersect lines (A,B) and (C,D), return 2 pts if identical: (WORKS ONLY FOR DOUBLES!!)
vector<Bod> intersect_line_line(const Bod &A, const Bod &B, const Bod &C, const Bod &D) {
  vector<Bod> res;
  Bod U = B-A, V = D-C;
  if (colinear(Bod(0, 0), U,V)) { // identical or parallel
    if (colinear(Bod(0, 0), U,C-A)) { res.push_back(A); res.push_back(B); }
    return res;
  }
  // one intersection point (WORK ONLY FOR DOUBLES!!!)
  T k = ( cross_product(C,V) - cross_product(A,V) ) / cross_product(U,V);
  res.push_back(A + k*U);
  return res;
}

// intersect a poly and a halfplane to the left of [A,B):
vector<Bod> intersect_poly_halfplane(const vector<Bod> &V, const Bod &A, const Bod &B) { 
  int N = V.size();
  vector<Bod> res;

  if (N == 0) return res;
  if (N == 1) if (! clockwise(A,B,V[0]) ) return V; else return res;

  rep(i, 0, N) {
    if (! clockwise(A,B,V[i])) res.push_back(V[i]);
    int intersects = 0;
    if (counterclockwise(A,B,V[i])) if (clockwise(A,B, V[(i+1)%N] )) intersects = 1;
    if (clockwise(A,B,V[i])) if (counterclockwise(A,B, V[(i+1)%N] )) intersects = 1;
    if (intersects) {
      poly tmp = intersect_line_line(A,B,V[i], V[(i+1)%N] );
      res.push_back( tmp[0] ); // vieme, ze ma len jeden bod
    }
  }
  return res;
}

// intersect segments [A,B] and [C,D], may return endpoints of a segment:
vector<Bod> intersect_segment_segment(const Bod &A, const Bod &B, const Bod &C, const Bod &D) {
  vector<Bod> res;

  Bod U = B-A, V = D-C, W = C-A, X = D-A;
  if (colinear(U,V)) { // parallel
    // check for degenerate cases
    if (are_equal(A,B)) { if (is_on_segment(C,D,A)) res.push_back(A); return res; }
    if (are_equal(C,D)) { if (is_on_segment(A,B,C)) res.push_back(C); return res; }
    // two parallel segments
    if (!colinear(U,W)) return res; // not on the same line
    
    T ssU = square_size(U), ssW = square_size(W), ssX = square_size(X);

    // does A coincide with C or D? 
    
    if (is_zero(ssW)) {
      res.push_back(A);
      if (is_negative(dot_product(U,X))) return res; // B, D on different sides 
      if (is_negative(ssU-ssX)) res.push_back(B); else res.push_back(D); 
      return res;
    }
    if (is_zero(ssX)) {
      res.push_back(A);
      if (is_negative(dot_product(U,W))) return res; // B, C on different sides
      if (is_negative(ssU-ssW)) res.push_back(B); else res.push_back(C); 
      return res;
    }
    
    if (is_inside_segment(C,D,A)) {
      // A is inside CD, intersection is [A,?] 
      res.push_back(A);
      if (is_positive(dot_product(U,W))) { // B,C on the same side 
        if (is_negative(ssU-ssW)) res.push_back(B); else res.push_back(C); 
        return res;
      } else { // B,D on the same side 
        if (is_negative(ssU-ssX)) res.push_back(B); else res.push_back(D); 
        return res;
      }
    } else {
      // segment CD is strictly on one side of A
      if (ssW < ssX) {
        // A_C_D
        if (is_negative(dot_product(U,W))) return res; // B is on the other side
        if (is_negative(ssU-ssW)) return res; // B before C
        if (are_equal(B,C)) { res.push_back(B); return res; }
        res.push_back(C);
        if (is_negative(ssU-ssX)) res.push_back(B); else res.push_back(D); 
        return res;
      } else {
        // A_D_C
        if (is_negative(dot_product(U,X))) return res; // B is on the other side 
        if (is_negative(ssU-ssX)) return res; // B before D
        if (are_equal(B,D)) { res.push_back(B); return res; }
        res.push_back(D);
        if (is_negative(ssU-ssW)) res.push_back(B); else res.push_back(C); 
        return res;
      }
    }
  }    
  // not parallel, at most one intersection point
  T k = ( cross_product(C,V) - cross_product(A,V) ) / cross_product(U,V);
  Bod cand = A + k*U;
  if (is_on_segment(A,B,cand) && is_on_segment(C,D,cand)) res.push_back(cand);
  return res;
}
