#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, K;
  cin >> N >> K;
  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
  }
  vector<int> ds(A.begin(), A.end());
  sort(ds.begin(), ds.end());
  ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
  int M = ds.size();
  vector<vector<int>> pos(M);
  for (int i = 0; i < N; ++i) {
    int p = lower_bound(ds.begin(), ds.end(), A[i]) - ds.begin(); 
    pos[p].push_back(i);
  }

  auto Solve = [&](const vector<int>& buffer) {
    vector<int> pref(buffer.size() + 1);
    for (int i = 0; i < buffer.size(); ++i) {
      pref[i + 1] = pref[i] + buffer[i];
    }
    int res = accumulate(buffer.begin(), buffer.end(), 0), best = -1'000'000'000;
    for (int i = 0; i < buffer.size(); ++i) {
      best = max(best, 2 * pref[i] - i);
      res = max(res, pref.back() - 2 * pref[i + 1] + i + 1 + best);
    }
    return res;
  };

  int ans = 0;
  for (int i = 0; i < M; ++i) {
    int v = ds[i] - K;
    auto iter = lower_bound(ds.begin(), ds.end(), v);
    ans = max(ans, static_cast<int>(pos[i].size()));
    if (K != 0) {
      if (iter != ds.end() && *iter == v) {
        vector<int> buffer;
        int e = iter - ds.begin();
        int j = 0, k = 0;
        while (j < pos[i].size() && k < pos[e].size()) {
          if (pos[i][j] < pos[e][k]) {
            buffer.push_back(1);
            j++;
          } else {
            buffer.push_back(0);
            k++;
          }
        }
        while (j < pos[i].size()) {
          buffer.push_back(1);
          j++;
        }
        while (k < pos[e].size()) {
          buffer.push_back(0);
          k++;
        }
        ans = max(ans, Solve(buffer));
      }
    }
  }
  cout << ans << "\n";
}

