#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int M, N;
  cin >> M >> N;
  int64_t k;
  cin >> k;
  vector<int> x(M), y(M);
  vector<int64_t> s(M), t(M);
  vector<double> pb(M);
  vector<vector<int>> g(N);
  for (int i = 0; i < M; ++i) {
    cin >> x[i] >> y[i] >> s[i] >> t[i] >> pb[i];
    g[x[i]].push_back(i);
  }

  vector<int64_t> ts;
  for (int i = 0; i < M; ++i) {
    ts.push_back(s[i]);
    ts.push_back(t[i]);
  }

  sort(ts.begin(), ts.end());
  ts.resize(unique(ts.begin(), ts.end()) - ts.begin());

  vector<vector<int>> events(ts.size());
  vector<vector<int>> tp(N);
  for (int i = 0; i < M; ++i) {
    int p = lower_bound(ts.begin(), ts.end(), s[i]) - ts.begin();
    events[p].emplace_back(x[i]);
    tp[x[i]].push_back(p);
  }
  vector<vector<double>> dp(N);
  vector<vector<vector<int>>> out(N);
  for (int i = 0; i < N; ++i) {
    sort(tp[i].begin(), tp[i].end());
    tp[i].resize(unique(tp[i].begin(), tp[i].end()) - tp[i].begin());
    dp[i].resize(tp[i].size());
    out[i].resize(tp[i].size());
  }
  for (int i = 0; i < M; ++i) {
    int p = lower_bound(ts.begin(), ts.end(), s[i]) - ts.begin();
    p = lower_bound(tp[x[i]].begin(), tp[x[i]].end(), p) - tp[x[i]].begin();
    out[x[i]][p].push_back(i);
  }
  for (int i = ts.size() - 1; i >= 0; --i) {
    // cout << "t = " << ts[i] << endl;
    sort(events[i].begin(), events[i].end());
    events[i].resize(unique(events[i].begin(), events[i].end()) - events[i].begin());
    for (int x : events[i]) {
      // cout << "x = " << x << endl;
      int p = lower_bound(tp[x].begin(), tp[x].end(), i) - tp[x].begin();
      // cout << "p = " << p << endl;
      double nxt = p + 1 < tp[x].size() ? dp[x][p + 1] : 0;
      // cout << "nxt = " << nxt << endl;
      dp[x][p] = nxt;
      const vector<int>& route = out[x][p];
      double v = 0;
      for (int e : route) {
        int tt = lower_bound(ts.begin(), ts.end(), t[e]) - ts.begin();
        auto it = upper_bound(tp[y[e]].begin(), tp[y[e]].end(), tt) - tp[y[e]].begin();
        double w = y[e] == 1 ? 1 : (it < tp[y[e]].size() ? dp[y[e]][it] : 0);
        v = max(v, pb[e] * w + (1 - pb[e]) * nxt);
      }
      dp[x][p] = max(dp[x][p], v);
      // cout << "dp[" << x << "][" << ts[i] << "] = " << dp[x][p] << endl;
    }
  }
  cout << fixed << setprecision(20);
  if (dp[0].empty()) {
    cout << 0 << "\n";
  } else {
    cout << dp[0][0] << "\n";
  }
  return 0;
}

