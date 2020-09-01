#include <bits/stdc++.h>
using namespace std;

int Solve() {
  int N;
  cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
  }
  vector<int> ds(A.begin(), A.end());
  sort(ds.begin(), ds.end());
  ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
  int M = ds.size();
  for (int i = 0; i < N; ++i) {
    A[i] = lower_bound(ds.begin(), ds.end(), A[i]) - ds.begin();
  }
  int res = 0;
  vector<int> to(N, -1);
  for (int i = 0; i < N; ++i) {
    vector<bool> used(M);
    for (int j = i; j < N; ++j) {
      if (used[A[j]]) break;
      used[A[j]] = true;
      res = max(res, j - i + 1);
      to[i] = j;
    }
  }

  vector<int> tree(N * 4);
  vector<int> tag(N * 4);
  vector<int> left(N * 4);
  vector<int> val(N * 4);

  for (int i = 1; i < N; ++i) {
    auto Build = [&]() {
      auto dfs = [&](auto dfs, int l, int r, int o = 0) {
        tag[o] = -1;
        if (r - l == 1) {
          tree[o] = min(i - 1, to[l]);
          left[o] = l;
          val[o] = tree[o] - l + 1;
          return;
        }
        int m = (l + r) >> 1;
        dfs(dfs, l, m, o * 2 + 1);
        dfs(dfs, m, r, o * 2 + 2);
        left[o] = min(left[o * 2 + 1], left[o * 2 + 2]);
        val[o] = max(val[o * 2 + 1], val[o * 2 + 2]);
      };

      dfs(dfs, 0, i);
    };

    auto QueryTree = [&](int p) {
      auto dfs = [&](auto dfs, int l, int r, int o = 0) {
        if (r - l == 1) {
          return tree[o];
        }
        if (tag[o] != -1) {
          for (int k = 1; k <= 2; ++k) {
            tag[o * 2 + k] = tag[o];
            tree[o * 2 + k] = tag[o];
            val[o * 2 + k] = min(val[o * 2 + k], tag[o] - left[o * 2 + k] + 1);
          }
          tag[o] = -1;
        }
        int m = (l + r) >> 1;
        if (p < m) return dfs(dfs, l, m, o * 2 + 1);
        else return dfs(dfs, m, r, o * 2 + 2);
      };

      return dfs(dfs, 0, i);
    };

    auto Modify = [&](int ql, int qr, int v) {
      auto dfs = [&](auto dfs, int l, int r, int o = 0) {
        if (l >= qr || ql >= r) return;
        if (l >= ql && r <= qr) {
          tag[o] = v;
          tree[o] = v;
          val[o] = min(val[o], v - left[o] + 1);
          return;
        }
        if (tag[o] != -1) {
          for (int k = 1; k <= 2; ++k) {
            tag[o * 2 + k] = tag[o];
            tree[o * 2 + k] = tag[o];
            val[o * 2 + k] = min(val[o * 2 + k], tag[o] - left[o * 2 + k] + 1);
          }
          tag[o] = -1;
        }
        int m = (l + r) >> 1;
        dfs(dfs, l, m, o * 2 + 1);
        dfs(dfs, m, r, o * 2 + 2);
        left[o] = min(left[o * 2 + 1], left[o * 2 + 2]);
        val[o] = max(val[o * 2 + 1], val[o * 2 + 2]);
      };

      dfs(dfs, 0, i);
    };

    auto ModifyVal = [&](int p) {
      auto dfs = [&](auto dfs, int l, int r, int o = 0) {
        if (r - l == 1) {
          val[o] = -1;
          left[o] = 1e9;
          return;
        }
        if (tag[o] != -1) {
          for (int k = 1; k <= 2; ++k) {
            tag[o * 2 + k] = tag[o];
            tree[o * 2 + k] = tag[o];
            val[o * 2 + k] = min(val[o * 2 + k], tag[o] - left[o * 2 + k] + 1);
          }
          tag[o] = -1;
        }
        int m = (l + r) >> 1;
        if (p < m) dfs(dfs, l, m, o * 2 + 1);
        else dfs(dfs, m, r, o * 2 + 2);
        left[o] = min(left[o * 2 + 1], left[o * 2 + 2]);
        val[o] = max(val[o * 2 + 1], val[o * 2 + 2]);
      };

      dfs(dfs, 0, i);
    };

    Build();

    vector<bool> used(M);
    vector<vector<int>> ev(M);
    for (int j = 0; j < i; ++j) {
      ev[A[j]].push_back(j);
    }

    auto Erase = [&](int p) {
      int L = p;
      for (int d = 10; d >= 0; --d) {
        if (L - (1 << d) >= 0 && QueryTree(L - (1 << d)) >= p) {
          L -= (1 << d);
        }
      }
      if (L < p) {
        Modify(L, p, p - 1);
      }
      ModifyVal(p);
    };

    for (int j = i; j < N; ++j) {
      if (used[A[j]]) break;
      used[A[j]] = true;
      for (int u : ev[A[j]]) Erase(u);
      res = max(res, j - i + 1 + val[0]);
    }
  }
  return res;
}

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; ++i) {
    cout << "Case #" << i + 1 << ": ";
    cout << Solve() << "\n";
  }
}
