#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

struct DisjointSet {
  vector<int> uf, sz;
  vector<pair<int *, int>> hist;
  vector<int> pv;

  DisjointSet(int n) : uf(n), sz(n, 1) { 
    iota(uf.begin(), uf.end(), 0); 
    hist.reserve(30 * n);
    pv.reserve(n * 4);
  }

  int Find(int x) {
    if (x == uf[x]) return x;
    return Find(uf[x]);
  };

  void Merge(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return;
    if (sz[x] > sz[y]) swap(x, y);
    Assign(&uf[x], y);
    Assign(&sz[y], sz[x] + sz[y]);
  }

  void Assign(int *p, int v) {
    hist.emplace_back(p, *p);
    *p = v;
  }

  void Save() { pv.push_back(hist.size()); }

  void Undo() {
    int g = pv.back();
    pv.pop_back();
    while (hist.size() > g) {
      *hist.back().first = hist.back().second;
      hist.pop_back();
    }
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  if (m == 0) {
    for (int i = 0; i < n; ++i) cout << "0\n";
    return 0;
  }
  vector<int> st(m), ed(m), w(m);
  vector<int> deg(n);
  vector<vector<int>> g(n);
  for (int i = 0; i < m; ++i) {
    cin >> st[i] >> ed[i] >> w[i];
    --st[i];
    --ed[i];
    ++deg[st[i]];
    ++deg[ed[i]];
  }
  for (int i = 0; i < n; ++i) g[i].reserve(deg[i]);
  for (int i = 0; i < m; ++i) {
    g[st[i]].push_back(i);
    g[ed[i]].push_back(i);
  }
  vector<pair<int, int>> qr;
  vector<int> point(n);
  vector<int> cnt(m);
  for (int i = 0; i < n; ++i) {
    for (int u : g[i]) {
      qr.emplace_back(u, 0);
      cnt[u]++;
    }
    point[i] = qr.size();
    for (int u : g[i]) {
      qr.emplace_back(u, w[u]);
      cnt[u]++;
    }
  }

  vector<int64_t> res(qr.size());
  DisjointSet djs(n);

  auto Contract = [&](int l, int r, vector<int> v, vector<int> &x, vector<int> &y) {
    sort(v.begin(), v.end(), [&](int i, int j) {
      if (w[i] == w[j]) return i < j;
      return w[i] < w[j];
    });
    djs.Save();
    for (int i = l; i < r; ++i) {
      djs.Merge(st[qr[i].first], ed[qr[i].first]);
    }
    for (int i = 0; i < v.size(); ++i) {
      if (djs.Find(st[v[i]]) != djs.Find(ed[v[i]])) {
        x.push_back(v[i]);
        djs.Merge(st[v[i]], ed[v[i]]);
      }
    }
    djs.Undo();
    djs.Save();
    for (int i = 0; i < x.size(); ++i) {
      djs.Merge(st[x[i]], ed[x[i]]);
    }
    for (int i = 0; i < v.size(); ++i) {
      if (djs.Find(st[v[i]]) != djs.Find(ed[v[i]])) {
        y.push_back(v[i]);
        djs.Merge(st[v[i]], ed[v[i]]);
      }
    }
    djs.Undo();
  };

  auto Solve = [&](auto self, int l, int r, const vector<int> &v, int64_t cost) {
    if (r - l == 1) {
      w[qr[l].first] = qr[l].second;
      if (st[qr[l].first] == ed[qr[l].first]) {
        res[l] = cost;
      } else {
        int k = qr[l].second;
        for (int i = 0; i < v.size(); ++i) k = min(k, w[v[i]]);
        res[l] = cost + k;
      }
      return;
    }
    int m = (l + r) >> 1;
    vector<int> lv = v, rv = v;
    vector<int> x, y;
    for (int i = m; i < r; ++i) {
      if (--cnt[qr[i].first] == 0) {
        lv.push_back(qr[i].first);
      }
    }
    Contract(l, m, lv, x, y);
    int64_t lc = cost, rc = cost;
    djs.Save();
    for (int i = 0; i < x.size(); ++i) {
      lc += w[x[i]];
      djs.Merge(st[x[i]], ed[x[i]]);
    }
    self(self, l, m, y, lc);
    djs.Undo();
    x.clear();
    y.clear();
    for (int i = m; i < r; ++i) cnt[qr[i].first]++;
    for (int i = l; i < m; ++i) {
      if (--cnt[qr[i].first] == 0) {
        rv.push_back(qr[i].first);
      }
    }
    Contract(m, r, rv, x, y);
    djs.Save();
    for (int i = 0; i < x.size(); ++i) {
      rc += w[x[i]];
      djs.Merge(st[x[i]], ed[x[i]]);
    }
    self(self, m, r, y, rc);
    djs.Undo();
    for (int i = l; i < m; ++i) cnt[qr[i].first]++;
  };

  Solve(Solve, 0, qr.size(), vector<int>(), 0);
  for (int i = 0; i < n; ++i) {
    int64_t ans = res[point[i] - 1];
    for (int u : g[i]) ans += w[u];
    cout << ans << "\n";
  }
}
