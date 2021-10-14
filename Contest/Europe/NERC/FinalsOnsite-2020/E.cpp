#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  double X, Y;
  cin >> N >> X >> Y;
  int H = N / 2;
  vector<vector<vector<tuple<double, double, int>>>> info(
      324 + 1, vector<vector<tuple<double, double, int>>>(H + 1));
  constexpr double kEps = 1E-8;
  for (int s = 0; s < (1 << H); ++s) {
    int p = 0, m = 0;  // m = mass * 2
    double x = 0, y = 0;
    bool bad = false;
    for (int i = 0; i < H; ++i) {
      if (s >> i & 1) {
        double tx = static_cast<double>(i + i + 1 + i + 1) / 3;
        double ty = static_cast<double>(p + p + p + 1) / 3;
        double sx = i + 0.5;
        double sy = static_cast<double>(p) / 2;
        double rx = (tx + sx * p * 2) / (1 + p * 2);
        double ry = (ty + sy * p * 2) / (1 + p * 2);
        x = (x * m + rx * (1 + p * 2)) / (m + 1 + p * 2);
        y = (y * m + ry * (1 + p * 2)) / (m + 1 + p * 2);
        m += 1 + p * 2;
        p++;
      } else {
        if (p == 0) {
          bad = true;
          break;
        }
        double tx = static_cast<double>(i + i + i + 1) / 3;
        double ty = static_cast<double>(p + p - 1 + p - 1) / 3;
        double sx = i + 0.5;
        double sy = static_cast<double>(p - 1) / 2;
        double rx = (tx + sx * (p - 1) * 2) / (1 + (p - 1) * 2);
        double ry = (ty + sy * (p - 1) * 2) / (1 + (p - 1) * 2);
        x = (x * m + rx * (1 + (p - 1) * 2)) / (m + 1 + (p - 1) * 2);
        y = (y * m + ry * (1 + (p - 1) * 2)) / (m + 1 + (p - 1) * 2);
        m += 1 + (p - 1) * 2;
        p--;
      }
    }
    if (bad) continue;
    // cout << "m = " << m << " p = " << p << " x = " << x << " y = " << y << " s = " << s << "\n";
    info[m][p].emplace_back(x, y, s);
  }
  for (int m = 0; m <= 324; ++m) {
    for (int i = 0; i <= H; ++i) {
      sort(info[m][i].begin(), info[m][i].end());
    }
  }
  for (int s = 0; s < (1 << H); ++s) {
    int pc = __builtin_popcount(s);
    int diff = (H - pc) - pc;
    if (diff < 0) continue;
    int p = diff, m = 0;  // mass * 2
    double x = 0, y = 0;
    bool bad = false;
    for (int i = 0; i < H; ++i) {
      if (s >> i & 1) {
        double tx = static_cast<double>(i + i + 1 + i + 1) / 3;
        double ty = static_cast<double>(p + p + p + 1) / 3;
        double sx = i + 0.5;
        double sy = static_cast<double>(p) / 2;
        double rx = (tx + sx * p * 2) / (1 + p * 2);
        double ry = (ty + sy * p * 2) / (1 + p * 2);
        x = (x * m + rx * (1 + p * 2)) / (m + 1 + p * 2);
        y = (y * m + ry * (1 + p * 2)) / (m + 1 + p * 2);
        m += 1 + p * 2;
        p++;
      } else {
        if (p == 0) {
          bad = true;
          break;
        }
        double tx = static_cast<double>(i + i + i + 1) / 3;
        double ty = static_cast<double>(p + p - 1 + p - 1) / 3;
        double sx = i + 0.5;
        double sy = static_cast<double>(p - 1) / 2;
        double rx = (tx + sx * (p - 1) * 2) / (1 + (p - 1) * 2);
        double ry = (ty + sy * (p - 1) * 2) / (1 + (p - 1) * 2);
        x = (x * m + rx * (1 + (p - 1) * 2)) / (m + 1 + (p - 1) * 2);
        y = (y * m + ry * (1 + (p - 1) * 2)) / (m + 1 + (p - 1) * 2);
        m += 1 + (p - 1) * 2;
        p--;
      }
    }
    if (bad) continue;
    assert(p == 0);
    // cout << "m = " << m << " p = " << p << " x = " << x + H << " y = " << y << " s = " << s << " diff = " << diff << "\n";
    // info[m][p].emplace_back(x, y, s);
    for (int i = 0; i <= 324; ++i) {
      if (info[i][diff].empty()) continue;
      double tx = ((i + m) * X - m * (x + H)) / i;
      double ty = ((i + m) * Y - m * y) / i;
      // cout << "tx = " << tx << " ty = " << ty << "\n";
      auto iter = lower_bound(info[i][diff].begin(), info[i][diff].end(), make_tuple(tx - kEps, ty - kEps, -1));
      if (iter != info[i][diff].end()) {
        double sx = get<0>(*iter);
        double sy = get<1>(*iter);
        if (fabs(sx - tx) < kEps && fabs(sy - ty) < kEps) {
          int w = get<2>(*iter);
          for (int j = 0; j < H; ++j) {
            if (w >> j & 1) cout << "(";
            else cout << ")";
          }
          for (int j = 0; j < H; ++j) {
            if (s >> j & 1) cout << "(";
            else cout << ")";
          }
          cout << "\n";
          return 0;
        }
      }
    }
  }
  return 0;
}
