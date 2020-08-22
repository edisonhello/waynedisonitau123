#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("harmless.in", "r", stdin);
  freopen("harmless.out", "w", stdout);
  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<int>> pref(n, vector<int>(m));
  vector<vector<int>> rank(m, vector<int>(n));
  vector<vector<int>> trev(m, vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> pref[i][j];
      pref[i][j]--;
    }
  }
  vector<vector<bool>> inc(m, vector<bool>(n));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> rank[i][j];
      rank[i][j]--;
      trev[i][rank[i][j]] = j;
      if (j < k) {
        inc[i][rank[i][j]] = true;
      }
    }
  }
  vector<bool> used(n);
  vector<vector<int>> res(m);
  while (true) {
    int z = -1;
    for (int i = 0; i < m && z == -1; ++i) {
      for (int j = 0; j < n && z == -1; ++j) {
        if (used[j]) continue;
        if (inc[pref[j][i]][j]) {
          z = i;
          break;
        }
      }
    }
    // cerr << "z = " << z << endl;
    assert(z != -1);
    for (int j = 0; j < n; ++j) {
      if (used[j]) continue;
      if (inc[pref[j][z]][j]) {
        // cerr << "go j = " << j << " fac = " << pref[j][z] << endl;
        res[pref[j][z]].push_back(j);
        used[j] = true;
        for (int p = z + 1; p < m; ++p) {
          if (inc[pref[j][p]][j]) {
            inc[pref[j][p]][j] = false;
          }
        }
      }
    }
    bool ok = true;
    for (int j = 0; j < m; ++j) {
      int need = k - res[j].size();
      assert(need >= 0);
      ok &= need == 0;
      for (int p = 0; p < n && need > 0; ++p) {
        // cerr << "j = " << j << "  fuck = " << rank[j][p] << endl;
        if (used[rank[j][p]]) continue;
        // cerr << "fac " << j << " get " << rank[j][p] << endl;
        inc[j][rank[j][p]] = true;
        need--;
      }
      // if (need != 0) cerr << "j = " << j << endl;
      assert(need == 0);
    }
    if (ok) break;
  }
  for (int i = 0; i < m; ++i) {
    // cerr << "size = " << res[i].size() << endl;
    assert(res[i].size() == k);
    sort(res[i].begin(), res[i].end(), [&](int x, int y) { return trev[i][x] < trev[i][y]; });
    for (int j = 0; j < k; ++j) {
      cout << res[i][j] + 1 << " \n"[j + 1 == k];
    }
  }
}
