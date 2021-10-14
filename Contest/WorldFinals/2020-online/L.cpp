#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N, M;
  cin >> N >> M;
  vector<int> c(N);
  for (int i = 0; i < N; ++i) {
    cin >> c[i];
  }
  vector<tuple<int, int, int>> edges;
  for (int i = 0; i < M; ++i) {
    int a, b, w;
    cin >> a >> b >> w;
    edges.emplace_back(w, a - 1, b - 1);
  }
  sort(edges.rbegin(), edges.rend());

  vector<int> uf(N);
  iota(uf.begin(), uf.end(), 0);

  vector<int64_t> dp(N);
  for (int i = 0; i < N; ++i) {
    dp[i] = c[i];
  }

  function<int(int)> Find = [&](int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
  };

  int64_t sum = accumulate(c.begin(), c.end(), 0LL);
  int64_t ans = 1'000'000'000;

  auto Merge = [&](int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return;
    dp[x] += dp[y];
    uf[y] = x;
  };

  for (int i = 0, j = 0; i < M; i = j) {
    int64_t z = 0;
    while (j < M && get<0>(edges[j]) == get<0>(edges[i])) {
      z = max(z, dp[Find(get<1>(edges[j]))]);
      z = max(z, dp[Find(get<2>(edges[j]))]);
      j++;
    }
    ans = min(ans, z + get<0>(edges[i]) - sum);
    for (int k = i; k < j; ++k) {
      Merge(get<1>(edges[k]), get<2>(edges[k]));
    }
  }
  if (ans <= 0) ans = -1;
  cout << ans << "\n";
  return 0;
}
