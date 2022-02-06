#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  auto start = chrono::system_clock::now();
  int N, M;
  cin >> N >> M;
  int Q;
  cin >> Q;
  unordered_set<int64_t> s;
  for (int i = 0; i < Q; ++i) {
    int a, b;
    cin >> a >> b;
    s.emplace(1000000000LL * a + b);
  }

  int ans = 1'000'000'000;
  set<pair<int, int>> visited;

  auto Brute = [&](int i, int j) {
    int step = 0;
    while (i < N || j < M) {
      step++;
      if (i <= j) {
        i += j;
      } else {
        j += i;
      }
    }
    return step;
  };

  auto Dfs = [&](auto dfs, int i, int j, int step) -> void {
    // if (visited.find(make_pair(i, j)) != visited.end()) {
    //   return;
    // }
    // visited.emplace(i, j);
    if (i >= N && j >= M) {
      ans = min(ans, step);
      return;
    }
    auto cur = chrono::system_clock::now();
    if (chrono::duration_cast<chrono::milliseconds>(cur - start).count() >= 970) {
      return;
    }
    int next = s.find(1000000000LL * i + j) != s.end() ? i + j + 1 : i + j;
    if (i <= j) {
      if (step + 1 < ans && min(next, N) > i) {
        dfs(dfs, min(next, N), j, step + 1);
      }
      if (step + 1 < ans && min(next, M) > j) {
        dfs(dfs, i, min(next, M), step + 1);
      }
    } else {
      if (step + 1 < ans && min(next, M) > j) {
        dfs(dfs, i, min(next, M), step + 1);
      }
      if (step + 1 < ans && min(next, N) > i) {
        dfs(dfs, min(next, N), j, step + 1);
      }
    }
  };

  if (s.find(1000000000LL * 1 + 1) != s.end()) {
    Dfs(Dfs, 1, min(M, 3), 1);
    start = chrono::system_clock::now();
    Dfs(Dfs, min(N, 3), 1, 1);
  } else {
    Dfs(Dfs, 1, 2, 1);
    start = chrono::system_clock::now();
    Dfs(Dfs, 2, 1, 1);
  }
  cout << ans << "\n";
}

