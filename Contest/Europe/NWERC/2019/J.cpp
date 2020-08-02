#include <bits/stdc++.h>
using namespace std;

struct Item {
  int l, r, pl, pr;

  bool operator<(const Item &item) const { return l < item.l; }
};

int main() {
  int n, c, r;
  cin >> n >> c >> r;
  vector<int> s(n);
  for (int i = 0; i < n; ++i) cin >> s[i];
  if (count(s.begin(), s.end(), 0) == n) {
    cout << min(1LL * c, 1LL * n * r) << "\n";
    return 0;
  }

  auto Solve = [&](vector<int> s, int base) -> int64_t {
    if (s.empty()) return 0;
    int n = s.size();
    vector<pair<int, int>> ev;
    for (int i = 0; i < n; ++i) {
      if (s[i] == 0) continue;
      int need = s[i] < 0 ? 1 - s[i] : 1 + s[i];
      ev.emplace_back(need, i);
    }
    sort(ev.begin(), ev.end(), greater<pair<int, int>>());
    set<Item> g;
    vector<bool> used(n);

    auto Sign = [&](int v) {
      assert(v != 0);
      return v > 0 ? 1 : -1;
    };

    int cost = 0;

    auto Cost = [&](int x, int y, int z) {
      return (x == y) != (z % 2);
    };

    auto Insert = [&](int p) {
      Item x{p, p, Sign(s[p]), Sign(s[p])};
      auto it = g.lower_bound(x);
      if (it != begin(g) && it != end(g)) {
        int gap = it->l - prev(it)->r - 1;
        cost -= Cost(prev(it)->pr, it->pl, gap);
      }
      if (it == begin(g) && it == end(g)) {
        g.insert(x);
      } else if (it != begin(g) && it == end(g)) {
        if (prev(it)->r + 1 == p) {
          cost += prev(it)->pr == x.pl;
          Item i = *prev(it);
          g.erase(i);
          i.r++;
          i.pr = x.pl;
          g.insert(i);
        } else {
          int gap = p - prev(it)->r - 1;
          cost += Cost(prev(it)->pr, x.pl, gap);
          g.insert(x);
        }
      } else if (it == begin(g) && it != end(g)) {
        if (it->l - 1 == p) {
          cost += it->pl == x.pl;
          Item i = *it;
          g.erase(i);
          i.l--;
          i.pl = x.pl;
          g.insert(i);
        } else {
          int gap = it->l - p - 1;
          cost += Cost(x.pl, it->pl, gap);
          g.insert(x);
        }
      } else {
        Item i = *prev(it), j = *it;
        if (i.r + 1 == p && j.l - 1 == p) {
          cost += i.pr == x.pl;
          cost += x.pl == j.pl;
          g.erase(i);
          g.erase(j);
          i.pr = j.pr;
          i.r = j.r;
          g.insert(i);
        } else if (i.r + 1 == p) {
          cost += i.pr == x.pl;
          g.erase(i);
          i.r++;
          i.pr = x.pl;
          int gap = j.l - i.r - 1;
          cost += Cost(i.pr, j.pl, gap);
          g.insert(i);
        } else if (j.l - 1 == p) {
          cost += j.pl == x.pl;
          g.erase(j);
          j.l--;
          j.pl = x.pl;
          int gap = j.l - i.r - 1;
          cost += Cost(i.pr, j.pl, gap);
          g.insert(j);
        } else {
          int gl = p - i.r - 1;
          int gr = j.l - p - 1;
          cost += Cost(i.pr, x.pl, gl);
          cost += Cost(x.pl, j.pl, gr);
          g.insert(x);
        }
      }
    };

    int64_t res = 1LL * n * r;

    for (int i = 0, j = 0; i < ev.size(); i = j) {
      while (j < ev.size() && ev[i].first == ev[j].first) {
        Insert(ev[j++].second);
      }
      int nxt = j < ev.size() ? ev[j].first : base;
      res = min(res, 1LL * nxt * c + 1LL * cost * r);
    }
    return res;
  };

  int64_t res = Solve(s, 1);
  vector<int> ps;
  int cnt = count(s.begin(), s.end(), 0);
  for (int i = 0; i < n; ++i) {
    if (s[i] != 0) ps.push_back(s[i]);
  }
  res = min(res, Solve(ps, 0) + 1LL * cnt * r);

  cout << res << "\n";
}
