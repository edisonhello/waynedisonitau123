#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  constexpr double kPi = acos(-1);
  constexpr double kEps = 1E-8;
  while (T--) {
    int C;
    cin >> C;
    int N;
    cin >> N;

    double La = -1, Ra = 1E9;
    vector<double> x(N), y(N);

    auto Get = [&C](double alpha, double x, double y) {
      double t = (x / (C * cos(alpha)));
      return x * tan(alpha) - 5 * t * t - y;
    };

    constexpr int kIter = 20;
    for (int i = 0; i < N; ++i) {
      cin >> x[i] >> y[i];
      double l = 0, r = kPi / 2;
      double alpha = atan(static_cast<double>(C) * C / 10 / x[i]);
      l = 0;
      r = alpha;
      for (int it = 0; it < kIter; ++it) {
        double mid = (l + r) / 2;
        if (Get(mid, x[i], y[i]) >= 0) r = mid;
        else l = mid;
      }
      double L = (l + r) / 2;
      l = alpha;
      r = kPi / 2;
      for (int it = 0; it < kIter; ++it) {
        double mid = (l + r) / 2;
        if (Get(mid, x[i], y[i]) >= 0) l = mid;
        else r = mid;
      }
      double R = (l + r) / 2;
      La = max(La, L);
      Ra = min(Ra, R);
    }
    assert(La <= Ra + kEps);
    double ans = (La + Ra) / 2;
    for (int i = 0; i < N; ++i) assert(Get(ans, x[i], y[i]) > -kEps);
    cout << fixed << setprecision(3) << tan(ans) << "\n";
  }
}
