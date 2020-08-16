#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<string> gr(n);
  for (int i = 0; i < n; ++i) {
    cin >> gr[i];
  }
  vector<int> up(m);
  int a = 0, b = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      up[j] = (gr[i][j] == '0' ? 0 : up[j] + 1);
      if (up[j] >= a) b = a, a = up[j];
      else if (up[j] >= b) b = up[j];

      if (up[j] > 1) {
        if (up[j] - 1 >= a) b = a, a = up[j] - 1;
        else if (up[j] - 1 >= b) b = up[j] - 1;
      }
    }
    vector<int> ord(m);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int u, int v) { return up[u] > up[v]; });
    vector<bool> used(m);
    vector<int> uf(m), sz(m, 1), fk(up.begin(), up.end());
    iota(uf.begin(), uf.end(), 0);

    function<int(int)> Find = [&](int x) {
      if (x == uf[x]) return x;
      return uf[x] = Find(uf[x]);
    };

    auto Merge = [&](int x, int y) {
      x = Find(x);
      y = Find(y);
      assert(x != y);
      fk[y] = min(fk[y], fk[x]);
      sz[y] += sz[x];
      uf[x] = y;
      
      int g = sz[y] * fk[y];
      if (g >= a) b = a, a = g;
      else if (g >= b) b = g;
      if (sz[y] > 1) {
        g = (sz[y] - 1) * fk[y];
        if (g >= a) b = a, a = g;
        else if (g >= b) b = g;
      }
      if (fk[y] > 1) {
        g = (fk[y] - 1) * sz[y];
        if (g >= a) b = a, a = g;
        else if (g >= b) b = g;
      }
    };

    for (int j = 0; j < m; ++j) {
      int p = ord[j];
      if (p > 0 && used[p - 1]) Merge(p - 1, p);
      if (p + 1 < m && used[p + 1]) Merge(p, p + 1);
      used[p] = true;
    }
  }
  cout << b << endl;
}
