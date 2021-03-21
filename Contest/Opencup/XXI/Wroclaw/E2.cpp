#include <bits/stdc++.h>
using namespace std;

pair<double, double> solve2(double a, double b, double c) {
  // cerr << "bb 4ac " << b * b - 4 * a * c << endl;
  double d = sqrt(b * b - 4 * a * c) / (2 * a);
  double u = -b / (2 * a);
  return make_pair(u - d, u + d);
}

pair<double, double> solve(double c, double x, double y) {
  return solve2(5 * x * x / (c * c), -x, y + 5 * x * x / (c * c));
}

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
      auto [L, R] = solve(C, x[i], y[i]);
      // cerr << "L R = " << L << ' ' << R << endl;
      La = max(La, L);
      Ra = min(Ra, R);
    }
    assert(La <= Ra + kEps);
    double ans = (La + Ra) / 2;
    cout << fixed << setprecision(3) << ans << "\n";
  }
}
