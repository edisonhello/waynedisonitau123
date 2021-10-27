#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N;
  cin >> N;
  vector<vector<int>> p(2, vector<int>(N)), h(2, vector<int>(N));
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> p[i][j];
    }
    for (int j = 0; j < N; ++j) {
      cin >> h[i][j];
    }
  }

  vector<vector<int>> order(2, vector<int>(N));
  for (int i = 0; i < 2; ++i) {
    iota(order[i].begin(), order[i].end(), 0);
    sort(order[i].begin(), order[i].end(), [&](int x, int y) { return p[i][x] < p[i][y]; });
  }

  int ptr = 0, i = 0, j = 0;
  set<pair<int, int>> A, B;
  vector<vector<int>> ans(2);
  while (ptr < N) {
    while (i < N && p[0][order[0][i]] == p[0][order[0][ptr]]) {
      A.insert(make_pair(h[0][order[0][i]], order[0][i]));
      i++;
    }
    while (j < N && p[1][order[1][j]] == p[1][order[1][ptr]]) {
      B.insert(make_pair(h[1][order[1][j]], order[1][j]));
      j++;
    }
    if (A.size() < B.size()) {
      for (auto t : A) {
        auto iter = B.lower_bound(make_pair(t.first, -1));
        if (iter == B.begin()) {
          cout << "impossible\n";
          return 0;
        }
        ans[0].push_back(t.second);
        ans[1].push_back(prev(iter)->second);
        B.erase(prev(iter));
      }
      A.clear();
      ptr = i;
    } else {
      for (auto t : B) {
        auto iter = A.upper_bound(make_pair(t.first, N));
        if (iter == A.end()) {
          cout << "impossible\n";
          return 0;
        }
        ans[0].push_back(iter->second);
        ans[1].push_back(t.second);
        A.erase(iter);
      }
      B.clear();
      ptr = j;
    }
  }
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < N; ++j) cout << ans[i][j] + 1 << " ";
    cout << "\n";
  }
  return 0;
}

