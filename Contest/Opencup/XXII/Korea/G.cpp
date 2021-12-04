#include <bits/stdc++.h>
using namespace std;

struct Node {
  int64_t best;
  int64_t sum;
  int64_t lbest;
  int64_t rbest;
  int64_t lmax;
  int64_t lmin;

  Node() = default;
  Node(int v) : best(min(v, 0)), sum(v), lbest(min(v, 0)), rbest(min(v, 0)), lmax(max(v, 0)), lmin(min(v, 0)) {}

  Node operator+(const Node& rhs) const {
    Node res;
    res.best = min(best, rhs.best);
    res.sum = sum + rhs.sum;
    res.lbest = min(lbest, sum + rhs.lbest);
    res.rbest = min(rhs.rbest, rhs.sum + rbest);
    res.best = min(res.best, rbest + rhs.lbest);
    res.lmax = max(lmax, sum + rhs.lmax);
    res.lmin = min(lmin, sum + rhs.lmin);
    return res;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, Q;
  cin >> N >> Q;
  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
  }

  vector<Node> tree(N * 4);

  auto Build = [&]() {
    auto dfs = [&](auto dfs, int l, int r, int o = 0) -> void {
      if (r - l == 1) {
        tree[o] = Node(A[l]);
        return;
      }
      int m = (l + r) >> 1;
      dfs(dfs, l, m, o * 2 + 1);
      dfs(dfs, m, r, o * 2 + 2);
      tree[o] = tree[o * 2 + 1] + tree[o * 2 + 2];
    };

    return dfs(dfs, 0, N);
  };

  auto Update = [&](int p, int x) {
    auto dfs = [&](auto dfs, int l, int r, int o = 0) -> void {
      if (r - l == 1) {
        tree[o] = Node(x);
        return;
      }
      int m = (l + r) >> 1;
      if (p < m) dfs(dfs, l, m, o * 2 + 1);
      else dfs(dfs, m, r, o * 2 + 2);
      tree[o] = tree[o * 2 + 1] + tree[o * 2 + 2];
    };

    return dfs(dfs, 0, N);
  };

  auto Query = [&](int ql, int qr) {
    auto dfs = [&](auto dfs, int l, int r, int o = 0) -> Node {
      if (l >= qr || ql >= r) return Node(0);
      if (l >= ql && r <= qr) return tree[o];
      int m = (l + r) >> 1;
      return dfs(dfs, l, m, o * 2 + 1) + dfs(dfs, m, r, o * 2 + 2);
    };

    return dfs(dfs, 0, N);
  };

  Build();

  while (Q--) {
    int type;
    cin >> type;
    if (type == 2) {
      int i, x;
      cin >> i >> x;
      i--;
      Update(i, x);
    } else {
      int l, r, x;
      cin >> l >> r >> x;
      l--;

      auto Solve = [&]() -> int64_t {
        Node nd = Query(0, l);
        if (nd.best <= -x) {
          return 0;
        }
        int y = nd.sum - nd.lmax + x; // after l - 1
        // cout << "y = " << y << endl;
        int to = N + 1;
        if (Query(l, N).lmax + y >= x) {
          for (int d = 20; d >= 0; --d) {
            if (to - (1 << d) >= l) {
              Node p = Query(l, to - (1 << d));
              if (p.lmax + y >= x) {
                to -= (1 << d);
              }
            } 
          }
        }
        // cout << "to = " << to << endl;
        if (to <= r) {
          if (Query(l, to).lmin + y <= (x + 9) / 10) {
            y = (x + 9) / 10; 
          } else {
            // cout << "here" <<endl;
            Node nd = Query(to, r); 
            // cout << "this = " << nd.best + x - (x + 9) / 10 << endl;
            // cout << "nd.best = " << nd.best << endl;
            if (nd.best + x - (x + 9) / 10 > 0) {
              // nd = Query(to - 1, r);
              y = nd.sum - nd.lmax + x;
            } else {
              y = (x + 9) / 10;
              // cout << "correct" << endl;
            }
          }
        } else {
          Node nd = Query(l, r);
          if (y + nd.lmin <= (x + 9) / 10) {
            y = (x + 9) / 10;
          } else {
            y += nd.sum;
          }
        }
        // after r
        // cout << "after y = " << y << endl;
        
        to = N + 1;
        if (Query(r, N).lmax + y >= x) {
          for (int d = 20; d >= 0; --d) {
            if (to - (1 << d) >= r) {
              Node p = Query(r, to - (1 << d));
              if (p.lmax + y >= x) {
                to -= (1 << d);
              }
            } 
          }
        }
        if (Query(r, N).lmax + y >= x) {
          // none
          Node nd = Query(r, to);
          if (y + nd.lmin <= 0) {
            return 0;
          }
          y = x;
          nd = Query(to, N);
          if (y + nd.best <= 0) {
            return 0;
          }
          return y + nd.sum - nd.lmax;
        } else {
          // cout << "here" << endl;
          Node nd = Query(r, N);
          if (y + nd.lmin <= 0) {
            return 0;
          }
          return y + nd.sum;
        }
      };

      cout << Solve() << "\n";
    }
  }
}

