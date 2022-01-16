#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second

#define crx(a, b, c) (cross((b - a), (c - a)))

pair<int, int> operator-(const pair<int, int> &a, const pair<int, int> &b) {
  return pair{a.first - b.first, a.second - b.second};
}

int64_t cross(pair<int, int> a, pair<int, int> b) {
  return a.first * 1ll * b.second - a.second * 1ll * b.first;
}

double get_len(pair<int, int> a) {
  return hypot((double)a.first, (double)a.second);
}

ostream& operator<<(ostream &o, tuple<double, int, int> &t) {
  return o << "(" << get<1>(t) << ", " << get<2>(t) << ")";
}

pair<int, int> simp(tuple<double, int, int> t) {
  return pair{get<1>(t), get<2>(t)};
}

class TB {
 public:
  deque<int> bads;
  deque<pair<int, int>> pt;
  int bad;
  double len_sum;

  TB() : bad(0), len_sum(0) {}

  int ok() { return bad == 0 && pt.size() >= 2u; }

  int push_back(tuple<double, int, int> t) {
    return push_back(pair{get<1>(t), get<2>(t)});
  }

  int push_back(pair<int, int> p) {
    if (pt.size()) {
      len_sum += get_len(pt.back() - p);
    }
    pt.push_back(p);
    bads.push_back(0);

    if (pt.size() >= 3u)
      check_ok(pt.size() - 2);

    int popped = 0;
    while (pt.size() >= 2u && cross(pt.back(), pt[0]) >= 0) {
      pop_front();
      ++popped;
    }

    return popped;
  }

  void pop_front() {
    if (pt.size() >= 2) {
      len_sum -= get_len(pt[0] - pt[1]);
    }
    assert(bads[0] == 0);
    bads.pop_front();
    pt.pop_front();

    check_ok(0);
  }

  void check_ok(int idx) {
    if (pt.empty()) return;
    if (idx == 0 || idx == (int)pt.size() - 1) {
      if (bads[idx]) {
        bads[idx] = 0;
        --bad;
      }
      return;
    }

    if (cross(pt[idx - 1] - pt[idx], pt[idx + 1] - pt[idx]) >= 0) {
      if (!bads[idx]) {
        bads[idx] = 1;
        ++bad;
      }
    }
  }

  double get_ans() {
    // // cerr << "pt[0] back len " << get_len(pt[0]) << ' ' << get_len(pt.back()) << ' ' << len_sum << endl;
    return get_len(pt[0]) + get_len(pt.back()) + len_sum;
  }
};

int comp_first(tuple<double, int, int> d, tuple<double, int, int> u) {
  auto [_, dx, dy] = d;
  auto [__, ux, uy] = u;
  dx = -dx;
  dy = -dy;
  if (cross(pair{dx, dy}, pair{ux, uy}) >= 0) return 0;
  return 1;
}

auto get_conv(auto &ps) {
  sort(ps.begin(), ps.end());

  vector<pair<int, int>> p;
  for (int i = 0; i < (int)ps.size(); ++i) {
    while (p.size() >= 2 && crx(p[p.size() - 2], ps[i], p[p.size() - 1]) > 0) p.pop_back();
    p.push_back(ps[i]);
  }
  int t = p.size();
  for (int i = (int)ps.size() - 2; i >= 0; --i) {
    while ((int)p.size() > t && crx(p[p.size() - 2], ps[i], p[p.size() - 1]) > 0) p.pop_back();
    p.push_back(ps[i]);
  }
  p.pop_back();
  return p;
}

int same_line(pair<int, int> a, pair<int, int> b, pair<int, int> c) {
  auto [ax, ay] = a - b;
  auto [bx, by] = b - c;
  return 1ll * ax * by == 1ll * bx * ay;
}

int has_same_line(auto &ps) {
  int n = ps.size();
  for (int i = 0; i < n; ++i) {
    int p = (i - 1 + n) % n;
    int x = (i + 1) % n;

    if (same_line(ps[p], ps[i], ps[x])) return 1;
  }
  return 0;
}

