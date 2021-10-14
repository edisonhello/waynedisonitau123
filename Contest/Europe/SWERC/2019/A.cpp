#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;

#define sq(x) ((x) * (x))
#define Update(x, y) x = min(x, y);

int main() {
  int sx, sy, tx, ty; cin >> sx >> sy >> tx >> ty;
  int B; cin >> B;
  vector<int> C(105, 0);
  cin >> C[0];
  int T; cin >> T;
  for (int i = 1; i <= T; ++i) cin >> C[i];
  int N; cin >> N;
  vector<pair<int, int>> pos(N + 2);
  vector<vector<tuple<int, int, int>>> G(N + 2);

  auto AddEdge = [&] (int i, int j, int t) -> void {
    int dd = sq(pos[i].first - pos[j].first) + sq(pos[i].second - pos[j].second);
    double d = sqrt((double)dd);
    int rd = ceil(d - eps);
    int w = rd * C[t];

    // cerr << "i j t dd d rd w " << i << ' ' << j << ' ' << t << ' ' << dd << ' ' << d << ' ' << rd << ' ' << w << endl;
    
    G[i].emplace_back(j, rd, w);
    G[j].emplace_back(i, rd, w);
  };

  vector<tuple<int, int, int>> recedge;
  for (int i = 0; i < N; ++i) {
    cin >> pos[i].first >> pos[i].second;
    int z; cin >> z;
    while (z--) {
      int j, t; cin >> j >> t;
      recedge.emplace_back(i, j, t);
      // AddEdge(i, j, t);
    }
  }
  pos[N] = make_pair(sx, sy);
  pos[N + 1] = make_pair(tx, ty);

  for (auto [i, j, t] : recedge) {
    AddEdge(i, j, t);
  }

  AddEdge(N, N + 1, 0);
  for (int i = 0; i < N; ++i) {
    AddEdge(i, N, 0);
    AddEdge(i, N + 1, 0);
  }

  vector<vector<int>> dp(B + 1, vector<int>(N + 2, 1000000000));
  dp[0][N] = 0;

  for (int b = 0; b < B; ++b) {
    for (int i = 0; i < N + 2; ++i) {
      for (auto [j, d, w] : G[i]) {
        if (b + d > B) continue;
        Update(dp[b + d][j], dp[b][i] + w);
      }
    }
  }

  int mn = INT_MAX;
  for (int b = 0; b <= B; ++b) {
    mn = min(mn, dp[b][N + 1]);
  }
  if (mn >= 1000000000) mn = -1;
  cout << mn << endl;
}
