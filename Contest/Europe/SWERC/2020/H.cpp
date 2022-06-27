#include <bits/stdc++.h>
using namespace std;

struct node {
  node *l, *r;
  int sum;
  node() : l(0), r(0), sum(0) {}
  node(node *ref) : l(ref->l), r(ref->r), sum(ref->sum) {}
  void pull() { sum = l->sum + r->sum; }
} * root[100005];

#define mid ((l + r) >> 1)
void build(node *now, int l, int r) {
  if (l == r) return;

  build(now->l = new node(), l, mid);
  build(now->r = new node(), mid + 1, r);
}

void modify(node *now, int l, int r, int x, int v) {
  if (l == r) {
    now->sum += v;
    return;
  }
  if (x <= mid)
    modify(now->l = new node(now->l), l, mid, x, v);
  else
    modify(now->r = new node(now->r), mid + 1, r, x, v);
  now->pull();
}

int query(node *now, int l, int r, int ql, int qr) {
  if (qr < l || r < ql) return 0;
  if (ql <= l && r <= qr) return now->sum;
  return query(now->l, l, mid, ql, qr) + query(now->r, mid + 1, r, ql, qr);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  cin.ignore();

  build(root[0] = new node(), 0, n - 1);

  for (int i = 1; i <= n; ++i) {
    root[i] = new node(root[i - 1]);

    string s;
    getline(cin, s);

    stringstream ss(s);
    while (ss >> s) {
      int x = atoi(s.data() + 1);
      if (s[0] == '+')
        modify(root[i], 0, n - 1, x, 1);
      else
        modify(root[i], 0, n - 1, x, -1);
    }
  }

  int cur = 0;
  for (int i = 1; i <= n; ++i) {
    int d;
    cin >> d;
    int add = query(root[d], 0, n - 1, cur, n - 1);
    cur += add;
    if (cur >= n) cur -= n;
  }

  cout << cur << endl;
}


