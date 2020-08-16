#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second

double eps = 1e-9;
bool same(double a, double b) {
  return abs(a - b) < eps;
}

struct cmp {
  bool operator() (const pair<double, double> &a, const pair<double, double> &b) const {
    return same(a.first, b.first) ? same(a.second, b.second) ? 0 : a.second < b.second : a.first < b.first;
  }
};

pair<int, int> ps[2505]; 

int main() {
  int n; cin >> n;
  for (int i = 0; i < n; ++i) cin >> ps[i].first >> ps[i].second;

  map<pair<double, double>, int, cmp> mp;

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      double a = ps[i].y - ps[j].y;
      double b = ps[j].x - ps[i].x;
      double c = ps[i].x * ps[j].y - ps[i].y * ps[j].x;

      if (same(c, 0)) {
        if (same(b, 0)) {
          a = 1;
          b = 0;
        } else {
          a /= b;
          b /= b;
          if (b < 0) {
            a *= -1;
            b *= -1;
          }
        }
      } else {
        a /= c;
        b /= c;
        c /= c;
        if (c < 0) {
          a *= -1;
          b *= -1;
          c *= -1;
        }
      }

      ++mp[make_pair(a, b)];
    }
  }

  if (n <= 2) {
    cout << n << endl;
    exit(0);
  }

  int mx = 0;
  for (auto &p : mp) mx = max(mx, p.second);
  for (int i = 3; i <= n; ++i) {
    if (mx == i * (i - 1) / 2) {
      cout << i << endl;
      exit(0);
    }
  }

  exit(1);



}
