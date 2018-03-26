#define MAXN 1111
vector<int> partity1, partity2;
set<int> set_partity1, set_partity2;

bool graph[MAXN][MAXN];
int matched[MAXN];
bool visited[MAXN];

bool match(int x) {
  visited[x] = true;
  FOR(i, partity2.size()) {
    if (!graph[partity1[x]][partity2[i]]) continue;
    if (matched[i] == -1 || (!visited[matched[i]] && match(matched[i]))) {
      matched[i] = x;
      return true;
    }
  }
  return false;
}

int maximum_bipartity() {
  partity1 = vector<int>(set_partity1.begin(), set_partity1.end());
  partity2 = vector<int>(set_partity2.begin(), set_partity2.end());

  int result = 0;
  FOR(i, partity2.size()) matched[i] = -1;
  FOR(i, partity1.size()) {
    FOR(j, partity1.size()) visited[j] = false;
    result += match(i);
  }
  return result;
}

#define FIRST_SIZE 555
// vertices from both partities are indexed 0 ... FIRST_SIZE - 1
void add_edge(int a, int b) {
  graph[a][b + FIRST_SIZE] = true;
  graph[b + FIRST_SIZE][a] = true;

  set_partity1.insert(a);
  set_partity2.insert(b + FIRST_SIZE);
}
