#include <bits/stdc++.h>
using namespace std;

int nxt[100005][30];

int main() {
  string s, t; cin >> s >> t;
  int n = s.size();
  int m = t.size();
  
  for (int i = 0; i < 26; ++i) nxt[n][i] = nxt[n + 1][i] = n + 1;
  for (int i = n - 1; i >= 0; --i) {
    for (int j = 0; j < 26; ++j) {
      nxt[i][j] = nxt[i + 1][j];
    }
    nxt[i][s[i] - 'a'] = i + 1;
  }

  long long cnt = 0;
  for (int i = 0; i < (int)s.size(); ++i) {
    int pos = i;
    for (char c : t) {
      pos = nxt[pos][c - 'a'];
    }
    // cerr << "pos = " << pos << endl;
    if (pos > n);
    else cnt += n - pos + 1;
    // for (int j = i; j < (int)s.size(); ) {
    //   pos = nxt[pos][s[j] - 'a'];
    //   if (pos > m) break;
    //   ++cnt;
    // }
  }

  cout << cnt << endl;
}
