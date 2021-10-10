#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define ll int64_t

int64_t a[100005];
vector<int> g[100005];
int64_t pre[100005];
int in[100005], out[100005], dt, at[100005];

int p[18][100005], d[100005];

void dfs(int now, int pa) {
  p[0][now] = pa;
  ++dt;
  in[now] = dt;
  at[dt] = now;
  pre[now] += a[now];
  for (int i : g[now]) if (i != pa) {
    pre[i] = pre[now];
    d[i] = d[now] + 1;
    dfs(i, now);
  }
  out[now] = dt;
}

struct node {
  node *l, *r;
  ll val;
  node() : l(0), r(0), val(0) {}
  void add(ll x) {
    val += x;
  }
  void push() {
    if (val) {
      l->add(val);
      r->add(val);
      val = 0;
    }
  }
} *root;

#define mid ((l + r) >> 1)
void build(node *now, int l, int r) {
  if (l == r) {
    now->val = pre[at[l]];
    return;
  }

  build(now->l = new node(), l, mid);
  build(now->r = new node(), mid + 1, r);
}

void modify(node *now, int l, int r, int ml, int mr, int v) {
  if (mr < l || r < ml) return;
  if (ml <= l && r <= mr) {
    now->add(v);
    return;
  }
  now->push();
  modify(now->l, l, mid, ml, mr, v);
  modify(now->r, mid + 1, r, ml, mr, v);
}

int query(node *now, int l, int r, int x) {
  if (x < l || x > r) return 0;
  if (l == r) return now->val;
  now->push();
  if (x <= mid) return query(now->l, l, mid, x);
  return query(now->r, mid + 1, r, x);
}

int lca(int u, int v) {
  if (u == v) return u;
  if (d[u] > d[v]) swap(u, v);
  for (int i = 17; i >= 0; --i) if ((1 << i) & (d[v] - d[u])) v = p[i][v];
  if (u == v) return u;
  for (int i = 17; i >= 0; --i) if (p[i][u] != p[i][v]) {
    u = p[i][u];
    v = p[i][v];
  }
  return p[0][u];
}

int32_t main() {
  int n, q;
  cin >> n >> q;

  for (int i = 1; i <= n; ++i) cin >> a[i], a[i] = abs(a[i]);

  for (int i = 1; i < n; ++i) {
    int u, v; cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  dfs(1, 0);

  build(root = new node(), 1, n);

  for (int z = 1; z < 18; ++z) {
    for (int i = 1; i <= n; ++i) p[z][i] = p[z - 1][p[z - 1][i]];
  }

  for (int i = 0; i < q; ++i) {
    int c, a, b;
    cin >> c >> a >> b;
    if (c == 1) {
      b = abs(b);
      int diff = b - ::a[a];
      ::a[a] = b;
      modify(root, 1, n, in[a], out[a], diff);
    } else {
      int l = lca(a, b);
      int pa = query(root, 1, n, in[a]);
      int pb = query(root, 1, n, in[b]);
      int pl = query(root, 1, n, in[p[0][l]]);
      cout << (pa + pb - pl * 2 - ::a[l]) * 2 - ::a[a] - ::a[b] << '\n';
    }
  }

}
