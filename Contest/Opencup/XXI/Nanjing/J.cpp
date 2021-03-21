#include <bits/stdc++.h>
using namespace std;

constexpr int kInf = (1 << 30);

struct Node {
  array<int, 30> cnt{};
  int xv, m1, m2, cv;

  Node() = default;
  Node(int v) : xv(v), m1(v), m2(kInf), cv(1) {
    for (int i = 0; i < 30; ++i) cnt[i] = (v >> i & 1);
  }

  Node operator+(const Node &rhs) const {
    Node res;
    res.xv = xv ^ rhs.xv;
    res.m1 = min(m1, rhs.m1);
    res.cv = (m1 == res.m1 ? cv : 0) + (rhs.m1 == res.m1 ? rhs.cv : 0);
    res.m2 = kInf;
    for (int u : {m1, m2, rhs.m1, rhs.m2}) {
      if (u != res.m1) res.m2 = min(res.m2, u);
    }
    for (int i = 0; i < 30; ++i) res.cnt[i] = cnt[i] + rhs.cnt[i];
    return res;
  }

  void SetMax(int x) {
    assert(x > m1 && x < m2);
    for (int i = 0; i < 30; ++i) {
      if ((m1 >> i & 1) == 1) cnt[i] -= cv;
      if ((x >> i & 1) == 1) cnt[i] += cv;
    }
    if (cv & 1) {
      xv ^= m1;
      xv ^= x;
    }
    m1 = x;
  }
};

Node tree[1'000'000];
int tag[1'000'000];

void Update(int, int, int, int, int, int = 0);

void Push(int o, int l, int r) {
  if (tag[o] == -1) return;
  int m = (l + r) >> 1;
  Update(l, m, l, m, tag[o], o * 2 + 1);
  Update(m, r, m, r, tag[o], o * 2 + 2);
  tag[o] = -1;
}

void Build(int l, int r, const vector<int> &A, int o = 0) {
  if (r - l == 1) {
    tree[o] = Node(A[l]);
    return;
  }
  int m = (l + r) >> 1;
  Build(l, m, A, o * 2 + 1);
  Build(m, r, A, o * 2 + 2);
  tree[o] = tree[o * 2 + 1] + tree[o * 2 + 2];
}

void Update(int l, int r, int ql, int qr, int x, int o) {
  if (l >= qr || ql >= r) return;
  if (x <= tree[o].m1) return;
  if (l >= ql && r <= qr && x < tree[o].m2) {
    tag[o] = max(tag[o], x);
    tree[o].SetMax(x);
    return;
  }
  Push(o, l, r);
  int m = (l + r) >> 1;
  Update(l, m, ql, qr, x, o * 2 + 1);
  Update(m, r, ql, qr, x, o * 2 + 2);
  tree[o] = tree[o * 2 + 1] + tree[o * 2 + 2];
}

Node Query(int l, int r, int ql, int qr, int o = 0) {
  if (l >= ql && r <= qr) return tree[o];
  Push(o, l, r);
  int m = (l + r) >> 1;
  if (qr <= m) return Query(l, m, ql, qr, o * 2 + 1);
  if (ql >= m) return Query(m, r, ql, qr, o * 2 + 2);
  return Query(l, m, ql, qr, o * 2 + 1) + Query(m, r, ql, qr, o * 2 + 2);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N, Q;
  cin >> N >> Q;
  vector<int> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];
  Build(0, N, A);
  while (Q--) {
    int t, l, r, x;
    cin >> t >> l >> r >> x;
    l--;
    if (t == 1) {
      Update(0, N, l, r, x);
    } else {
      Node nd = Query(0, N, l, r);
      int g = nd.xv ^ x;
      if (g == 0) {
        cout << "0\n";
      } else {
        for (int i = 29; i >= 0; --i) {
          if (g >> i & 1) {
            cout << nd.cnt[i] + (x >> i & 1) << "\n";
            break;
          }
        }
      }
    }
  }
}
