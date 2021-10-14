#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N, Q;
  cin >> N >> Q;
  vector<int> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];
  vector<vector<vector<int>>> Or(31, vector<vector<int>>(1));
  vector<vector<int>> OrV(31);
  vector<vector<vector<int>>> And(31, vector<vector<int>>(1));
  vector<vector<int>> AndV(31);
  for (int pc = 0; pc <= 30; ++pc) {
    for (int i = 0; i < N; ++i) {
      if (__builtin_popcount(A[i]) <= pc) {
        Or[pc][0].push_back(A[i]);
        OrV[pc].push_back(i);
      }
      if (__builtin_popcount(A[i]) >= pc) {
        And[pc][0].push_back(A[i]);
        AndV[pc].push_back(i);
      }
    }
    for (int i = 1; (1 << i) <= Or[pc][0].size(); ++i) {
      Or[pc].emplace_back(Or[pc][0].size());
      for (int j = 0; j + (1 << i) <= Or[pc][0].size(); ++j) {
        Or[pc][i][j] = Or[pc][i - 1][j] | Or[pc][i - 1][j + (1 << (i - 1))];
      }
    }
    for (int i = 1; (1 << i) <= And[pc][0].size(); ++i) {
      And[pc].emplace_back(And[pc][0].size());
      for (int j = 0; j + (1 << i) <= And[pc][0].size(); ++j) {
        And[pc][i][j] = And[pc][i - 1][j] & And[pc][i - 1][j + (1 << (i - 1))];
      }
    }
  }
  // cout << "haha" << endl;

  auto QueryAnd = [&](int bit, int l, int r) {
    l = lower_bound(AndV[bit].begin(), AndV[bit].end(), l) - AndV[bit].begin();
    r = lower_bound(AndV[bit].begin(), AndV[bit].end(), r) - AndV[bit].begin();
    if (l == r) return -1;
    int p = 31 - __builtin_clz(r - l);
    return And[bit][p][l] & And[bit][p][r - (1 << p)];
  };

  auto QueryOr = [&](int bit, int l, int r) {
    l = lower_bound(OrV[bit].begin(), OrV[bit].end(), l) - OrV[bit].begin();
    r = lower_bound(OrV[bit].begin(), OrV[bit].end(), r) - OrV[bit].begin();
    // cout << "l = " << l << " r = " << r << " size = " << Or[bit][0].size() << endl;
    if (l == r) return -1;
    int p = 31 - __builtin_clz(r - l);
    return Or[bit][p][l] | Or[bit][p][r - (1 << p)];
  };

  map<int, vector<int>> pos;
  for (int i = 0; i < N; ++i) pos[A[i]].push_back(i);

  while (Q--) {
    int L, R;
    cin >> L >> R;
    L--;
    bool ok = false;
    for (int bit = 0; bit <= 30; ++bit) {
      if (bit + 1 <= 30) {
        int x = QueryAnd(bit + 1, L, R);
        // cout << "x = " << x << endl;
        int y = QueryOr(bit, L, R);
        // cout << "y = " << y << endl;
        // cout << "bit = " << bit << " x = " << x << " y = " << y << endl;
        if (x != -1 && y != -1 && x == y) {
          ok = true;
          break;
        }
      }
      int y = QueryOr(bit, L, R);
      if (y != -1) {
        auto iter = pos.find(y);
        if (iter != pos.end()) {
          // cout << "L = " << L << " R = " << R << endl;
          // cout << "x = " << x << " y = " << y << endl;
          int l = lower_bound(iter->second.begin(), iter->second.end(), L) - iter->second.begin();
          int r = lower_bound(iter->second.begin(), iter->second.end(), R) - iter->second.begin();
          if (r - l >= 2) {
            int x = QueryAnd(bit, L, R);
            if (x == y) {
              ok = true;
              break;
            }
          }
        }
      }
    }
    cout << (ok ? "YES" : "NO") << "\n";
  }
  return 0;
}
