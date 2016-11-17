int father[MAXN], rank[MAXN];
int root(int x) { return father[x] == -1 ? x : (father[x] = root(father[x])); }

bool DFU(int a, int b) {
  int ca = root(a), cb = root(b);
  if(ca != cb) {
    if (rank[ca] < rank[cb])     father[ca] = cb;
    else if(rank[cb] < rank[ca]) father[cb] = ca;
    else {
      rank[ca]++;
      father[cb]=ca;
    }
    return true;
  }
  return false;
}
