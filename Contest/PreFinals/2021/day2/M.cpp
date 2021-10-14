#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M;
  cin >> N >> M;
  vector<vector<pair<int, int>>> poly(N);
  vector<pair<int, int>> but(N);
  for (int i = 0; i < N; ++i) {
    int P;
    cin >> P;
    poly[i].resize(P);
    for (int j = 0; j < P; ++j) {
      cin >> poly[i][j].first >> poly[i][j].second;
    }
    cin >> but[i].first >> but[i].second;
  }
  vector<vector<double>> dist(N, vector<double>(N, 1E18));

  auto Dist = [&](auto p, auto q) {
    return hypot(p.first - q.first, p.second - q.second);
  };

  vector<int> deg(N);
  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      for (int k = 0; k < poly[i].size(); ++k) {
        for (int l = 0; l < poly[j].size(); ++l) {
          if (poly[i][k] == poly[j][l]) {
            dist[i][j] = dist[j][i] = Dist(poly[i][k], but[i]) + Dist(poly[j][l], but[j]);
            deg[i]++;
            deg[j]++;
          }
        }
      }
    }
  }
  double ans = 0.0;
  for (int i = 0; i < N; ++i) dist[i][i] = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      if (dist[i][j] < 1E10) ans += 2 * dist[i][j];
    }
  }
  for (int k = 0; k < N; ++k) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    }
  }
  vector<int> odd;
  for (int i = 0; i < N; ++i) {
    if (deg[i] & 1) odd.push_back(i);
  }
  int K = odd.size();
  vector<double> dp(1 << K, 1E18);
  dp[0] = 0;
  for (int s = 1; s < (1 << K); ++s) {
    for (int i = 0; i < K; ++i) {
      if (s >> i & 1) {
        for (int j = i + 1; j < K; ++j) {
          if (s >> j & 1) {
            dp[s] = min(dp[s], dp[s ^ (1 << i) ^ (1 << j)] + dist[odd[i]][odd[j]]);
          }
        }
      }
    }
  }
  cout << fixed << setprecision(20) << ans + dp[(1 << K) - 1] << "\n";
}
