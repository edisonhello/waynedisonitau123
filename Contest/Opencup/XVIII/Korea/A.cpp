#include <bits/stdc++.h>
using namespace std;

struct node {
  node *l, *r;
  long long tag, mx;
  node() : l(0), r(0), mx(0), tag(0) {}
  void addtag(long long v) {
    tag += v;
    mx += v;
  }
  void pull() {
    mx = max(l->mx, r->mx);
  }
  void push() {
    if (tag) {
      l->addtag(tag);
      r->addtag(tag);
      tag = 0;
    }
  }
} *root;

#define mid ((l + r) >> 1)
void Build(node *now, int l, int r) {
  if (l == r) {
    return;
  }
  Build(now->l = new node(), l, mid);
  Build(now->r = new node(), mid + 1, r);
  now->pull();
}

void Modify(node *now, int l, int r, int ml, int mr, int v) {
  if (r < ml || mr < l) return;
  if (ml <= l && r <= mr) {
    now->addtag(v);
    return;
  }
  now->push();
  Modify(now->l, l, mid, ml, mr, v);
  Modify(now->r, mid + 1, r, ml, mr, v);
  now->pull();
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n, l, r; cin >> n >> l >> r;
  map<int, vector<tuple<int, int, int>>> ev;
  vector<tuple<int, int, int>> pts;
  vector<int> ally;

  while (n--) {
    int x, y, w; cin >> x >> y >> w;
    pts.emplace_back(x, y, w);
    for (int z = -2; z <= 2; ++z) ally.push_back(y - l + z);
    for (int z = -2; z <= 2; ++z) ally.push_back(y - r + z);
    for (int z = -2; z <= 2; ++z) ally.push_back(y + l + z);
    for (int z = -2; z <= 2; ++z) ally.push_back(y + r + z);
  }

  sort(ally.begin(), ally.end());
  ally.resize(unique(ally.begin(), ally.end()) - ally.begin());

  for (auto &t : pts) {
    int x, y, w; tie(x, y, w) = t;

    auto Get = [&] (int y) { return upper_bound(ally.begin(), ally.end(), y) - ally.begin(); };

    ev[x - r].emplace_back(Get(y - r), Get(y + r), w);
    ev[x + r + 1].emplace_back(Get(y - r), Get(y + r), -w);
    ev[x - l + 1].emplace_back(Get(y - l + 1), Get(y + l - 1), -w);
    ev[x + l].emplace_back(Get(y - l + 1), Get(y + l - 1), w);
  }

  Build(root = new node(), 1, ally.size());
  long long mx = LLONG_MIN;
  for (auto &mpp : ev) {
    // cerr << "time " << mpp.first << endl;
    for (auto &t : mpp.second) {
      Modify(root, 1, ally.size(), get<0>(t), get<1>(t), get<2>(t));
      // cerr << "  add event " << get<0>(t) << ' ' << get<1>(t) << ' ' << get<2>(t) << endl;
    }
    mx = max(mx, root->mx);
    // cerr << "  val " << root->mx << endl;
  }

  cout << mx << endl;

}
