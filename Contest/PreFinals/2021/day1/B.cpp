#include <bits/stdc++.h>
using namespace std;

int ans[555];
int L, n;
int bx, by;

set<pair<int, int>> nopoint;

map<pair<int, int>, vector<pair<double, int>>> points;

void add_point(int x, int y, int z) {
  int dx = x - bx;
  int dy = y - by;
  double d = hypot((double)dx, (double)dy);

  int g = abs(__gcd(dx, dy));
  dx /= g;
  dy /= g;
  auto o = make_pair(dx, dy);

  points[o].emplace_back(d, z);
}

void add_square(int x1, int y1, int x2, int y2) {
  nopoint.insert(make_pair(x1, y1));
  nopoint.insert(make_pair(x1, y2));
  nopoint.insert(make_pair(x2, y1));
  nopoint.insert(make_pair(x2, y2));
}

void go_up(int x1, int y1, int x2, int y2, int x, int y, int z) {
  if (z > n) return;
  y = y2 * 2 - y; ++z;
  y1 += 2 * L;
  y2 += 2 * L;
  add_point(x, y, z);
  add_square(x1, y1, x2, y2);
  go_up(x1, y1, x2, y2, x, y, z);
}

void go_down(int x1, int y1, int x2, int y2, int x, int y, int z) {
  if (z > n) return;
  y = y1 * 2 - y; ++z;
  y1 -= 2 * L;
  y2 -= 2 * L;
  add_point(x, y, z);
  add_square(x1, y1, x2, y2);
  go_down(x1, y1, x2, y2, x, y, z);
}

void go_right(int x1, int y1, int x2, int y2, int x, int y, int z) {
  if (z > n) return;
  x = x2 * 2 - x; ++z;
  x1 += 2 * L;
  x2 += 2 * L;
  add_point(x, y, z);
  add_square(x1, y1, x2, y2);
  go_right(x1, y1, x2, y2, x, y, z);
  go_up(x1, y1, x2, y2, x, y, z);
  go_down(x1, y1, x2, y2, x, y, z);
}

void go_left(int x1, int y1, int x2, int y2, int x, int y, int z) {
  if (z > n) return;
  x = x1 * 2 - x; ++z;
  x1 -= 2 * L;
  x2 -= 2 * L;
  add_point(x, y, z);
  add_square(x1, y1, x2, y2);
  go_left(x1, y1, x2, y2, x, y, z);
  go_up(x1, y1, x2, y2, x, y, z);
  go_down(x1, y1, x2, y2, x, y, z);
}

int main() {
  cin >> L >> n;
  int x, y; cin >> bx >> by >> x >> y;

  add_point(x, y, 0);
  add_square(-L, -L, L, L);

  go_up(-L, -L, L, L, x, y, 0);
  go_down(-L, -L, L, L, x, y, 0);

  go_right(-L, -L, L, L, x, y, 0);
  go_left(-L, -L, L, L, x, y, 0);

  for (auto [x, y] : nopoint) {
    add_point(x, y, -1);
  }

  for (auto &[o, v] : points) {
    auto p = *min_element(v.begin(), v.end());
    if (p.second >= 0) ++ans[p.second];
  }

  for (int i = 0; i <= n; ++i) cout << ans[i] << ' ';
  cout << endl;
}
