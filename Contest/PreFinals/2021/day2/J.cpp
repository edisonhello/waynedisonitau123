#include <bits/stdc++.h>
using namespace std;



int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);

  int q, O, F; cin >> q >> O >> F;

  vector<tuple<int, int, int>> qs;
  vector<vector<int>> g(200005);

  int n = 1;

  for (int i = 0; i < q; ++i) {
    int c; cin >> c;
    if (c == 1) {
      int x; cin >> x; ++x;
      qs.emplace_back(1, x, ++n);
      g[x].push_back(n);
    } else {
      qs.emplace_back(2, -1, -1);
    }
  }

  vector<int> pa(n + 3), sz(n + 3), mxchi(n + 3, 0);
  auto dfs = [&] (auto dfs, int now, int _pa) -> void {
    pa[now] = _pa;
    sz[now] = 1;
    for (int i : g[now]) {
      dfs(dfs, i, now);
      sz[now] += sz[i];
      if (sz[i] > sz[mxchi[now]]) mxchi[now] = i;
    }
  };

  int ccc = 0;
  vector<int> cn(n + 3), icpos(n + 3), cpa(n + 3), clen(n + 3);
  auto dfs2 = [&] (auto dfs, int now, int _pa, int ccn, int cpos) -> void {
    cn[now] = ccn;
    icpos[now] = cpos;
    clen[ccn] = cpos;
    for (int i : g[now]) {
      if (i == mxchi[now]) {
        dfs(dfs, i, now, ccn, cpos + 1);
      } else {
        int nccc = ++ccc;
        cpa[nccc] = now;
        dfs(dfs, i, now, nccc, 1);
      }
    }
  };

  dfs(dfs, 1, 0);
  dfs2(dfs2, 1, 0, ++ccc, 1);

  struct Seg {
    struct node {
      node *l, *r;
      int mn, mnc, tag;
      node() : l(0), r(0), mn(0), mnc(1), tag(0) {}
      void addtag(int w) {
        tag += w;
        mn += w;
      }
      void push() {
        if (tag) {
          l->addtag(tag);
          r->addtag(tag);
          tag = 0;
        }
      }
      void pull() {
        mn = min(l->mn, r->mn);
        mnc = (mn == l->mn ? l->mnc : 0) + (mn == r->mn ? r->mnc : 0);
      }
    } *root;

#define mid ((l + r) >> 1)
    void build(node *now, int l, int r) {
      if (l == r) return;
      build(now->l = new node(), l, mid);
      build(now->r = new node(), mid + 1, r);
      now->pull();
    }

    void add(node *now, int l, int r, int ml, int mr, int v) {
      if (r < ml || mr < l) return;
      if (ml <= l && r <= mr) {
        now->addtag(v);
        return;
      }
      now->push();
      add(now->l, l, mid, ml, mr, v);
      add(now->r, mid + 1, r, ml, mr, v);
      now->pull();
    }

    int query(node *now, int l, int r, int ql, int qr, int v) {
      if (r < ql || qr < l) return 0;
      if (ql <= l && r <= qr) {
        if (v == 1) assert(now->mn != 0);
        if (now->mn == v) return now->mnc;
        return 0;
      }
      now->push();
      return query(now->l, l, mid, ql, qr, v) + query(now->r, mid + 1, r, ql, qr, v);
    }
#undef mid

    int N;

    Seg() = default;
    Seg(int n) : N(n) { build(root = new node(), 1, N); }

    void add(int l, int r) { add(root, 1, N, l, r, 1); }
    void remove(int l, int r) { add(root, 1, N, l, r, -1); }
    int query_zero(int l, int r) { return query(root, 1, N, l, r, 0); }
    int query_one(int l, int r) { return query(root, 1, N, l, r, 1); }
  };

  struct Maint {
    vector<Seg> segs;
    int d;
    int curans;
    vector<int> *cn, *icpos, *cpa, *clen;
    Maint(int ccc, int d, vector<int> &cn, vector<int> &icpos, vector<int> &cpa, vector<int> &clen) : d(d), curans(0), cn(&cn), icpos(&icpos), cpa(&cpa), clen(&clen) {
      segs.resize(ccc + 3);
      for (int i = 1; i <= ccc; ++i) {
        segs[i] = Seg(clen[i]);
      }
    }

    void add(int x) {
      // cerr << "Maint " << d << ": " << " add " << x << endl;
      int dd = d;
      while (x && dd) {
        int xc = (*cn)[x];
        int xcp = (*icpos)[x];
        
        int dolen = min(dd, xcp);
        int r = xcp;
        int l = r - dolen + 1;
        dd -= dolen;

        // cerr << "do on chain " << xc << " l r " << l << ' ' << r << endl;

        curans += segs[xc].query_zero(l, r);
        segs[xc].add(l, r);

        x = (*cpa)[xc];
      }
      // cerr << "curans = " << curans << endl;
    }

    void remove(int x) {
      // cerr << "Maint " << d << ": " << " remove " << x << endl;
      int dd = d;
      while (x && dd) {
        int xc = (*cn)[x];
        int xcp = (*icpos)[x];
        
        int dolen = min(dd, xcp);
        int r = xcp;
        int l = r - dolen + 1;
        dd -= dolen;

        // cerr << "do on chain " << xc << " l r " << l << ' ' << r << endl;

        curans -= segs[xc].query_one(l, r);
        segs[xc].remove(l, r);

        x = (*cpa)[xc];
      }
      // cerr << "curans = " << curans << endl;
    }

    int getcur() { return curans; }
  };

  vector<int> isleaf(n + 3, 0);

  Maint mo(ccc, O + 1, cn, icpos, cpa, clen), mf(ccc, F + 1, cn, icpos, cpa, clen);
  mo.add(1);
  mf.add(1);
  isleaf[1] = 1;

  for (auto [c, pa, x] : qs) {
    if (c == 1) {
      if (isleaf[pa]) {
        mo.remove(pa);
        mf.remove(pa);
        isleaf[pa] = 0;
      }
      mo.add(x);
      mf.add(x);
      isleaf[x] = 1;
    } else if (c == 2) {
      // cerr << "mo = " << mo.getcur() << endl;
      // cerr << "mf = " << mf.getcur() << endl;
      cout << fixed << setprecision(12) << (double)mo.getcur() / mf.getcur() << '\n';
    }
  }
}
