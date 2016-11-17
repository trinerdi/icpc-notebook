int A[MAXN][MAXN], ans[MAXN]; // A is destroyed
bool gauss(int N) { // returns true if solution found
  REP(i, N) { // Fix i-th row
    if (A[i][i] == 0) {
      rep(j, i + 1, N) if (A[j][i] != 0) {
        rep(k, i, N + 1) swap(A[i][k], A[j][k]);
        break;
      }
      if (A[i][i] == 0) return false;
    }
    int I = inv(A[i][i]); // TODO: MOD arithmetics or division
    rep(j, i, N + 1) A[i][j] = ((long long)A[i][j] * I) % MOD;
    rep(j, i + 1, N) per(k, i, N + 1) {
      A[j][k] = ((A[j][k] - (long long)A[i][k] * A[j][i]) % MOD + MOD) % MOD;
    }
  }
  per(i, 0, N) REP(j, i) {
    A[j][N] = ((A[j][N] - (long long)A[i][N] * A[j][i]) % MOD + MOD) % MOD;
    rep(k, 0, i + 1) {
      A[j][k] = ((A[j][k] - (long long)A[i][k] * A[j][i]) % MOD + MOD) % MOD;
    }
  }
  REP(i, N) ans[i] = A[i][N];
  return true;
}
