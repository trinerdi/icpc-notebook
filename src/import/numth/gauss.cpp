int A[MAXN][MAXN], ans[MAXN]; // A is destroyed
bool gauss(int N) { // returns true if solution found
  REP(i, N) { // Fix i-th row
    if (A[i][i] == 0) {
      FOR(j, i + 1, N - 1) if (A[j][i] != 0) {
        FOR(k, i, N) swap(A[i][k], A[j][k]);
        break;
      }
      if (A[i][i] == 0) return false;
    }
    int I = inv(A[i][i]); // TODO: MOD arithmetics or division
    FOR(j, i, N) A[i][j] = ((long long)A[i][j] * I) % MOD;
    FOR(j, i + 1, N - 1) FORD(k, N, i) {
      A[j][k] = ((A[j][k] - (long long)A[i][k] * A[j][i]) % MOD + MOD) % MOD;
    }
  }
  FORD(i, N - 1, 0) REP(j, i) {
    A[j][N] = ((A[j][N] - (long long)A[i][N] * A[j][i]) % MOD + MOD) % MOD;
    FOR(k, 0, i) {
      A[j][k] = ((A[j][k] - (long long)A[i][k] * A[j][i]) % MOD + MOD) % MOD;
    }
  }
  REP(i, N) ans[i] = A[i][N];
  return true;
}
