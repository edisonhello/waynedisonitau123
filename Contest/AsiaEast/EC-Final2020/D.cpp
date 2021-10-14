#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N, M, K;
  cin >> N >> M >> K;

  vector<vector<int>> g(N);
  for (int i = 0; i < M; ++i) {
    int x, y;
    cin >> x >> y;
    x--;
    y--;
    g[x].push_back(y);
    g[y].push_back(x);
  }

  int s1, t1, s2, t2;
  cin >> s1 >> t1 >> s2 >> t2;
  s1--;
  t1--;
  s2--;
  t2--;

  auto GetDist = [&](int x) {
    vector<int> dist(N, -1), que(1, x);
    dist[x] = 0;
    for (int i = 0; i < que.size(); ++i) {
      int y = que[i];
      for (int u : g[y]) {
        if (dist[u] == -1) {
          dist[u] = dist[y] + 1;
          que.push_back(u);
        }
      }
    }
    return dist;
  };

  auto ds1 = GetDist(s1);
  auto dt1 = GetDist(t1);
  auto ds2 = GetDist(s2);
  auto dt2 = GetDist(t2);

  auto Solve = [&](int A, int B) -> double {
    if (A == 0 && B == 0) return 0;
    if (A == 0) {
      int t = K / B;
      int g = K % B;
      return 2 * static_cast<double>(B - g) / (t + 1) +
             2 * static_cast<double>(g) / (t + 2);
    }
    if (B == 0) {
      int t = K / A;
      int g = K % A;
      return static_cast<double>(A - g) / (t + 1) +
             static_cast<double>(g) / (t + 2);
    }
    int64_t s = 0;
    int sx = -1, sy = -1;
    for (int bit = 60; bit >= 0; --bit) {
      int64_t t = s + (1LL << bit);
      int x = 0;
      for (int b = 30; b >= 0; --b) {
        if (1LL * (x + (1 << b)) * (x + (1 << b) + 1) <= t) {
          x += (1 << b);
        }
      }
      int y = 0;
      for (int b = 30; b >= 0; --b) {
        if (2LL * (y + (1 << b)) * (y + (1 << b) + 1) <= t) {
          y += (1 << b);
        }
      }
      int64_t need = 1LL * x * B + 1LL * y * A;
      if (need <= K) {
        sx = x;
        sy = y;
        s = t;
      }
    }
    int need = sx * B + sy * A;
    assert(need <= K);
    int remain = K - need;
    double res = 2 * static_cast<double>(B) / (sx + 1) + static_cast<double>(A) / (sy + 1);
    while (remain > 0) {
      if (2LL * (sy + 1) * (sy + 2) < 1LL * (sx + 1) * (sx + 2)) {
        int take = min(A, remain);  
        remain -= take;
        sy++;
        if (remain == 0) {
          res = 2 * static_cast<double>(B) / (sx + 1) +
                static_cast<double>(take) / (sy + 1) +
                static_cast<double>(A - take) / sy;
        }
      } else {
        int take = min(B, remain);  
        remain -= take;
        sx++;
        if (remain == 0) {
          res = 2 * static_cast<double>(take) / (sx + 1) +
                2 * static_cast<double>(B - take) / sx +
                static_cast<double>(A) / (sy + 1);
        }
      }
    }
    return res;
  };

  double ans = Solve(ds1[t1] + ds2[t2], 0);

  constexpr int kInf = 1'000'000'000;
  vector<int> best(N + 1, kInf);

  for (int x = 0; x < N; ++x) {
    if (ds1[x] == -1 || ds2[x] == -1) continue;
    auto dist = GetDist(x);
    for (int y = 0; y < N; ++y) {
      if (dt1[y] == -1 || dt2[y] == -1) continue;
      best[dist[y]] = min(best[dist[y]], ds1[x] + ds2[x] + dt1[y] + dt2[y]);
    }
  }
  for (int x = 0; x < N; ++x) {
    if (ds1[x] == -1 || dt2[x] == -1) continue;
    auto dist = GetDist(x);
    for (int y = 0; y < N; ++y) {
      if (dt1[y] == -1 || ds2[y] == -1) continue;
      best[dist[y]] = min(best[dist[y]], ds1[x] + dt2[x] + dt1[y] + ds2[y]);
    }
  }
  for (int i = 0; i <= N; ++i) {
    if (best[i] < kInf) ans = min(ans, Solve(best[i], i));
  }
  cout << fixed << setprecision(20) << ans << "\n";
}
