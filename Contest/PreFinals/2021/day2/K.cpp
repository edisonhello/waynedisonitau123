#include <bits/stdc++.h>
using namespace std;
#define ll int64_t
#define sq(x) ((x) * (x))

struct Circle {
  int cen, r;
  bool empty() { return !r; }
  double get(int x) {
    return sqrt(sq((double)r) - sq((double)(cen - x)));
  }
};

struct node {
  node *l, *r;
  Circle c;
  node() : l(0), r(0), c(Circle{0, 0}) {}
} *rootl, *rootr;

vector<Circle> circ;
vector<int> qs, qxs;

#define mid ((l + r) >> 1)
void build(node *now, int l, int r) {
  if (l == r) return;
  build(now->l = new node(), l, mid);
  build(now->r = new node(), mid + 1, r);
}

void insert(node *now, int l, int r, int ml, int mr, Circle &c) {
  if (ml > mr) return;
  if (mr < l || r < ml) return;
  if (ml <= l && r <= mr) {
    if (now->c.empty()) {
      now->c = c;
      return;
    }
    int lx = qxs[l];
    int rx = qxs[r];
    double lv = c.get(lx), rv = c.get(rx);
    double olv = now->c.get(lx), orv = now->c.get(rx);
    bool lbet = lv >= olv, rbet = rv >= orv;
    if (lbet == rbet) {
      if (lbet) now->c = c;
      return;
    }
  }
  insert(now->l, l, mid, ml, mr, c);
  insert(now->r, mid + 1, r, ml, mr, c);
}

double query(node *now, int l, int r, int i) {
  double x = now->c.empty() ? (double)(0) : now->c.get(qxs[i]);
  if (l == r) return x;
  if (i <= mid) x = max(x, query(now->l, l, mid, i));
  else x = max(x, query(now->r, mid + 1, r, i));
  return x;
}

#undef mid

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);

  int n; cin >> n;
  for (int i = 0; i < n; ++i) {
    int x, r; cin >> x >> r;
    circ.push_back(Circle{x, r});
  }

  int q; cin >> q;

  for (int i = 0; i < q; ++i) {
    int x; cin >> x;
    qs.push_back(x);
    qxs.push_back(x);
  }

  sort(qxs.begin(), qxs.end());
  qxs.resize(unique(qxs.begin(), qxs.end()) - qxs.begin());

  int nn = qxs.size();

  build(rootl = new node(), 0, nn - 1);
  build(rootr = new node(), 0, nn - 1);

  auto find_l = [&] (int x) {
    return upper_bound(qxs.begin(), qxs.end(), x) - qxs.begin() - 1;
  };
  auto find_r = [&] (int x) {
    return lower_bound(qxs.begin(), qxs.end(), x) - qxs.begin();
  };

  for (int i = 0; i < n; ++i) {
    auto c = circ[i];
    insert(rootl, 0, nn - 1, find_r(c.cen - c.r), find_l(c.cen), c);
    insert(rootr, 0, nn - 1, find_r(c.cen), find_l(c.cen + c.r), c);
  }

  for (int x : qs) {
    int i = find_l(x);
    double ql = query(rootl, 0, nn - 1, i);
    double qr = query(rootr, 0, nn - 1, i);
    cout << fixed << setprecision(12) << max(ql, qr) << '\n';
  }
}
