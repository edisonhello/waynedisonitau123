#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, Q;
  cin >> N >> Q;
  vector<int> a(N);
  for (int i = 0; i < N; ++i) {
    cin >> a[i];
  }
  vector<vector<int>> g(N);
  for (int i = 0; i < N - 1; ++i) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  constexpr int kC = 1'000'000 + 1;
  bitset<kC> dp{};
  dp.set(0);
  for (int i = 0; i < Q; ++i) {
    int x;
    cin >> x;
    dp |= dp << x;
  }
  vector<int> vec;
  for (int i = 0; i < kC; ++i) {
    if (dp[i]) {
      vec.push_back(i);
    }
  }

  vector<int64_t> bc(N);

  auto Dfs = [&](auto self, int x, int p = -1) -> int64_t {
    bc[x] = a[x]; 
    int64_t sum = 0;
    int64_t diff = 0;
    for (int u : g[x]) {
      if (u == p) {
        continue;
      }
      sum += self(self, u, x);
      diff = max(diff, bc[u] - a[x]);
    }
    if (diff > vec.back()) {
      cout << "-1\n";
      exit(0);
    }
    int add = *lower_bound(vec.begin(), vec.end(), diff);
    bc[x] += add;
    sum += bc[x];
    return sum;
  };

  cout << Dfs(Dfs, 0) << "\n";
  return 0;
}
