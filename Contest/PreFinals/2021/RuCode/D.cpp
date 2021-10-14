#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1);

double dp[2004][2004], D[2004][2004];
double fw[2004][2004];

int main() {
  int n, k; cin >> n >> k;

  vector<pair<double, double>> segs;
  vector<double> os;

  for (int i = 0; i < n; ++i) {
    double x, y, r;
    cin >> x >> y >> r;
    
    if (y + r < 0) continue;

    double d = hypot(x, y);

    double dd = sqrt(d * d - r * r);

    double o = atan2(y, x);
    double oo = acos((d * d + dd * dd - r * r) / (2 * d * dd));
    
    double R = o + oo, l = o - oo;
    if (l < -PI) {
      l += 2 * PI;
      R += 2 * PI;
    }
    R = min(R, PI);
    l = max(l, (double)0);

    // cerr << l << ' ' << R << endl;

    segs.emplace_back(l, R);
    os.emplace_back(l);
    os.emplace_back(R);
  }

  sort(os.begin(), os.end());
  os.resize(unique(os.begin(), os.end()) - os.begin());

  sort(segs.begin(), segs.end(), [&] (const pair<double, double> &a, const pair<double, double> &b) { return a.second < b.second; });

  for (int i = 0; i < 2004; ++i) {
    for (int j = 0; j < 2004; ++j) fw[i][j] = -1E9;
  }

  auto Update = [&](double *fw, int p, double v) {
    for (int i = p + 1; i < 2004; i += i & -i)
      fw[i] = max(fw[i], v);
  };

  auto Query = [&](double *fw, int p) {
    double res = -1E9;
    for (int i = p + 1; i > 0; i -= i & -i)
      res = max(res, fw[i]);
    return res;
  };

  for (int i = 0; i < 2004; ++i) {
    for (int j = 0; j < 2004; ++j) dp[i][j] = -1E9;
  }
  for (int i = 0, ptr = 0; i < segs.size(); ++i) {
    dp[i][1] = segs[i].second - segs[i].first;
    int p = -1;
    for (int d = 20; d >= 0; --d) {
      if (p + (1 << d) < i && segs[p + (1 << d)].second <= segs[i].first)
        p += (1 << d);
    }
    for (int j = k; j >= 2; --j) {
      if (p >= 0) dp[i][j] = D[p][j - 1] + segs[i].second - segs[i].first;
      dp[i][j] = max(dp[i][j], segs[i].second + Query(fw[j - 1], 2000 - (p + 1)));
      Update(fw[j], 2000 - i, dp[i][j] - segs[i].second);
    }
    Update(fw[1], 2000 - i, dp[i][1] - segs[i].second);
    // for (int j = 2; j <= k; ++j) {
    //   for (int p = 0; p < i; ++p) {
    //     if (segs[p].second <= segs[i].first)
    //       dp[i][j] = max(dp[i][j], dp[p][j - 1] + segs[i].second - segs[i].first);
    //     else
    //       dp[i][j] = max(dp[i][j], dp[p][j - 1] + segs[i].second - segs[p].second);
    //   }
    // }
    for (int j = 1; j <= k; ++j) {
      D[i][j] = dp[i][j];
      if (i > 0) D[i][j] = max(D[i][j], D[i - 1][j]);
    }
  }

  cout << fixed << setprecision(20) << D[segs.size() - 1][k] / PI << endl;
}
