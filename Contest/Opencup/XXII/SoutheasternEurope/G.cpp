#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, M;
  cin >> N >> M;
  vector<int> A(N), B(M);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
  }
  A.push_back(2'000'000'000);
  N++;
  for (int i = 0; i < M; ++i) {
    cin >> B[i];
  }
  sort(B.begin(), B.end());
  vector<int> f(N);
  vector<int> ds;
  for (int i = 0; i < N; ++i) {
    f[i] = lower_bound(B.begin(), B.end(), A[i]) - B.begin();
    ds.push_back(f[i] - i);
  }
  sort(ds.begin(), ds.end());
  ds.resize(unique(ds.begin(), ds.end()) - ds.begin());

  int K = ds.size();
  vector<map<int, int>> fw(K + 1);

  auto Update = [&](int p, int k, int v) {
    for (int i = p + 1; i <= K; i += i & -i) {
      {
        auto iter = fw[i].lower_bound(k);
        if (iter != fw[i].begin() && prev(iter)->second >= v) {
          continue;
        }
      }
      auto [iter, suc] = fw[i].emplace(k, v);
      assert(suc);
      iter = next(iter);
      while (iter != fw[i].end() && iter->second <= v) {
        iter = fw[i].erase(iter);
      }
    }
  };

  auto Query = [&](int p, int k) {
    int res = -1'000'000'000;
    for (int i = p + 1; i > 0; i -= i & -i) {
      auto iter = fw[i].lower_bound(k);
      if (iter != fw[i].begin()) {
        res = max(res, prev(iter)->second);
      }
    }
    return res;
  };

  vector<int> dp(N, -1'000'000'000);
  int ans = -1'000'000'000;
  for (int i = 0; i < N; ++i) {
    if (f[i] >= i) {
      dp[i] = 0;
    }
    {
      int key = f[i] - i + 1;
      int p = upper_bound(ds.begin(), ds.end(), key) - ds.begin();
      dp[i] = max(dp[i], Query(p - 1, A[i]) + 1);
    }
    {
      int key = f[i] - i;
      int p = lower_bound(ds.begin(), ds.end(), key) - ds.begin();
      Update(p, A[i], dp[i]);
    }
  }
  if (dp[N - 1] < 0) {
    cout << "-1\n";
  } else {
    cout << N - 1 - dp[N - 1] << "\n";
  }
}

