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

  vector<int64_t> sum(N);
  for (int i = 0; i < N; ++i) {
    sum[i] = c[i];
  }

  function<int(int)> Find = [&](int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
  };

  vector<int64_t> dp(N, 1'000'000'000);

  auto Merge = [&](int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return;
    uf[x] = y;
  };

  vector<vector<int>> nd(N);
  for (int i = 0, j = 0; i < M; i = j) {
    vector<int> vec;
    while (j < M && get<0>(edges[j]) == get<0>(edges[i])) {
      vec.push_back(Find(get<1>(edges[j])));
      vec.push_back(Find(get<2>(edges[j])));
      j++;
    }
    sort(vec.begin(), vec.end());
    vec.resize(unique(vec.begin(), vec.end()) - vec.begin());
    for (int k = i; k < j; ++k) {
      Merge(get<1>(edges[k]), get<2>(edges[k]));
    }
    for (int v : vec) {
      nd[Find(v)].push_back(v);
    }
    for (int v : vec) {
      uf[v] = v;
    }
    int w = get<0>(edges[i]);
    for (int v : vec) {
      if (!nd[v].empty()) {
        sort(nd[v].begin(), nd[v].end(), [&](int x, int y) {
          int64_t X = min(dp[x], min(w - sum[x], dp[y] - sum[x]));
          int64_t Y = min(dp[y], min(w - sum[y], dp[x] - sum[y]));
          return X > Y;
        });
        for (int k = 1; k < nd[v].size(); ++k) {
          int a = Find(nd[v][k - 1]);
          int b = Find(nd[v][k]);
          int64_t d = max(min(dp[a], min(w - sum[a], dp[b] - sum[a])),
                          min(dp[b], min(w - sum[b], dp[a] - sum[b])));
          dp[a] = d;
          sum[a] += sum[b];
          uf[b] = a;
        }
        nd[v].clear();
      }
    }
  }
  int64_t ans = dp[Find(0)];
  if (ans <= 0) ans = -1;
  cout << ans << "\n";
  return 0;
}
