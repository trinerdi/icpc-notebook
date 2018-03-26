//////////////// 1D Fenwick tree /////////////////////////////////

int size1d;
int T1d[1234567];

void init1d(int sz) { size1d=1; while (size1d<sz) size1d <<= 1; }
void update1d(int x, int d) { while (x <= size1d){ T1d[x]+=d; x+=x&-x; } }

int sum1d(int x1, int x2) { // sucet v uzavretom intervale [x1,x2]
  int res=0;
  x1--;
  while (x2) { res += T1d[x2]; x2 -= x2 & -x2; }
  while (x1) { res -= T1d[x1]; x1 -= x1 & -x1; }
  return res;
}

int find1d(int sum){ // najvacsie z take ze sucet v intervale [1,z] <= sum
  int idx = 0, bitMask=size1d;
  while (bitMask && (idx<size1d)) {
    int tIdx = idx + bitMask;
    if (sum >= T1d[tIdx]) { idx=tIdx; sum -= T1d[tIdx]; }
    bitMask >>= 1;
  }
  return idx;
}

//////////////// 2D Fenwick tree /////////////////////////////////

int size2d;
int T2d[1030][1030];

void init2d(int sz) { size2d=1; while (size2d<sz) size2d <<= 1; }
void update2d(int x, int y, int d){
  while (x <= size2d) {
    int y1=y;
    while (y1 <= size2d) { T2d[x][y1]+=d; y1+=y1&-y1; }
    x+=x&-x;
  }
}

int sum2d(int x1, int _y1, int x2, int _y2) {
  int res=0;
  x1--;
  while (x2) { 
    int y1=_y1-1, y2=_y2;
    while (y2) { res += T2d[x2][y2]; y2 -= y2 & -y2; }
    while (y1) { res -= T2d[x2][y1]; y1 -= y1 & -y1; }
    x2 -= x2 & -x2;
  }
  while (x1) { 
    int y1=_y1-1, y2=_y2;
    while (y2) { res -= T2d[x1][y2]; y2 -= y2 & -y2; }
    while (y1) { res += T2d[x1][y1]; y1 -= y1 & -y1; }
    x1 -= x1 & -x1;
  }
  return res;
}
