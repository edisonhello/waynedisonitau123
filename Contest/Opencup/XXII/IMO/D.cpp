#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 4000;
int cost[kN][kN];
bitset<kN / 2> dp[kN];
bitset<kN / 2> dp2[kN];
int which[kN * kN];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; j += 2) {
      cin >> cost[i][j];
      which[cost[i][j]] = i * N + j;
    }
  }

  auto Push = [&](auto self, int l, int r, int t) -> void {
    dp[l].set(r / 2);
    dp2[r].set(l / 2);
    if (l > 0 && r + 1 < N && !dp[l - 1].test((r + 1) / 2) &&
        cost[l - 1][r + 1] <= t) {
      self(self, l - 1, r + 1, t);
    }
    if (r + 1 < N) {
      auto bs = ~dp[l] & dp[r + 1];
      for (int i = bs._Find_first(); i * 2 + (1 - l % 2) < N;
           i = bs._Find_next(i)) {
        self(self, l, i * 2 + (1 - l % 2), t);
      }
    }
    if (l > 0) {
      auto bs = ~dp2[r] & dp2[l - 1];
      for (int i = bs._Find_first(); i * 2 + (1 - r % 2) < l;
           i = bs._Find_next(i)) {
        self(self, i * 2 + (1 - r % 2), r, t);
      }
    }
  };

  for (int t = 1; t <= (N / 2) * (N / 2); ++t) {
    int i = which[t] / N, j = which[t] % N;
    if (i + 1 == j) {
      Push(Push, i, j, t);
    } else {
      if (dp[i + 1].test((j - 1) / 2)) {
        Push(Push, i, j, t);
      }
    }
    if (dp[0].test((N - 1) / 2)) {
      cout << t << "\n";
      return 0;
    }
  }
}
