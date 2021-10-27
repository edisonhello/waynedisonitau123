#include <bits/stdc++.h>
using namespace std;
#define ll int64_t

ll lenans(ll v) {
  return v * (v + 1) / 2;
}

int a[200005];

struct Data {
  ll ans;
  int tag;
  int len, lest, llen, rest, rlen;

  Data() : ans(0), tag(0), len(0), lest(0), llen(0), rest(0), rlen(0) {}

  void addtag() {
    tag ^= 1;
    lest ^= 1;
    rest ^= 1;
  }

  void set(int v) {
    len = 1;
    ans = 1;
    lest = rest = v;
    llen = rlen = 1;
  }

  Data merge(Data b) const {
    Data d;
    d.ans = ans + b.ans;
    d.len = len + b.len;
    d.lest = lest;
    d.rest = b.rest;
    
    if (rest != b.lest) {
      d.ans -= lenans(rlen);
      d.ans -= lenans(b.llen);
      d.ans += lenans(rlen + b.llen);
      d.llen = (llen == len ? len + b.llen : llen);
      d.rlen = (b.rlen == b.len ? b.len + rlen : b.rlen);
    } else {
      d.llen = llen;
      d.rlen = b.rlen;
    }

    return d;
  }
} seg[200005 * 4];

void push(int o) {
  if (seg[o].tag) {
    seg[o * 2 + 1].addtag();
    seg[o * 2 + 2].addtag();
    seg[o].tag = 0;
  }
}

#define mid ((l + r) >> 1)
void build(int o, int l, int r) {
  if (l == r) {
    seg[o].set(a[l]);
    return;
  }
  build(o * 2 + 1, l, mid);
  build(o * 2 + 2, mid + 1, r);
  seg[o] = seg[o * 2 + 1].merge(seg[o * 2 + 2]);
}

void modify(int o, int l, int r, int ml, int mr) {
  if (mr < l || r < ml) return;
  if (ml <= l && r <= mr) {
    seg[o].addtag();
    return;
  }
  push(o);
  modify(o * 2 + 1, l, mid, ml, mr);
  modify(o * 2 + 2, mid + 1, r, ml, mr);
  seg[o] = seg[o * 2 + 1].merge(seg[o * 2 + 2]);
}

Data query(int o, int l, int r, int ql, int qr) {
  if (ql <= l && r <= qr) return seg[o];
  push(o);
  if (qr <= mid) return query(o * 2 + 1, l, mid, ql, qr);
  if (mid + 1 <= ql) return query(o * 2 + 2, mid + 1, r, ql, qr);
  Data dl = query(o * 2 + 1, l, mid, ql, qr);
  Data dr = query(o * 2 + 2, mid + 1, r, ql, qr);
  return dl.merge(dr);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, q; 
  cin >> n >> q;
  for (int i = 1; i <= n; ++i) cin >> a[i];

  build(0, 1, n);

  for (int i = 0; i < q; ++i) {
    int c, l, r;
    cin >> c >> l >> r;
    if (c == 1) modify(0, 1, n, l, r);
    else {
      Data res = query(0, 1, n, l, r);
      cout << res.ans << '\n';
    }
  }
}
