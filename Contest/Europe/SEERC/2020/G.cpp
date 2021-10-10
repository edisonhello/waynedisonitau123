#include <bits/stdc++.h>
using namespace std;

int sign(int x) {
  return x > 0 ? 1 : -1;
}


struct node {
  node *l, *r;
  int mn, mncnt, tag, len;
  node(): l(0), r(0), mn (0), mncnt(1), tag(0), len(1) {}
  void addtag(int v) {
    tag += v;
    mn += v;
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
    if (l->mn == r->mn) mncnt = l->mncnt + r->mncnt;
    else if (l->mn < r->mn) mncnt = l->mncnt;
    else mncnt = r->mncnt;
    len = l->len + r->len;
  }
} *root;


#define mid ((l + r) >> 1)
void build(node *now, int l, int r) {
  if (l == r) {
    return;
  }
  build(now->l = new node(), l, mid);
  build(now->r = new node(), mid + 1, r);
  now->pull();
}

void add(node *now, int l, int r, int ml, int mr) {
  if (r < ml || mr < l) return;
  if (ml <= l && r <= mr) {
    now->addtag(1);
    return;
  }
  now->push();
  add(now->l, l, mid, ml, mr);
  add(now->r, mid + 1, r, ml, mr);
  now->pull();
}

void remove(node *now, int l, int r, int ml, int mr) {
  if (r < ml || mr < l) return;
  if (ml <= l && r <= mr) {
    now->addtag(-1);
    return;
  }
  now->push();
  remove(now->l, l, mid, ml, mr);
  remove(now->r, mid + 1, r, ml, mr);
  now->pull();
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;

  vector<pair<int, int>> ps(n);
  for (int i = 0; i < n; ++i) {
    cin >> ps[i].first >> ps[i].second;
  }

  vector<tuple<int, int, int>> re;

  for (int i = 0; i < n; ++i) {
    int j = (i + 1) % n;
    if (ps[i].first == ps[j].first) {
      re.emplace_back(ps[i].first, ps[i].second, ps[j].second);
    }
  }

  sort(re.begin(), re.end());
  int pos_dir = sign(get<2>(re[0]) - get<1>(re[0]));

  vector<tuple<int, int, int, int>> events;
  for (auto [x, y1, y2] : re) {
    if (sign(y2 - y1) == pos_dir) events.emplace_back(x, 1, min(y1, y2), max(y1, y2));
    else events.emplace_back(x, -1, min(y1, y2), max(y1, y2));
  }

  build(root = new node(), 1, 1000000);
  long long ans = 0;
  int ptot = 0, px = -1;
  for (auto [x, t, y1, y2] : events) {
    cerr << "ev " << x << ' ' << t << ' ' << y1 << ' ' << y2 << endl;
    ans += (x - px) * 1ll * ptot;
    if (t == 1) add(root, 1, 1000000, y1, y2);
    else remove(root, 1, 1000000, y1, y2);
    px = x;
    ptot = root->mn == 0 ? root->len - root->mncnt : root->len;
  }

  cout << ans << endl;
}
