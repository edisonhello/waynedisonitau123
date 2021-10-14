#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

namespace std {
  template <>
  struct hash<pair<int64_t, int64_t>> {
    uint64_t operator()(const pair<int64_t, int64_t> &p) const {
      return p.first ^ p.second;
    }
  };
}

int main() {
  string s;
  cin >> s;
  int64_t A;
  cin >> A;

  int N = s.size();
  vector<unordered_map<pair<int64_t, int64_t>, int64_t>> dp(N);
  vector<__int128> suffix(N), pw(N + 1, 1);
  vector<int> cnt(N);
  for (int i = 1; i <= N; ++i) pw[i] = pw[i - 1] * 10;
  for (int i = 0; i < N; ++i) {
    for (int j = i; j < N; ++j) {
      if (isdigit(s[j])) {
        suffix[i] = suffix[i] * 10 + (s[j] - '0');
        cnt[i]++;
      }
    }
  }
  auto Dfs = [&](auto dfs, int64_t a, int64_t b, int p) -> int64_t {
    if (a + b > A) return 0;
    if (p == N) {
      if (b == 0) return 0;
      if (a + b == A) return 1;
      return 0;
    }
    if (dp[p].find(make_pair(a, b)) != dp[p].end()) return dp[p][make_pair(a, b)];
    int64_t ans = dfs(dfs, a, b, p + 1);
    __int128 x = b * pw[cnt[p]] + suffix[p];
    if (a + x < A) return 0;
    if (s[p] == '+') {
      if (b) {
        ans += dfs(dfs, a + b, 0, p + 1);
      }
    } else {
      __int128 t = (__int128)b * 10 + s[p] - '0';
      if (a + t <= A) ans += dfs(dfs, a, t, p + 1);
    }
    dp[p][make_pair(a, b)] = ans;
    return ans;
  };

  cout << Dfs(Dfs, 0, 0, 0) << "\n";
  return 0;
}
