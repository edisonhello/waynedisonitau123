#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, w, h;
  cin >> N >> w >> h;
  vector<int> x(N), y(N);
  for (int i = 0; i < N; ++i) {
    cin >> x[i] >> y[i];
  }
  int64_t ans = 0;
  for (int t = 1; t <= w; ++t) {
    vector<double> levent;
    vector<double> revent;
    for (int i = 0; i < N; ++i) {
      int x1 = x[i], x2 = x[(i + 1) % N];
      int y1 = y[i], y2 = y[(i + 1) % N];
      if (x1 == x2) {
        continue;
      }
      if (max(x1, x2) <= t - 1) {
        continue;
      }
      if (min(x1, x2) >= t) {
        continue;
      }
      levent.push_back(y1 + static_cast<double>(y2 - y1) / (x2 - x1) * ((t - 1) - x1));
      revent.push_back(y1 + static_cast<double>(y2 - y1) / (x2 - x1) * (t - x1));
    }
    sort(levent.begin(), levent.end());
    sort(revent.begin(), revent.end());
    vector<pair<int, int>> cur;
    for (int j = 0; j + 1 < levent.size(); j += 2) {
      int l1 = floor(levent[j] + 1e-8);
      int r1 = floor(levent[j + 1] - 1e-8);
      int l2 = floor(revent[j] + 1e-8);
      int r2 = floor(revent[j + 1] - 1e-8);
      // cout << "l = " << l << " r = " << r << endl;
      cur.emplace_back(min(l1, l2), max(r1, r2));
    }
    vector<pair<int, int>> ev;
    for (auto [l, r] : cur) {
      ev.emplace_back(l, 1);
      ev.emplace_back(r + 1, -1);
    }
    sort(ev.begin(), ev.end());
    int s = 0, pv = -1;
    for (int i = 0, j = 0; i < ev.size(); i = j) {
      while (j < ev.size() && ev[j].first == ev[i].first) {
        s += ev[j].second;
        j++;
      }
      if (s > 0 && pv == -1) {
        pv = ev[i].first;
      } else if (s == 0) {
        // cout << "t = " << t << " add = " << pv << " " << ev[i].first - 1 << endl;
        ans += ev[i].first - pv;
        pv = -1;
      }
    }
  }
  cout << ans << "\n";
}