double solveoo(vector<tuple<double, int, int>> opt) {
  vector<pair<int, int>> pt;
  for (auto [o, x, y] : opt) pt.emplace_back(x, y);
  pt.emplace_back(0, 0);

  // for (auto p : pt) cerr << "all pt " << p.X << " " << p.Y << endl;
  auto conv = get_conv(pt);
  // for (auto p : conv) cerr << "conv pt " << p.X << " " << p.Y << endl;
  bool zero_in = 0;
  for (auto p : conv) {
    if (p.X == 0 && p.Y == 0) zero_in = 1;
  }

  // cout << "another zero in " << zero_in << endl;
  if (!zero_in) return 0;
  set<pair<int, int>> st(conv.begin(), conv.end());

  vector<pair<int, int>> others;
  for (auto &p : pt) {
    if (st.count(p));
    else others.push_back(p);
  }
  others.emplace_back(0, 0);

  auto conv2 = get_conv(others);
  if (conv2.size() != others.size()) return 0;
  if (conv.size() < 3u) return 0;
  if (conv2.size() < 3u) return 0;
  if (has_same_line(conv)) return 0;
  if (has_same_line(conv2)) return 0;

  double ans = 0;
  for (int i = 0; i < (int)conv.size(); ++i) {
    int j = (i + 1) % conv.size();
    ans += get_len(conv[i] - conv[j]);
  }

  for (int i = 0; i < (int)conv2.size(); ++i) {
    int j = (i + 1) % conv2.size();
    ans += get_len(conv2[i] - conv2[j]);
  }

  return ans;
}

double solve2(vector<tuple<double, int, int>> pt) {
  int n = pt.size();

  sort(pt.begin(), pt.end());

  for (int i = 0; i < n; ++i) {
    int j = (i + 1) % n;
    int g1 = abs(__gcd(get<1>(pt[i]), get<2>(pt[i])));
    int g2 = abs(__gcd(get<1>(pt[j]), get<2>(pt[j])));

    int dx1 = get<1>(pt[i]) / g1;
    int dy1 = get<2>(pt[i]) / g1;
    int dx2 = get<1>(pt[j]) / g2;
    int dy2 = get<2>(pt[j]) / g2;

    if (dx1 == dx2 && dy1 == dy2) {
      return 0;
    }
  }

  TB d, u;
  int d_last = n - 1, u_last = 0;
  for (int i = 0; i < n; ++i) {
    auto [o, x, y] = pt[i];
    if (i == 0 || cross(simp(pt[0]), simp(pt[i])) > 0) {
      assert(d.push_back(pair{x, y}) == 0);
      d_last = i;
    }
    else assert(u.push_back(pair{x, y}) == 0);
  }
  u_last = n - 1;

  // cout << "dlast ulast " << d_last << ' ' << u_last << endl;

  double mx = 0;
  // while (u_last != o_d_last || d_last != o_u_last) {
  for (int z = 0; z < n; ++z) {
    int d_next = (d_last + 1) % n;
    int u_next = (u_last + 1) % n;
    // 0 => d, 1 => u
    int source = -1;
    if (d.pt.empty()) source = 0;
    else if (u.pt.empty()) source = 1;
    else if (cross(simp(pt[d_last]), simp(pt[d_next])) <= 0) source = 1;
    else if (cross(simp(pt[u_last]), simp(pt[u_next])) <= 0) source = 0;
    else source = comp_first(pt[d_next], pt[u_next]);
    // cout << "next " << pt[d_next] << " and " << pt[u_next] << " choose source " << source << endl;
    // cout << "now d u size " << d.pt.size() << ' ' << u.pt.size() << endl;
    if (source == 0) {
      u.pop_front();
      int popped = d.push_back(pt[d_next]);
      d_last = (d_last + 1) % n;
      assert(popped <= 1);
      for (int i = 0; i < popped; ++i) {
        assert(u.push_back(pt[u_next]) == 0);
        u_last = u_next;
        u_next = (u_next + 1) % n;
      }
    } else {
      d.pop_front();
      int popped = u.push_back(pt[u_next]);
      u_last = (u_last + 1) % n;
      assert(popped <= 1);
      for (int i = 0; i < popped; ++i) {
        assert(d.push_back(pt[d_next]) == 0);
        d_last = d_next;
        d_next = (d_next + 1) % n;
      }
    }

    if (u.ok() && d.ok()) {
      // cout << "ok! " << "u d ans " << u.get_ans() << " " << d.get_ans() << endl;
      mx = max(mx, u.get_ans() + d.get_ans());
    }
  }

  return mx;
}

void solve() {
  int n; cin >> n;
  vector<tuple<double, int, int>> pt;

  for (int i = 0; i < n; ++i) {
    int x, y; cin >> x >> y;
    double o = atan2((double)y, (double)x);
    pt.emplace_back(o, x, y);
  }

  cout << fixed << setprecision(12) << max(solve2(pt), solveoo(pt)) << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t; cin >> t; while (t--) solve();
}

