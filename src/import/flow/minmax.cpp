template<class T, class U>
class MincostMaxflow {
  public:
  class edge {
    public:
      int source, destination;
      T capacity, residue;
      U cost;
      edge(int s, int d, T cap, T res, U cost) 
        : source(s), destination(d), capacity(cap), residue(res), cost(cost) { }
  };

  vector< vector<int> > V;
  vector<edge> E;
  void clear();
  void addArc(int source, int destination, T capacity, U cost);
  pair<T,U> getFlow(int source, int sink);
};

template<class T, class U> void MincostMaxflow<T,U>::clear() { V.clear(); E.clear(); }

template<class T, class U> 
void MincostMaxflow<T,U>::addArc(int source, int destination, T capacity, U cost) {
  int e = E.size();
  if (source >= int(V.size())) V.resize(source+1);
  if (destination >= int(V.size())) V.resize(destination+1);
  V[source].push_back( e );
  V[destination].push_back( e+1 );
  E.push_back(edge(source,destination,capacity,capacity,cost));
  E.push_back(edge(destination,source,capacity,0,-cost));
}

template<class T, class U> 
pair<T,U> MincostMaxflow<T,U>::getFlow(int source, int sink) {
  if (source >= int(V.size())) V.resize(source+1);
  if (sink >= int(V.size())) V.resize(sink+1);

  int N = V.size(), M = E.size();
  T flowSize = 0;
  U flowCost = 0;
  T Tinfinity = 1; while (2*Tinfinity > Tinfinity) Tinfinity *= 2; 
  U Uinfinity = 1; while (2*Uinfinity > Uinfinity) Uinfinity *= 2;
  U Uepsilon = 1; for (int i=0; i<30; i++) Uepsilon /= 2;
  vector<T> flow(M,0);
  vector<U> potential(N,0);
  while (1) {
    // use dijkstra to find an augmenting path
    vector<int> from(N,-1);
    vector<U> dist(N,Uinfinity);

    priority_queue< pair<U,int>, vector<pair<U,int> >, greater<pair<U,int> > > Q;
    Q.push(make_pair(0,source));
    from[source]=-2; 
    dist[source] = 0;

    while (!Q.empty()) {
      U howFar = Q.top().first; 
      int where = Q.top().second;
      Q.pop();
      if (dist[where] < howFar) continue;

      for (int i=0; i<int(V[where].size()); i++) {
        if (E[ V[where][i] ].residue == 0) continue;
        int dest = E[ V[where][i] ].destination;
        U cost = E[ V[where][i] ].cost;
        if (dist[dest] > dist[where] + potential[where] - potential[dest] + cost + Uepsilon) {
          dist[dest] = dist[where] + potential[where] - potential[dest] + cost;
          from[dest] = V[where][i];
          Q.push( make_pair( dist[dest],dest ));
        }
      }
    }

    // update vertex potentials
    FOR(i, N) {
      if (dist[i]==Uinfinity) potential[i] = Uinfinity;
      else if (potential[i]<Uinfinity) potential[i] += dist[i];
    }

    // if there is no path, we are done
    if (from[sink] == -1) return make_pair(flowSize,flowCost);

    // construct an augmenting path
    T canPush = Tinfinity;
    int where = sink;

    while (1) { 
      if (from[where]==-2) break;
      canPush = min(canPush, E[ from[where] ].residue );
      where = E[ from[where] ].source;
    }

    // update along the path
    where = sink;
    while (1) {
      if (from[where]==-2) break;
      E[ from[where] ].residue -= canPush;
      E[ from[where]^1 ].residue += canPush;
      flowCost += canPush * E[ from[where] ].cost;
      where = E[ from[where] ].source;
    }
    flowSize += canPush;
  }
  return make_pair(-1,47);
}
