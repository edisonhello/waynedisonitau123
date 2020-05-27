#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);

struct node {
  node *l, *r;
  vector<int> op;
} *root;

int r, R;

double Dist(double o) {
  double rt = -1;
  if (cos(o / 2) >= (double)r / R) rt = 2 * R * sin(o / 2);
  else rt = 2 * sqrt((double)R * R - (double)r * r) + (o - 2 * acos((double)r / R)) * r;
  // cerr << "       Dist " << o << " = " << rt << endl;
  return rt;
}

#define mid ((l + r) >> 1)
void Dfs(node *now, int l, int r, double mx, set<int> &st) {
  // cerr << "Dfs at " << l << " " << r << endl;

  double newmx = mx;

  auto AddDist = [&] (int x, int y) {
    // cerr << "     AddDist x y " << x << ' ' << y << endl;
    int d = (y - x + 360000) % 360000;
    int e = (x - y + 360000) % 360000;
    newmx = max(newmx, Dist((double)min(d, e) / (360000) * (2 * pi)));
  };
  auto Add = [&] (int x) {
    // cerr << "   Add " << x << endl;
    int y = (x + 180000) % 360000;
    auto it = st.lower_bound(y);
    if (it == st.end()) {
      if (st.size()) AddDist(x, *st.begin());
    } else AddDist(x, *it);
    if (it == st.begin()) {
      if (st.size()) AddDist(x, *prev(st.end()));
    } else AddDist(x, *prev(it));
    st.insert(x);
  };

  for (int i : now->op) Add(i);

  if (l == r) {
    cout << fixed << setprecision(12) << newmx << '\n';
  } else {
    Dfs(now->l, l, mid, newmx, st);
    Dfs(now->r, mid + 1, r, newmx, st);
  }

  for (int i : now->op) st.erase(i);
}

void Build(node *now, int l, int r) {
  if (l == r) return;
  Build(now->l = new node(), l, mid);
  Build(now->r = new node(), mid + 1, r);
}

void Modify(node *now, int l, int r, int ml, int mr, int x) {
  if (now == root) {
    // cerr << "Modify " << ml << ' ' << mr << " with x = " << x << endl;
  }
  if (r < ml || mr < l) return;
  if (ml <= l && r <= mr) {
    now->op.push_back(x);
    return;
  }
  Modify(now->l, l, mid, ml, mr, x);
  Modify(now->r, mid + 1, r, ml, mr, x);
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  cin >> R >> r;
  int n; cin >> n;
  map<int, int> life;
  while (n--) {
    int t; cin >> t;
    life[t] = 0;
  }
  int q; cin >> q;
  Build(root = new node(), 0, q);
  for (int i = 1; i <= q; ++i) {
    int c, v; cin >> c >> v;
    if (c == 1) {
      life[v] = i;
    } else {
      Modify(root, 0, q, life[v], i - 1, v);
      life.erase(v);
    }
  }
  for (auto &p : life) Modify(root, 0, q, p.second, q, p.first);

  set<int> cur;
  Dfs(root, 0, q, 0, cur);
}
