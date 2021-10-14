#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> s(N);
  for (int i = 0; i < N; ++i) cin >> s[i];
  sort(s.begin(), s.end());

  vector<int> nxt(N);
  int p = N;
  for (int i = N - 1; i >= 0; --i) {
    if (i + 1 < N && s[i + 1] != s[i]) p = i + 1;
    nxt[i] = p;
  }

  constexpr int kP = 1'000'000'000 + 7;
  vector<vector<int>> dp(N, vector<int>(N, -1));

  auto Dfs = [&](auto dfs, int l, int r) -> int {
    if (r <= l) return 1;
    if (dp[l][r] != -1) return dp[l][r];
    int v = s[l];
    dp[l][r] = 0;
    int dist = min(nxt[l], r + 1) - l - 1;
    for (int p = 0; p <= r - l; ++p) {
      int R = p, L = r - l - p;
      if (L >= dist) {
        int x = dfs(dfs, l + 1, l + L);
        int y = dfs(dfs, l + L + 1, r);
        dp[l][r] += 1LL * x * y % kP;
        dp[l][r] %= kP;
      }
    }
    // cerr << "dp[" << l << "][" << r << "] = " << dp[l][r] << endl;
    return dp[l][r];
  };

  auto fpow = [&](int a, int n) {
    int res = 1;
    while (n > 0) {
      if (n & 1) res = 1LL * res * a % kP;
      a = 1LL * a * a % kP;
      n >>= 1;
    }
    return res;
  };

  int ans = Dfs(Dfs, 0, N - 1);
  // cerr << "ans = " << ans << endl;
  vector<int> fc(N + 1, 1), iv(N + 1, 1);
  for (int i = 1; i <= N; ++i) fc[i] = 1LL * fc[i - 1] * i % kP;
  for (int i = 0; i <= N; ++i) iv[i] = fpow(fc[i], kP - 2);
  vector<int> cnt(N + 1);
  for (int u : s) cnt[u]++;
  int res = fc[N];
  for (int i = 1; i <= N; ++i) res = 1LL * res * iv[cnt[i]] % kP;
  cout << (res + kP - ans) % kP << "\n";
  return 0;
}
