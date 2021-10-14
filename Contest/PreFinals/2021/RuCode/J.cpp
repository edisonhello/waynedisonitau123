#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;


int main() {
  int n, m; cin >> n >> m;
  vector<pair<int, int>> v(n);
  for (int i = 0; i < n; ++i) {
    cin >> v[i].first >> v[i].second;
    --v[i].first;
    --v[i].second;
  }

  vector<int> prev(m, 1000000000);

  for (int i = 0; i < m; ++i) {
    int len = v.back().second - v.back().first + 1;
    if (i + len - 1 < m) {
      prev[i] = abs(i - v.back().first);
    }
  }


  vector<int> dp(m, 1000000000);
  deque<int> dq;
  for (int i = n - 2; i >= 0; --i) {
    fill(dp.begin(), dp.end(), 1000000000);
    dq.clear();

    auto insert = [&] (int x) {
      int v = prev[x];
      while (dq.size() && prev[dq.back()] >= v) dq.pop_back();
      dq.push_back(x);
    };

    int len = v[i].second - v[i].first + 1;
    int chlen = v[i + 1].second - v[i + 1].first + 1;
    int dqlen = len - chlen + 1;
    for (int j = 0; j < dqlen - 1; ++j) insert(j);

    for (int j = 0; j < m; ++j) {
      insert(dqlen - 1 + j);
      if (j + len - 1 < m) {
        dp[j] = abs(j - v[i].first) + prev[dq.front()];

        if (dq.front() == j) dq.pop_front();
      }

    }

    prev.swap(dp);

  }

  cout << *min_element(prev.begin(), prev.end()) << endl;
}
