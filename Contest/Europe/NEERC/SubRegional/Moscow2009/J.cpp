#include <bits/stdc++.h>
using namespace std;

char ans[500][500];

int main() {
  freopen("japanese.in", "r", stdin);
  freopen("japanese.out", "w", stdout);

  ios_base::sync_with_stdio(0); cin.tie(0);
  int n, m; cin >> n >> m;
  vector<string> s(n);
  for (int i = 0; i < n; ++i) cin >> s[i];

  vector<vector<int>> left, up;
  
  for (int i = 0; i < n; ++i) {
    vector<int> v;
    int c = 0;
    for (int j = 0; j < m; ++j) {
      if (s[i][j] == '.') {
        if (c) v.push_back(c);
        c = 0;
      } else ++c;
    }
    if (c) v.push_back(c);
    left.push_back(v);
  }

  for (int j = 0; j < m; ++j) {
    vector<int> v;
    int c = 0;
    for (int i = 0; i < n; ++i) {
      if (s[i][j] == '.') {
        if (c) v.push_back(c);
        c = 0;
      } else ++c;
    }
    if (c) v.push_back(c);
    up.push_back(v);
  }

  // for (int i = 0; i < n; ++i) {
  //   cerr << "up " << i << ": ";
  //   for (int j : up[i]) cerr << j << ' ';
  //   cerr << endl;
  // }
  // for (int i = 0; i < n; ++i) {
  //   cerr << "left " << i << ": ";
  //   for (int j : left[i]) cerr << j << ' ';
  //   cerr << endl;
  // }

  int nn = n, mm = m;
  int ll = 0, lu = 0;
  for (auto &v : left) ll = max(ll, (int)v.size());
  for (auto &v : up) lu = max(lu, (int)v.size());
  nn += lu;
  mm += ll;
  for (int i = 1; i <= lu; ++i) for (int j = 1; j <= ll; ++j) ans[i][j] = '*';
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) ans[i + lu][j + ll] = '.';

  // for (int i = 1; i <= nn; ++i) {
  //   for (int j = 1; j <= mm; ++j) {
  //     cout << ans[i][j];
  //   }
  //   cout << endl;
  // }

  for (int i = 0; i < n; ++i) {
    int p = ll;
    for (int j = (int)left[i].size() - 1; j >= 0; --j, --p) ans[i + lu + 1][p] = (char)(left[i][j] + '0');
    while (p >= 1) ans[i + lu + 1][p] = '_', --p;
  }
  for (int j = 0; j < m; ++j) {
    int p = lu;
    for (int i = (int)up[j].size() - 1; i >= 0; --i, --p) ans[p][j + ll + 1] = (char)(up[j][i] + '0');
    while (p >= 1) ans[p][j + ll + 1] = '_', --p;
  }

  for (int i = 1; i <= nn; ++i) {
    for (int j = 1; j <= mm; ++j) {
      cout << ans[i][j];
    }
    cout << endl;
  }
}
