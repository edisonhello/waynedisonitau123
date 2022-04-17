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
  vector<pair<int, int>> prv;
  for (int t = 0; t <= w; ++t) {
    vector<double> event;
    for (int i = 0; i < N; ++i) {
      int x1 = x[i], x2 = x[(i + 1) % N];
      int y1 = y[i], y2 = y[(i + 1) % N];
      if (x1 == x2) {
        if (t == x1) {
          event.push_back(min(y1, y2));
          event.push_back(max(y2, y1));
        }
        continue;
      }
      if (x1 > x2) {
        if (x2 == t) {
          if (x[(i + 2) % N] > t) {
            continue;
          }
        }
        if (x1 == t) {
          if (x[(i + N - 1) % N] < t) {
            continue;
          }
        }
        if (t <= x1 && t > x2) {
          double y = y1 + static_cast<double>(y2 - y1) * (t - x1) / (x2 - x1);
          event.push_back(y);
        }
      } else {
        if (x2 == t) {
          if (x[(i + 2) % N] < t) {
            continue;
          }
        }
        if (x1 == t) {
          if (x[(i + N - 1) % N] > t) {
            continue;
          }
        }
        if (x1 <= t && t < x2) {
          double y = y1 + static_cast<double>(y2 - y1) * (t - x1) / (x2 - x1);
          event.push_back(y);
        }
      }
    }
    sort(event.begin(), event.end());
    cout << "t = " << t << " event = " << event.size() << endl;
    vector<pair<int, int>> cur;
    for (int j = 0; j + 1 < event.size(); j += 2) {
      int l = floor(event[j]);
      int r = floor(event[j + 1] - 1e-8);
      cout << "l = " << l << " r = " << r << endl;
      cur.emplace_back(l, r);
    }
    if (t > 0) {
      vector<pair<int, int>> ev;
      for (auto [l, r] : prv) {
        ev.emplace_back(l, 1);
        ev.emplace_back(r + 1, -1);
      }
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
          cout << "t = " << t << " add = " << pv << " " << ev[i].first - 1 << endl;
          ans += ev[i].first - pv;
          pv = -1;
        }
      }
    }
    prv = cur;
  }
  cout << ans << "\n";
}
