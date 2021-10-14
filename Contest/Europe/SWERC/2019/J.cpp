#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N;
  cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];

  if (N == 0) {
    cout << 1 << "\n";
    return 0;
  }

  vector<vector<int>> sp(1, vector<int>(A.begin(), A.end()));
  for (int i = 1; (1 << i) <= N; ++i) {
    sp.emplace_back(N);
    for (int j = 0; j + (1 << i) <= N; ++j) {
      sp[i][j] = min(sp[i - 1][j], sp[i - 1][j + (1 << (i - 1))]);
    }
  }
  vector<vector<int>> pos(1000000 + 1);
  for (int i = 0; i < N; ++i) pos[A[i]].push_back(i);

  constexpr int kP = 1'000'000'000 + 7;
  vector<int> fc(2 * N + 1, 1), iv(2 * N + 1, 1);

  auto fpow = [&](int a, int n) {
    int res = 1;
    while (n > 0) {
      if (n & 1) res = 1LL * res * a % kP;
      a = 1LL * a * a % kP;
      n >>= 1;
    }
    return res;
  };

  for (int i = 1; i <= 2 * N; ++i) {
    fc[i] = 1LL * fc[i - 1] * i % kP;
    iv[i] = fpow(fc[i], kP - 2);
  }

  auto Query = [&](int l, int r) {
    int p = 31 - __builtin_clz(r - l);
    return min(sp[p][l], sp[p][r - (1 << p)]);
  };

  vector<int> cache(2 * N + 1, -1);

  auto Get = [&](int n) {
    if (cache[n] != -1) return cache[n];
    return cache[n] = 1LL * fc[2 * n] * iv[n] % kP * iv[n] % kP * fpow(n + 1, kP - 2) % kP;
  };

  auto Solve = [&](auto dfs, int l, int r) -> int {
    int t = Query(l, r);
    int k = lower_bound(pos[t].begin(), pos[t].end(), l) - pos[t].begin();
    assert(pos[t][k] < r);
    int cnt = 0, pv = l - 1, res = 1;
    for (int i = k; i < pos[t].size() && pos[t][i] < r; ++i) {
      if (pos[t][i] > pv + 1) res = 1LL * res * dfs(dfs, pv + 1, pos[t][i]) % kP;
      cnt++;
      pv = pos[t][i];
    }
    if (r > pv + 1) res = 1LL * res * dfs(dfs, pv + 1, r) % kP;
    res = 1LL * res * Get(cnt) % kP;
    return res;
  };

  cout << Solve(Solve, 0, N) << "\n";
  return 0;
}
