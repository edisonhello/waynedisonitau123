#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> g[200005];
map<pair<int, int>, pair<long long, int>> info;
int sz[200005], mxszi[200005];
int dep[200005];
int p[20][200005];
int j[200005];

const int mod = 1000000007;

void dfs(int now, int pa) {
  sz[now] = 1;
  p[0][now] = pa;
  j[now] = pa;
  for (int i : g[now]) if (i != pa) {
    dep[i] = dep[now] + 1;
    dfs(i, now);
    info[minmax(now, i)].first = 1ll * sz[i] * (n - sz[i]) % mod;
    sz[now] += sz[i];
    if (sz[i] > sz[mxszi[now]]) {
      mxszi[now] = i;
    }
  }
}

// struct segtree {
//   struct node {
//     node *l, *r;
//     int v;
//   } *root;
//   int R;
//   node() : root(0), R(0) {}
//   void Build(vector<int> &v) {
//     R = v.size() - 1;
//     auto dfs = [&] (auto self, node *now, int l, int r) {
// 
//     };
// 
//     dfs(dfs, root = new node(), 1, R);
//   }
// }

int cc, bel[200005], icpos[200005];
int chead[200005], ccon[200005];
vector<int> cmem[200005];
pair<int, int> mean[200005];
long long affect[200005];
int val[200005];

void dfs2(int now, int pa, int _c, int _cpos) {
  bel[now] = _c;
  icpos[now] = _cpos;
  cmem[_c].push_back(now);
  if (pa) {
    mean[now] = minmax(now, pa);
    affect[now] = info[mean[now]].first;
    val[now] = info[mean[now]].second;
  }

  dfs2(mxszi[now], now, _c, _cpos + 1);

  for (int i : g[now]) if (i != pa && i != mxszi[now]) {
    ++cc;
    chead[cc] = mxszi[now];
    ccon[cc] = now;
    cmem[cc].push_back(0);
    dfs2(i, now, cc, 1);
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int m; cin >> n >> m;
  for (int i = 1; i < n; ++i) {
    int u, v, w; cin >> u >> v >> w;
    g[u].push_back(v);
    g[v].push_back(u);
    info[minmax(u, v)] = make_pair(-1, w);
  }

  dfs(1, 0);
  for (int z = 1; z < 20; ++z) for (int i = 1; i <= n; ++i) 
    p[z][i] = p[z - 1][p[z - 1][i]];

  long long tot = 0;
  for (auto &p : info) {
    tot += p.second.first * p.second.second % mod;
  }

  tot %= mod;

  // dfs2(1, 0, ++cc, 1);
  
  function<int(int)> Find = [&] (int x) {
    int y = j[x];
    if (y == 0) return 1;
    if (info[minmax(y, p[0][y])].second == 1) return j[x] = Find(y);
    else return y;
  };

  auto LCA = [&] (int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    for (int z = 19; z >= 0; --z) if ((dep[v] - dep[u]) & (1 << z))
      v = p[z][v];
    if (u == v) return u;
    for (int z = 19; z >= 0; --z) if (p[z][u] != p[z][v])
      u = p[z][u], v = p[z][v];
    return p[0][u];
  };

  cout << tot % mod << '\n';
  while (m--) {
    auto Go = [&] (int l, int x) {
      while (dep[x] > dep[l]) {
        auto &pp = info[minmax(x, p[0][x])];
        int o = pp.second;
        int q = floor(sqrt(o + 0.5));
        tot -= pp.first * o % mod;
        tot += pp.first * q % mod;
        tot = (tot % mod + mod) % mod;
        pp.second = q;
        x = Find(x);
      }
    };

    int u, v; cin >> u >> v;
    int l = LCA(u, v);
    Go(l, u);
    Go(l, v);
    cout << tot % mod << '\n';
  }
}
