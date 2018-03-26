int N;
vector< vector<int> > G;
vector<int> SCC;

stack<int> S;
vector<int> cislo, najmenej;
vector<bool> spracuvam;
int cas, nSCC;

void hladaj(int v) {
  cislo[v] = najmenej[v] = cas++;
  S.push(v); spracuvam[v] = true;
  for (int i=0; i<int( G[v].size() ); i++) {
    int kam = G[v][i];
    if (cislo[kam]==-1) { hladaj(kam); najmenej[v] = min( najmenej[v], najmenej[kam] ); }
    else if (spracuvam[kam]) najmenej[v] = min( najmenej[v], najmenej[kam] );
  }
  if (najmenej[v] == cislo[v]) {
    while (1) { int k = S.top(); S.pop(); spracuvam[k]=false; SCC[k]=nSCC; if (k==v) break; }
    nSCC++;
  }
}

int main() {
  while (1) {
    cin >> N;
    if (!N) break;
    G.clear(); G.resize(N);
    int M;
    cin >> M;
    while (M--) { int x,y; cin >> x >> y; G[x-1].push_back(y-1); }
    SCC.clear(); SCC.resize(N,-1);
    cislo.clear(); cislo.resize(N,-1);
    najmenej.clear(); najmenej.resize(N,-1);
    spracuvam.clear(); spracuvam.resize(N,false);
    cas=nSCC=0;
    FOR(i, N) if (SCC[i]==-1) hladaj(i);

    vector<int> velkosti(nSCC,0);
    vector<bool> dobry(nSCC,true);
    FOR(i, N) velkosti[ SCC[i] ]++;
    FOR(i, N) for (int j=0; j<int(G[i].size()); j++)
      if (SCC[i] != SCC[ G[i][j] ]) dobry[ SCC[i] ]=false;
    bool uz = false;
    FOR(i, N) if (dobry[SCC[i]]) { cout << (uz?" ":"") << (i+1); uz = true; }
    cout << endl;
  }
}
