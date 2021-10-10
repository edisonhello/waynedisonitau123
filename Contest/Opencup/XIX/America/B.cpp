#include <bits/stdc++.h>
using namespace std;


int main() {
  int n, m; cin >> n >> m;
  vector<string> from(n);
  vector<string> to(n);

  for (int i = 0; i < n; ++i) cin >> from[i];
  for (int i = 0; i < n; ++i) cin >> to[i];

  vector<int> crx(n), ccx(m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (to[i][j] == 'X') crx[i]++, ccx[j]++;
    }
  }

  vector<int> chr(n, 1), chc(m, 1);

  for (int i = 0; i < n; ++i) if (crx[i] >= 2) chr[i] = 0;
  for (int i = 0; i < m; ++i) if (ccx[i] >= 2) chc[i] = 0;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (to[i][j] == 'X' && (!chr[i] || !chc[j])) {
        chr[i] = chc[j] = 0;
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (!chr[i] && !chc[j]) {
        if (from[i][j] != to[i][j]) {
          cout << 0 << endl;
          exit(0);
        }
      }
    }
  }

  int space = 0, spacex = 0, spaceo = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (chr[i] && chc[j]) {
        ++space;
        if (from[i][j] == 'O') ++spaceo;
        if (to[i][j] == 'X') ++spacex;
      }
    }
  }

  if (!spaceo || !spacex) {
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if (from[i][j] != to[i][j]) {
      cout << 0 << endl;
      exit(0);
    }
    cout << 1 << endl;
    exit(0);
  }

  cout << 1 << endl;
  exit(0);
}
