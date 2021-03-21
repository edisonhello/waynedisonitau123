#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

struct node {
  node *l, *r;
  int sz, pri;
  long long a, mx;
  node() = default;
  node(int a) : l(0), r(0), a(a), sz(1), pri(rand()), mx(a - 1) {}

  long long  val() { return a - this->lz() - 1; }
  long long  lmx() { return l ? l->mx : INT_MIN; }
  long long  rmx() { return r ? r->mx : INT_MIN; }
  int lz() { return l ? l->sz : 0; }
  int rz() { return r ? r->sz : 0; }
  void pull() { 
    sz = 1 + lz() + rz();
    mx = max(val(), max(lmx(), rmx() - 1 - lz()));
  }
} pool[100005];
int pidx = 0;

node* merge(node *a, node *b) {
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

void split_a(node *now, long long  val, node *&a, node *&b) {
  if (!now) { a = b = 0; return; }
  if (now->a <= val) {
    a = now;
    split_a(now->r, val, a->r, b);
    a->pull();
  } else {
    b = now;
    split_a(now->l, val, a, b->l);
    b->pull();
  }
}

void insert_a(node *&root, long long  val) {
  // cerr << "insert_a " << val << endl;
  node *a, *b;
  split_a(root, val, a, b);
  // if (b) b->addtag(-1);

  // cerr << "ins " << val << " l r sz " << (a ? a->sz : 0) << ' ' << (b ? b->sz : 0) << endl;
  root = merge(merge(a, new (&pool[pidx++]) node(val)), b);
}

int try_insert_a(node *&root, long long  val, long long  bnd) {
  // cerr << "try inserting val " << val << " bnd " << bnd << endl;
  long long  omx = root ? root->mx : INT_MIN;
  int osz = root ? root->sz : 0;
  // cerr << "omx osz bnd " << omx << ' ' << osz << ' ' << bnd << endl;
  // if (omx + osz + 1 > bnd) return 0;

  node *a, *b;
  split_a(root, val, a, b);
  if (val - (a ? a->sz : 0) - 1 + osz + 1 > bnd) {
    // cerr << "fail 1 " << endl;
    root = merge(a, b);
    return 0;
  }

  // if (a) cerr << "a mx = " << a->mx << " a sz = " << a->sz << endl;
  if ((long long)(a ? a->mx : INT_MIN) + osz + 1 > bnd) {
    // cerr << "fail 2 " << endl;
    root = merge(a, b);
    return 0;
  }

  // cerr << "a b " << a << ' ' << b << endl;
  if ((long long)(b ? b->mx : INT_MIN) - (a ? a->sz : 0) - 2 + osz + 1 > bnd) {
    // cerr << "fail 3 " << endl;
    root = merge(a, b);
    return 0;
  }

  // if (b) b->addtag(-1);
  root = merge(merge(a, new (&pool[pidx++]) node(val)), b);
  return 1;
}

void printtreap(node *now) {
  if (!now) return;
  if (now->l) cerr << "[", printtreap(now->l), cerr << "]";
  cerr << "(" << now->a << ")";
  if (now->r) cerr << "[", printtreap(now->r), cerr << "]";
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n, l1, l2, l3, k; cin >> n >> l1 >> l2 >> l3 >> k;
  int64_t m = (long long)l1 + l2 + l3 + 2;

  vector<pair<int, int>> le, mi, ri;
  for (int i = 0; i < k; ++i) {
    int a, x, y; cin >> a >> x >> y;
    (a == 1 ? le : a == 2 ? mi : ri).emplace_back(x, y);
  }

  sort(mi.begin(), mi.end(), [&] (const auto x, const auto y) { return x.first != y.first ? x.first > y.first : x.second < y.second; });
  vector<bool> handled(mi.size());
  auto ok = [&] (long long  t_lim) -> bool {
    // cerr << "ok t_lim = " << t_lim << endl;
    pidx = 0;
    node *root = 0;
    for (auto [x, y] : le) {
      insert_a(root, l1 + 1 - y + x);
    }

    // cerr << "root mx " << root->mx << ' ' << root->sz << endl;
    // printtreap(root);
    // cerr << endl;
    if (root && root->mx + root->sz > t_lim) return false;

    fill(handled.begin(), handled.end(), false);

    for (int i = 0; i < (int)mi.size(); ++i) {
      auto [x, y] = mi[i];
      int res = try_insert_a(root, y - l1 - 1 + x, t_lim);
      // cerr << "i = " << i << " res " << res << endl;
      if (res) handled[i] = true;
    }

    node *root2 = 0;
    for (int i = 0; i < (int)mi.size(); ++i) {
      auto [x, y] = mi[i];
      if (handled[i]) continue;
      insert_a(root2, l1 + l2 + 2 - y + x);
    }

    for (auto [x, y] : ri) {
      insert_a(root2, y - (l1 + l2 + 2) + x);
    }

    // cerr << "roo2 mx sz " << root2->mx << ' ' << root2->sz << endl;
    if (root2 && root2->mx + root2->sz > t_lim) return false;

    return true;
  };

  // int r = ok(4);
  // cout << "ok(4) = " << r << endl;
  // exit(0);

  int64_t L = 0, R = 2010000005;
  while (L != R) {
    int64_t m = (L + R) >> 1;
    // cerr << "l r m " << L << ' ' << R << ' ' << m << endl;
    if (ok(m)) R = m;
    else L = m + 1;
  }

  cout << L << endl;
}

