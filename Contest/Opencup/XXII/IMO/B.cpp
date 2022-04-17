#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;

int n, k, w;
int iw;

int pw(int b, int n) {
  int a = 1;
  while (n) {
    if (n & 1) a = 1ll * a * b % mod;
    b = 1ll * b * b % mod;
    n >>= 1;
  }
  return a;
}

int presum[7][100005];

int getpw(int x, int w) {
  if (w == 0) return 1;
  if (x == 0) return 0;
  int z = presum[w][x] - presum[w][x - 1] + mod;
  return z >= mod ? z - mod : z;
}

void init() {
  for (int z = 1; z <= 5; ++z) {
    for (int i = 1; i <= 100000; ++i) {
      presum[z][i] = (presum[z][i - 1] + pw(i, z)) % mod;
    }
  }
}

struct node {
  node *l, *r;
  int pri, sz, val, sum[7];
  int cnt[5][5];

  node() : pri(rand()), sz(1) {}

  void set(int v) {
    cnt[val % w][1 % w] = 0;
    val = v;
    for (int i = 0; i <= 5; ++i) sum[i] = v;
    cnt[v % w][1 % w] = 1;
  }

  int lsz() { return l ? l->sz : 0; }
  int rsz() { return r ? r->sz : 0; }
  int lsum(int p) { return l ? l->sum[p] : 0; }
  int rsum(int p) { return r ? r->sum[p] : 0; }
  int lcnt(int x, int y) { return l ? l->cnt[x][y] : 0; }
  int rcnt(int x, int y) { return r ? r->cnt[x][y] : 0; }
  void pull() {
    sz = lsz() + rsz() + 1;

    int mx = lsz() + 1;
    sum[0] = (0ll + lsum(0) + rsum(0) + val) % mod;
    sum[1] =
        (lsum(1) + 1ll * val * getpw(mx, 1) + rsum(1) + 1ll * mx * rsum(0)) %
        mod;
    sum[2] = (lsum(2) + 1ll * val * getpw(mx, 2) + rsum(2) +
              2ll * rsum(1) * getpw(mx, 1) % mod +
              1ll * rsum(0) * getpw(mx, 2) % mod) %
             mod;
    sum[3] = (lsum(3) + 1ll * val * getpw(mx, 3) + rsum(3) +
              3ll * rsum(2) * getpw(mx, 1) % mod +
              3ll * rsum(1) * getpw(mx, 2) % mod +
              1ll * rsum(0) * getpw(mx, 3) % mod) %
             mod;
    sum[4] = (lsum(4) + 1ll * val * getpw(mx, 4) + rsum(4) +
              4ll * rsum(3) * getpw(mx, 1) % mod +
              6ll * rsum(2) * getpw(mx, 2) % mod +
              4ll * rsum(1) * getpw(mx, 3) % mod +
              1ll * rsum(0) * getpw(mx, 4) % mod) %
             mod;
    sum[5] = (lsum(5) + 1ll * val * getpw(mx, 5) + rsum(5) +
              5ll * rsum(4) * getpw(mx, 1) % mod +
              10ll * rsum(3) % mod * getpw(mx, 2) % mod +
              10ll * rsum(2) % mod * getpw(mx, 3) % mod +
              5ll * rsum(1) * getpw(mx, 4) % mod +
              1ll * rsum(0) * getpw(mx, 5) % mod) %
             mod;

    for (int bi = 0; bi < w; ++bi) {
      for (int i = 0; i < w; ++i) {
        cnt[bi][i] = lcnt(bi, i) + rcnt(bi, ((i - mx) % w + w) % w);
      }
    }
    cnt[val % w][mx % w] += 1; // this
  }

  int get_ans() {
    int diff = 0;
    for (int bi = 0; bi < w; ++bi) {
      for (int i = 0; i < w; ++i) {
        diff += (1ll * bi * getpw(i, k) % w) * cnt[bi][i] % mod;
        diff %= mod;
      }
    }
    return (sum[k] - diff + mod) * 1ll * iw % mod;
  }

  void print() {
    if (l) cout << "[", l->print(), cout << "]";
    cout << "val " << val << " sums " << sum[0] << ' ' << sum[1] << ' ' << sum[2];
    if (r) cout << "[", r->print(), cout << "]";
  }
} * root, pool[100005];

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

void split_sz(node *now, int lsz, node *&l, node *&r) {
  if (!now) {
    l = r = 0;
    return;
  }
  if (now->lsz() >= lsz) {
    r = now;
    split_sz(now->l, lsz, l, r->l);
  } else {
    l = now;
    split_sz(now->r, lsz - 1 - now->lsz(), l->r, r);
  }
  now->pull();
}

void split_val(node *now, int val, node *&l, node *&r) {
  if (!now) {
    l = r = 0;
    return;
  }
  if (now->val <= val) {
    l = now;
    split_val(now->r, val, l->r, r);
  } else {
    r = now;
    split_val(now->l, val, l, r->l);
  }
  now->pull();
}

int a[100005];

int main() {
  init();

  ios_base::sync_with_stdio(0);
  cin.tie(0);

  cin >> n >> k >> w;

  iw = pw(w, mod - 2);

  vector<int> arr(n);
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
  }

  auto b = arr;
  sort(b.begin(), b.end());
  for (int i = 0; i < n; ++i) {
    pool[i].set(b[i]);
    root = merge(root, &pool[i]);
  }

  int q;
  cin >> q;
  while (q--) {
    int pos, x;
    cin >> pos >> x;
    --pos;

    int oval = arr[pos];

    node *a, *b, *c, *d;
    split_val(root, oval - 1, a, d);
    split_sz(d, 1, b, c);
    root = merge(a, c);
    b->set(x);
    arr[pos] = x;
    split_val(root, x - 1, a, c);
    root = merge(merge(a, b), c);

    // root->print();
    // cout << endl;

    cout << root->get_ans() << '\n';
  }
}
