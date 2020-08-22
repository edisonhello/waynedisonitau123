#include <bits/stdc++.h>
using namespace std;

struct node {
  node *l, *r;
  int sz, pri, v;
  node(int v) : l(0), r(0), sz(1), pri(rand()), v(v) {}
  int lz() { return l ? l->sz : 0; }
  int rz() { return r ? r->sz : 0; }
  void pull() { sz = lz() + rz() + 1; }
};

node *merge(node *a, node *b) {
  if (!a) return b;
  if (!b) return a;
  if (a->pri > b->pri) {
    a->r = merge(a->r, b);
    a->pull();
    return a;
  } else {
    b->l = merge(a, b->l);
    b->pull();
    return b;
  }
}

void split(node *s, int sz, node *&l, node *&r) {
  if (!s) { l = r = 0; return; }
  if (s->lz() >= sz) {
    r = s;
    split(s->l, sz, l, r->l);
    r->pull();
  } else {
    l = s;
    split(s->r, sz - 1 - s->lz(), l->r, r);
    l->pull();
  }
}

void dfs(node *now) {
  if (!now) return;
  if (now->l) dfs(now->l);
  cout << (char)now->v;
  if (now->r) dfs(now->r);
}

int main() {
  freopen("coding.in", "r", stdin);
  freopen("coding.out", "w", stdout);

  ios_base::sync_with_stdio(0); 
  cin.tie(0);
  string s; cin >> s;
  int n; cin >> n;
  vector<tuple<int, int, int>> v(n);
  for (int i = 0; i < n; ++i) {
    int a, b, c; cin >> a >> b >> c;
    v[i] = make_tuple(a, b, c);
  }
  reverse(v.begin(), v.end());
  node *root = 0;
  for (int i = 0; i < (int)s.size(); ++i) root = merge(root, new node(s[i]));
  // cerr << "bruh" << endl;
  for (auto [l, r, k] : v) {
    // cerr << "l r k " << l << ' ' << r << ' ' << k << endl;
    node *q, *w, *e, *t;
    split(root, l - 1, q, t);
    // cerr << "l r k " << l << ' ' << r << ' ' << k << endl;
    // cerr << "t, t size " << t << ' ' << t->sz << endl;
    split(t, r - l + 1, w, e);
    node *a, *b;
    // cerr << "w size " << w->sz << endl;
    split(w, k, a, b);
    // cerr << "l r k " << l << ' ' << r << ' ' << k << endl;
    root = merge(merge(merge(q, b), a), e);
    // cerr << "l r k " << l << ' ' << r << ' ' << k << endl;
  }

  dfs(root);
}
