#include <bits/stdc++.h>
using namespace std;

int a[22][22];

int cval[22][22];


int dp[22];

int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> a[i][j];
    }
  }

  for (int i = 0; i < m; ++i) {
    for (int j = i + 1; j < m; ++j) {
      int z = 0;
      for (int k = 0; k < n; ++k) {
        if (a[k][i] < a[k][j]) z |= 1 << k;
      }
      // cerr << "cval " << i << ' ' << j << " = " << z << endl;
      cval[i][j] = z;
    }
  }

  vector<int> tkr, tkc;
  unordered_map<int, vector<pair<int, int>>> val_edg;
  vector<vector<int>> froms(22);

  int64_t ans = 0;

  for (int z = 1; z < (1 << n); ++z) {
    // cerr << "z = " << z << endl;

    tkr.clear();
    tkc.clear();
    for (int i = 0; i < n; ++i) if (z & (1 << i)) tkr.push_back(i);

    for (int i = 0; i < m; ++i) {
      if (tkr.size() <= 2u) tkc.push_back(i);
      else {
        int fi = a[tkr[0]][i] < a[tkr[1]][i];
        int ok = 1;
        for (int j = 2; j < (int)tkr.size(); ++j) {
          if (fi != (a[tkr[j - 1]][i] < a[tkr[j]][i])) ok = 0;
        }
        if (ok) tkc.push_back(i);
      }
    }

    val_edg.clear();

    int mm = tkc.size();
    for (int i = 0; i < mm; ++i) {
      for (int j = i + 1; j < mm; ++j) {
        // cerr << "cval in " << tkc[i] << " and " << tkc[j] << " " << (cval[tkc[i]][tkc[j]] & z) << endl;
        val_edg[cval[tkc[i]][tkc[j]] & z].emplace_back(tkc[i], tkc[j]);
      }
    }

    for (auto &[_val, edgs] : val_edg) {
      for (int i : tkc) {
        froms[i].clear();
        dp[i] = 1;
      }

      for (auto &[u, v] : edgs) {
        froms[v].push_back(u);
      }

      for (int i : tkc) {
        for (int j : froms[i]) {
          dp[i] += dp[j];
        }

        ans += dp[i] - 1;
      }
    }

    ans += tkc.size();
  }

  cout << ans << endl;
}
