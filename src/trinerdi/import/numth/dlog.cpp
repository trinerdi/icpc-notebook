/**
 * Name: Discrete logarithm
 * Author: Charles University Team
 * Description: Return a possible $\log_A B \mod P$ or $-1$ if none exists.
 *  $P$ must be prime and $1 < A < P < 2^{31}$.
 * Time: $O(\sqrt{P} \log P)$
 */
#include "../../base.hpp"
#include "../../number-theory/fastexp.cpp"

/// Shanks' algorithm
ll dlog(ll A, ll B, ll P) {
  ll M = (ll)ceil(sqrt(P-1.0));

  vector< pair<ll, int> > P1, P2;
  ll pom = fastexp(A,M,P);
  
  P1.push_back(make_pair(1,0));
  for (int i=1; i<M; i++) P1.push_back(make_pair( (P1[i-1].first * pom)%P ,i)); 
  sort(P1.begin(), P1.end());

  ll Ainv = fastexp(A,P-2,P);
  P2.push_back(make_pair(B,0));
  for (int i=1; i<M; i++) P2.push_back(make_pair( (P2[i-1].first * Ainv)%P, i));
  sort(P2.begin(), P2.end());
  
  int i,j;
  for (i=0, j=0; P1[i].first != P2[j].first; ) {
    if (P1[i].first < P2[j].first) i++; else j++;
    if ( i==M || j==M ) return -1;
  }
  return ( M * P1[i].second + P2[j].second ) % (P-1);
}
