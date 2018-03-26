// lexicographic order for pairs and triples
inline bool leq(int a1, int a2, int b1, int b2) { return(a1 < b1 || (a1 == b1 && a2 <= b2)); }
inline bool leq(int a1, int a2, int a3, int b1, int b2, int b3) { return(a1 < b1 || (a1 == b1 && leq(a2,a3, b2,b3))); }

// stably sort a[0..n-1] to b[0..n-1] with keys in 0..K from r
static void radixPass(int* a, int* b, int* r, int n, int K) {
    int* c = new int[K + 1];
    rep(i,0,K + 1) c[i] = 0;
    rep(i,0, n) ++c[r[a[i]]];
    for (int i=0, sum = 0; i <= K; ++i) { int t=c[i]; c[i]=sum; sum+=t; }
    rep(i,0,n) b[c[r[a[i]]]++] = a[i];
    delete[] c;
}
#define GetI() (SA12[t] < n0 ? SA12[t] * 3 + 1 : (SA12[t] - n0) * 3 + 2)

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// find the suffix array SA of s[0..n-1] in {1..K}^n 
// require s[n]=s[n+1]=s[n+2]=0, n>=2
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void suffixArray(int* s, int* SA, int n, int K) {
  int n0=(n+2)/3, n1=(n+1)/3, n2=n/3, n02=n0+n2;
  int* s12 = new int[n02 + 3];  s12[n02]  = s12[n02+1]  = s12[n02+2]=0;
  int* SA12 = new int[n02 + 3]; SA12[n02] = SA12[n02+1] = SA12[n02+2]=0;
  int* s0 = new int[n0];
  int* SA0 = new int[n0];
  
  for (int i=0, j=0; i < n+(n0-n1); ++i) if (i%3 != 0) s12[j++] = i;
  radixPass(s12 , SA12, s+2, n02, K);
  radixPass(SA12, s12 , s+1, n02, K);
  radixPass(s12 , SA12, s  , n02, K);

  int name = 0, c0 = -1, c1 = -1, c2 = -1;
  FOR(i,n02) {
    if (s[SA12[i]] != c0 || s[SA12[i]+1] != c1 || s[SA12[i]+2] != c2)
    { ++name; c0 = s[SA12[i]]; c1 = s[SA12[i]+1]; c2 = s[SA12[i]+2]; }
    if (SA12[i] % 3 == 1) s12[SA12[i]/3] = name; else s12[SA12[i]/3 + n0] = name;
  }

  if (name < n02) {
    suffixArray(s12, SA12, n02, name);
    FOR(i,n02) s12[SA12[i]] = i + 1;
  } else FOR(i,n02) SA12[s12[i] - 1] = i;

  for (int i=0, j=0; i < n02; ++i) if (SA12[i] < n0) s0[j++] = 3*SA12[i];
  radixPass(s0, SA0, s, n0, K);

  for (int p=0, t=n0-n1, k=0; k < n; ++k) {
    int i = GetI(), j = SA0[p];
    if (SA12[t] < n0 ?
      leq(s[i], s12[SA12[t] + n0], s[j],              s12[j/3]) :
      leq(s[i], s[i+1],            s12[SA12[t]-n0+1], s[j],    s[j+1], s12[j/3+n0]))
    {
      SA[k] = i; ++t; if (t == n02) for (++k; p < n0; ++p, ++k) SA[k] = SA0[p];
    } else {
      SA[k] = j; ++p; if (p == n0) for (++k; t < n02; ++t, ++k) SA[k] = GetI();
    }
  }
  delete [] s12; delete [] SA12; delete [] SA0; delete [] s0;
}

// find the longest common prefixes:
// lcp[0]=0, lcp[i] = longest common prefix of suffixes starting at sa[i-1] and sa[i]
// je jedno, jestli s je string v lowercase nebo cisla
// pomaly algoritmus vyplivne sa jako strukturu, potreba pridat .idx
void findLCP(int* s, int* sa, int* lcp, int n) {//suffix u pomaleho pole
    lcp[0]=0;
    int* rank = new int[n];
    FOR(i,n) rank[sa[i]]=i;//.idx u pomaleho pole
    for (int i=0, h=0; i<n; ++i) if (rank[i]>0) {
        int j=sa[rank[i]-1];//.idx u pomaleho pole
        while (i+h<n && j+h<n && s[i+h]==s[j+h]) ++h;
        lcp[rank[i]]=h;
        if (h>0) --h;
    }
    delete [] rank;
}

// riesenie pre SPOJ::TWICE
#define MAXLEN 567890
char in1[MAXLEN], in2[MAXLEN];
int N, N1, N2, a[MAXLEN], sa[MAXLEN], rank[MAXLEN], height[MAXLEN];
int main() {
    scanf("%d%s",&N,in1); FOR(n,N) a[n]=in1[n]-'a'+1;
    suffixArray(a,sa,N,30);
    findLCP(a,sa,height,N);
    int ans=0; for (int n=1; n<N; ++n) ans=max(ans,height[n]);
    printf("%d\n",ans);
}
