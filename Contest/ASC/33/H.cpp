#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);
pair<int, int> p[1555];

int main() {
  freopen("points.in", "r", stdin);
  freopen("points.out", "w", stdout);

  int n; cin >> n;
  for (int i = 0; i < n; ++i) cin >> p[i].first >> p[i].second;

  long long out = 0;
  for (int i = 0; i < n; ++i) {
    vector<pair<double, pair<int, int>>> vp;
    // cerr << "pivot " << p[i].first << ' ' << p[i].second << endl;
    for (int j = 0; j < n; ++j) if (j != i) vp.emplace_back(atan2(p[j].second - p[i].second, p[j].first - p[i].first), p[j]);
    sort(vp.begin(), vp.end());

    // for (auto &p : vp) {
    //   cerr << "p " << p.first << ": " << p.second.first << ' ' << p.second.second << endl;
    // }

    int op = 0;
    double add = 0;
    int c = 0;
    for (int j = 0; j < (int)vp.size(); ++j) {
      while (op < (int)vp.size() && (vp[op].first + add - vp[j].first) < pi) ++op, ++c;
      if (op == (int)vp.size() && vp[0].first + 2 * pi - vp[j].first < pi) {
        op = 1;
        ++c;
        add = 2 * pi;
      }
      while (op < (int)vp.size() && (vp[op].first + add - vp[j].first) < pi) ++op, ++c;
      out += 1ll * (c - 1) * (c - 2) / 2;
      // cerr << "j c out " << j << ' ' << c << ' ' << out << endl;
      --c;
    }
  }

  out -= 2ll * n * (n - 1) * (n - 2) * (n - 3) / 24;
  cout << fixed << setprecision(12) << (double)(out) / (1ll * n * (n - 1) * (n - 2) / 6) << endl;

}
