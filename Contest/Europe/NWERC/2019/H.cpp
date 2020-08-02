#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  int n, k;
  cin >> n >> k;
  vector<int> h(n + 1);
  for (int i = 0; i <= n; ++i) {
    cin >> h[i];
  }

  auto Solve = [&](int g) {
    vector<pair<int64_t, int>> qu;
    double res = -1;
    for (int i = 0; i <= n; ++i) {
      int64_t v = h[i] - 1LL * g * i;
      if (!qu.empty()) {
        int k = (int)qu.size();
        for (int j = 20; j >= 0; --j) {
          if (k - (1 << j) < 0) continue;
          if (qu[k - (1 << j)].first <= v) {
            k -= (1 << j);
          }
        }
        if (k < qu.size()) {
          int u = qu[k].second;
          assert(h[i] - h[u] >= 1LL * (i - u) * g);
          double got = i - u;
          if (u > 0) {
            double l = 0.0, r = 1.0;
            for (int it = 0; it < 30; ++it) {
              double mid = 0.5 * (l + r);
              double mh = h[u] + mid * (h[u - 1] - h[u]);
              if ((h[i] - mh) >= g * (i - u + mid)) l = mid;
              else r = mid;
            }
            got += l;
          }
          res = max(res, got);
        }
      }
      if (qu.empty() || qu.back().first > v) {
        qu.emplace_back(v, i);
      }
    }
    qu.clear();
    for (int i = n; i >= 0; --i) {
      int64_t v = h[i] - 1LL * g * i;
      if (!qu.empty()) {
        int k = (int)qu.size();
        for (int j = 20; j >= 0; --j) {
          if (k - (1 << j) < 0) continue;
          if (qu[k - (1 << j)].first >= v) {
            k -= (1 << j);
          }
        }
        if (k < qu.size()) {
          int u = qu[k].second;
          assert(h[u] - h[i] >= 1LL * (u - i) * g);
          double got = u - i;
          if (u + 1 <= n) {
            double l = 0.0, r = 1.0;
            for (int it = 0; it < 30; ++it) {
              double mid = 0.5 * (l + r);
              double mh = h[u] + mid * (h[u + 1] - h[u]);
              if ((mh - h[i]) >= g * (u - i + mid)) l = mid;
              else r = mid;
            }
            got += l;
          }
          res = max(res, got);
        }
      }
      if (qu.empty() || qu.back().first < v) {
        qu.emplace_back(v, i);
      }
    }
    return res;
  };
  
  for (int i = 0; i < k; ++i) {
    string s;
    cin >> s;
    bool neg = false;
    if (s[0] == '-') {
      s = s.substr(1);
      neg = true;
    }
    int g = 0, j = 0;
    for (j = 0; s[j] != '.'; j++) g = g * 10 + (s[j] - '0');
    for (j++; j < s.size(); j++) g = g * 10 + (s[j] - '0');
    if (neg) g = -g;
    double res = Solve(g);
    if (res < 0) printf("-1\n");
    else printf("%.20lf\n", res);
  }
}
