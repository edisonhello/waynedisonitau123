#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  vector<int> x(N), y(N), v(N);
  for (int i = 0; i < N; ++i) {
    cin >> x[i] >> y[i] >> v[i];
  }

  auto Solve = [&]() {
    map<int, int64_t> sum;
    for (int i = 0; i < N; ++i) {
      sum[y[i]] += v[i];
    }
    multiset<int64_t> ms;
    for (auto iter : sum) {
      ms.insert(iter.second);
    }

    auto Get = [&](multiset<int64_t>& ms, int k) {
      k = min<int>(k, ms.size());
      if (k == 1) {
        return *prev(ms.end());
      }
      if (k == 2) {
        return *prev(ms.end()) + *prev(prev(ms.end()));
      }
      if (k == 3) {
        return *prev(ms.end()) + *prev(prev(ms.end())) +
               *prev(prev(prev(ms.end())));
      }
      assert(false);
    };

    int64_t ans = Get(ms, 3);
    map<int, vector<int>> xs;
    for (int i = 0; i < N; ++i) {
      xs[x[i]].push_back(i);
    }
    for (auto iter : xs) {
      int64_t s = 0;
      for (int u : iter.second) {
        s += v[u]; 
        ms.erase(ms.find(sum[y[u]]));
        sum[y[u]] -= v[u];
        ms.insert(sum[y[u]]);
      }
      ans = max(ans, s + Get(ms, 2));
      for (int u : iter.second) {
        ms.erase(ms.find(sum[y[u]]));
        sum[y[u]] += v[u];
        ms.insert(sum[y[u]]);
      }
    }
    return ans;
  };

  int64_t ans = Solve();
  for (int i = 0; i < N; ++i) {
    swap(x[i], y[i]);
  }
  ans = max(ans, Solve());
  cout << ans << "\n";
}
