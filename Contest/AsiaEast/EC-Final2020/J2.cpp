#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;
const double pi = acos(-1);

#define sq(x) ((x) * (x))

bool same(double a, double b) {
  return abs(a - b) < eps;
}

struct P {
  double x, y;

  P operator- (const P &b) const { return P{x - b.x, y - b.y}; }
  double abs() const { return hypot(x, y); }
  double angle() const { return atan2(y, x); }

};

struct C {
  P c;
  double r;
};

vector<pair<double, double>> CS(C &a, C &b) {
  double d = (a.c - b.c).abs();
  vector<pair<double, double>> res;
  if (same(a.r + b.r, d));
  else if (d <= abs(a.r - b.r) + eps) {
    if (a.r < b.r) res.emplace_back(0, 2 * pi);
  } else if (d < abs(a.r + b.r) - eps) {
    double o = acos((sq(a.r) + sq(d) - sq(b.r)) / (2 * a.r * d)), z = (b.c - a.c).angle();
    if (z < 0) z += 2 * pi;
    double l = z - o, r = z + o;
    if (l < 0) l += 2 * pi;
    if (r > 2 * pi) r -= 2 * pi;
    if (l > r) res.emplace_back(l, 2 * pi), res.emplace_back(0, r);
    else res.emplace_back(l, r);
  }
  return res;
}

vector<pair<double, double>> s, z;
vector<double> nums;
vector<int> delta;

double CUA(vector<C> &c) {
  int n = c.size();
  double a = 0;
  for (int i = 0; i < n; ++i) {
    s.clear();
    for (int j = 0; j < n; ++j) if (i != j) {
      z = CS(c[i], c[j]);
      for (auto &e : z) s.push_back(e);
    }
    sort(s.begin(), s.end());
    auto F = [&] (double t) { return c[i].r * (c[i].r * t + c[i].c.x * sin(t) - c[i].c.y * cos(t)); };

    nums.clear();
    for (auto [l, r] : s) nums.push_back(l), nums.push_back(r);
    sort(nums.begin(), nums.end());
    nums.resize(unique(nums.begin(), nums.end(), [&] (const double a, const double b) { return same(a, b); }) - nums.begin());

    delta.resize(nums.size());
    fill(delta.begin(), delta.end(), 0);

    for (auto &e : s) {
      int l = lower_bound(nums.begin(), nums.end(), e.first - 2 * eps) - nums.begin();
      int r = lower_bound(nums.begin(), nums.end(), e.second - 2 * eps) - nums.begin();
      delta[l] += 1;
      delta[r] -= 1;
    }

    int covered = 0;
    for (int i = 0; i < (int)nums.size(); ++i) {
      covered += delta[i];
      if (covered == n - 1) {
        a += F(nums[i + 1]) - F(nums[i]);
      }
    }
  }
  return a * 0.5;
}

void solve() {
  int n, r; cin >> n >> r;
  vector<P> ps(n);
  for (int i = 0; i < n; ++i) cin >> ps[i].x >> ps[i].y;

  vector<C> cs(n);
  for (int i = 0; i < n; ++i) cs[i].c = ps[i], cs[i].r = r;

  double ans = CUA(cs);
  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t; while (t--) solve();
}
