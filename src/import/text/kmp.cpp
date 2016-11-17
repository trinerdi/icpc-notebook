int N; //lenght of the needle
char needle[MAX_NEEDLE];
int fail[MAX_NEEDLE];

void failure() { //precomputes the failure function
  int k;
  fail[0] = -1;
  rep(i, 1, N + 1) {
    for (k = fail[i - 1]; k >= 0 && needle[k] != needle[i - 1]; k = fail[k]) ;
    fail[i] = k + 1;
  }
}

int L; //lenght of the text
char text[MAX_TEXT];

void kmp() {
  int i = 0, j = 0;
  while (i < L) {
    while (j >= 0 && text[i] != needle[j]) j = fail[j];
    i++; j++;
    if (j == N) {
      // string matched - needle ends in i (last symbol at i - 1) => starts in i - N
      j = fail[j];
    }
  }
}
