/**
 * Author: Václav Volhejn
 * Source: KACTL notebook (various/chapter.tex)
 * Status: Tested manually, forAllSubsetMasks tested at Ptz
 * Description: Various bit manipulation functions/snippets.
 */
#include "../base.hpp"

int lowestSetBit(int x) { return x & -x }

void forAllSubsetMasks(int m) { // Including m itself
    for (int x = m; x; --x &= m) { /* ... */ }
}

int nextWithSamePopcount(int x) { // 3->5->6->9->10->12->17...
    int c = x&-x, r = x+c;
    return (((r^x) >> 2)/c) | r;
}

// For each mask, compute sum of values D[1<<i] of its set bits i
void sumsOfSubsets() {
    int K = 3;
    vector<int> D(1<<K, 0);
    D[1] = 4; D[2] = 3; D[4] = 8;
    rep(b,0,K) rep(i,0,(1 << K)) if (i & 1 << b) D[i] += D[i^(1 << b)];
}
