#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

const int Z = 10;
const int ZZ = 1 << Z;

int prv[ZZ][Z];
int dp[ZZ][Z];

int main() {
  string s; cin >> s;
  for (char &c : s) c &= 15;
  int n = s.size();

  memset(prv, 0x3f, sizeof(prv));
  for (int i = 0; i < Z; ++i) {
    prv[1 << i][i] = s[0] != i;
  }

  // cerr << "i = 0" << endl;
  // for (int i = 0; i < ZZ; ++i) {
  //   for (int j = 0; j < Z; ++j) {
  //     cerr << "dp " << i << ' ' << j << ' ' << prv[i][j] << endl;
  //   }
  // }

  for (int i = 1; i < n; ++i) {
    memset(dp, 0x3f, sizeof(dp));

    for (int ps = 1; ps < ZZ; ++ps) {
      int bps = ps;

      while (bps) {
        int pi = __builtin_ctz(bps);
        bps ^= 1 << pi;

        int &y = dp[ps][pi];
        if (prv[ps][pi] + (int)(pi != s[i]) < y) {
          y = prv[ps][pi] + (int)(pi != s[i]);
        }
      }

      if ((ps & (1 << s[i])) == 0) {
        bps = ps;
        while (bps) {
          int pi = __builtin_ctz(bps);
          bps ^= 1 << pi;

          if (pi != s[i]) {
            int &y = dp[ps | (1 << s[i])][s[i]];
            if (prv[ps][pi] < y) {
              y = prv[ps][pi];
            }
            // y = min(y, prv[ps][pi]);
          }
        }
      }
    }

    swap(prv, dp);

    // cerr << "i = " << i << endl;
    // for (int i = 0; i < ZZ; ++i) {
    //   for (int j = 0; j < Z; ++j) {
    //     cerr << "dp " << i << ' ' << j << ' ' << prv[i][j] << endl;
    //   }
    // }
  }

  int mn = 1e9;
  for (int i = 0; i < ZZ; ++i) for (int j = 0; j < Z; ++j) {
    mn = min(mn, prv[i][j]);
  }

  cout << mn << endl;
}
