#include <bits/stdc++.h>
using namespace std;

int sign(int x) {
  return x == 0 ? 0 : x > 0 ? 1 : -1;
}

struct node {
  node *l, *r;
  int tag;
  int mn;
  node() : l(0), r(0), tag(0), mn(0) {}
  void push() {
    if (tag) {
      l->addtag(tag);
      r->addtag(tag);
      tag = 0;
    }
  }
  void pull() {
    mn = min(l->mn, r->mn);
  }
  void addtag(int v) {
    tag += v;
    mn += v;
  }
};

struct Seg {
  node *root;
  int len;
  Seg() : root(0), len(0) {}
#define mid ((l + r) >> 1)
  void build(node *now, int l, int r) {
    if (l == r) return;
    build(now->l = new node(), l, mid);
    build(now->r = new node(), mid + 1, r);
  }
  void init(int _len) {
    len = _len;
    build(root = new node(), 0, len - 1);
  }
  void modify(node *now, int l, int r, int ml, int mr, int v) {
    if (r < ml || mr < l) return;
    if (ml <= l && r <= mr) {
      now->addtag(v);
      return;
    }
    now->push();
    modify(now->l, l, mid, ml, mr, v);
    modify(now->r, mid + 1, r, ml, mr, v);
    now->pull();
  }
  void add(int x, int v) {
    // cerr << "add x v root " << x << ' ' << v << endl;
    modify(root, 0, len - 1, x, len - 1, v);
  }
  int is_good() {
    return root->mn >= 0;
  }
#undef mid
};

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;

  vector<int> num;
  vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    string s; cin >> s;
    int x = 0;
    for (int j = 1; j < (int)s.size(); ++j) {
      x = x * 10 + (s[j] & 15);
    }

    if (s[0] == 's') {
      v[i] = x;
    } else {
      v[i] = -x;
    }

    num.push_back(x);
  }
  
  sort(num.begin(), num.end());
  num.resize(unique(num.begin(), num.end()) - num.begin());

  for (int &i : v) {
    int sgn = sign(i);
    i = abs(i);
    i = lower_bound(num.begin(), num.end(), i) - num.begin() + 1;
    i *= sgn;
    // cerr << "i = " << i << endl;
  }

  int nn = num.size();
  vector<int> len(nn + 1), atpos(n);
  vector<int> cl(nn + 1), cr(nn + 1);
  for (int i = 0; i < n; ++i) {
    atpos[i] = len[abs(v[i])];
    ++len[abs(v[i])];
    if (v[i] > 0) ++cl[v[i]];
    if (v[i] < 0) ++cr[-v[i]];
  }

  vector<Seg> segs(nn + 1);
  for (int i = 1; i <= nn; ++i) {
    // cerr << "go init seg " << i << endl;
    segs[i].init(len[i] * 2);
  }

  for (int i = 0; i < n; ++i) {
    // cerr << "segs id " << abs(v[i]) << endl;
    segs[abs(v[i])].add(atpos[i], sign(v[i]));
  }

  int is_good = 0;

  auto get_is_good = [&](int x) -> bool {
    // cerr << "get_is_good " << x << endl;
    bool ret = 0;
    if (cl[x] != cr[x]) ret = 0;
    else ret = segs[x].is_good();
    // cerr << "ret = " << ret << endl;
    return ret;
  };

  for (int i = 1; i <= nn; ++i) {
    if (get_is_good(i))
      ++is_good;
  }

  int cut = 0, mx = is_good;

  // cerr << "is_good init " << is_good << endl;

  for (int i = 1; i < n; ++i) {
    // cerr << "i = " << i << endl;
    is_good -= get_is_good(abs(v[i - 1]));
    segs[abs(v[i - 1])].add(atpos[i - 1], -sign(v[i - 1]));
    atpos[i - 1] += len[abs(v[i - 1])];
    segs[abs(v[i - 1])].add(atpos[i - 1], sign(v[i - 1]));
    is_good += get_is_good(abs(v[i - 1]));

    // cerr << "i = " << i << " is_good = " << is_good << endl;
    if (is_good > mx) {
      mx = is_good;
      cut = i;
    }
  }

  cout << cut + 1 << ' ' << mx << endl;


}

