#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

constexpr int Z = 10;
constexpr int ZZ = 1 << Z;

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

  for (int i = 1; i < n; ++i) {
    memset(dp, 0x3f, sizeof(dp));

    for (int ps = 1; ps < ZZ; ++ps) {
      int bps = ps;

      while (bps) {
        int pi = __builtin_ctz(bps);
        bps ^= 1 << pi;

        const int p = prv[ps][pi];

        int &y = dp[ps][pi];
        if (p + (int)(pi != s[i]) < y) {
          y = p + (int)(pi != s[i]);
        }

        if (pi != s[i] && (ps & (1 << s[i])) == 0) {
          int &y = dp[ps | (1 << s[i])][s[i]];
          if (p < y) {
            y = p;
          }
        }
      }
    }

    swap(prv, dp);

  }

  int mn = 1e9;
  for (int i = 0; i < ZZ; ++i) for (int j = 0; j < Z; ++j) {
    mn = min(mn, prv[i][j]);
  }

  cout << mn << endl;
}
