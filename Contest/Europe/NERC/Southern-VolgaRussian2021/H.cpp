#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  vector<int> m(N), k(N);
  for (int i = 0; i < N; ++i) {
    cin >> m[i] >> k[i];
    m[i]--;
  }

  constexpr int kC = 200'000;
  pair<int64_t, int64_t> ans{0, 1};
  int opt = -1;
  for (int t = 1; t <= 20; ++t) {
    vector<int64_t> profit(kC);
    for (int i = 0; i < N; ++i) {
      profit[m[i]] += min(t, k[i]);
    }
    sort(profit.rbegin(), profit.rend());
    int64_t s = 0;
    for (int i = 0; i < t; ++i) {
      s += profit[i];
    }
    if (s * ans.second > t * ans.first) {
      ans = {s, t};
      opt = t;
    }
  }
  vector<int64_t> profit(kC);
  for (int i = 0; i < N; ++i) {
    profit[m[i]] += k[i];
  }
  sort(profit.rbegin(), profit.rend());
  int64_t s = 0;
  for (int i = 0; i < kC; ++i) {
    s += profit[i];
    if (i >= 20) {
      if (s * ans.second > (i + 1) * ans.first) {
        ans = {s, i + 1};
        opt = i + 1;
      }
    }
  }

  fill(profit.begin(), profit.end(), 0);
  for (int i = 0; i < N; ++i) {
    profit[m[i]] += min(opt, k[i]);
  }
  vector<int> order(kC);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(),
       [&](int i, int j) { return profit[i] > profit[j]; });
  cout << opt << "\n";
  for (int i = 0; i < opt; ++i) {
    cout << order[i] + 1 << " ";
  }
  cout << "\n";
  return 0;
}
