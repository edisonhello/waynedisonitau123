#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 50;
constexpr int kMod = 1'000'000'000 + 7;
int dp1[kN][kN][kN][11];
int dp2[kN][kN][kN][11];
int pw[kN + 1];
string s[kN];
int n, m;

int Dfs1(int l, int r, int k, int d) {
  if (k >= m) {
    if (l == r) return 1;
    return 0;
  }
  if (l > r) return 1;
  if (d >= 10) return 0;
  if (dp1[l][r][k][d] != -1) {
    return dp1[l][r][k][d];
  }
  dp1[l][r][k][d] = 0;
  (dp1[l][r][k][d] += Dfs1(l, r, k, d + 1)) %= kMod;
  bool ok = true;
  for (int z = l; z <= r; ++z) {
    ok &= s[z][k] == '?' || s[z][k] - '0' == d;
    if (!ok) break;
    dp1[l][r][k][d] +=
        1LL * Dfs1(l, z, k + 1, 0) * Dfs1(z + 1, r, k, d + 1) % kMod;
    dp1[l][r][k][d] %= kMod;
  }
  return dp1[l][r][k][d];
}

int Dfs2(int l, int r, int k, int d) {
  if (k >= m) return 0;
  if (l > r) return 0;
  if (d >= 10) return 0;
  if (dp2[l][r][k][d] != -1) {
    return dp2[l][r][k][d];
  }
  dp2[l][r][k][d] = 0;
  (dp2[l][r][k][d] += Dfs2(l, r, k, d + 1)) %= kMod;
  bool ok = true;
  for (int z = l; z <= r; ++z) {
    ok &= s[z][k] == '?' || s[z][k] - '0' == d;
    if (!ok) break;
    int ways = 1LL * Dfs1(l, z, k + 1, 0) * Dfs1(z + 1, r, k, d + 1) % kMod;
    int sum = 1LL * (z - l + 1) * pw[m - k - 1] % kMod * d % kMod;
    (dp2[l][r][k][d] += 1LL * ways * sum % kMod) %= kMod;
    (dp2[l][r][k][d] += 1LL * Dfs2(l, z, k + 1, 0) * Dfs1(z + 1, r, k, d + 1) % kMod) %= kMod;
    (dp2[l][r][k][d] += 1LL * Dfs2(z + 1, r, k, d + 1) * Dfs1(l, z, k + 1, 0) % kMod) %= kMod;
  }
  return dp2[l][r][k][d];
}

int main() {
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    cin >> s[i];
  }
  pw[0] = 1;
  for (int i = 1; i <= m; ++i) {
    pw[i] = 10LL * pw[i - 1] % kMod;
  }
  memset(dp1, -1, sizeof(dp1));
  memset(dp2, -1, sizeof(dp2));
  cout << Dfs2(0, n - 1, 0, 0) << "\n";
  return 0;
}
