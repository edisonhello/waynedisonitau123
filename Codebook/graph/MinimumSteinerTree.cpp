namespace steiner {
// Minimum Steiner Tree - O(N * 3^K + N^2 * 2^K)
// z[i] = the weight of the i-th vertex
const int maxn = 64, maxk = 10;
const int inf = 1e9;
int w[maxn][maxn], z[maxn], dp[1 << maxk][maxn], off[maxn];
void init(int n) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) w[i][j] = inf;
    z[i] = 0;
    w[i][i] = 0;
  }
}
void add_edge(int x, int y, int d) {
  w[x][y] = min(w[x][y], d);
  w[y][x] = min(w[y][x], d);
}
void build(int n) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      w[i][j] += z[i];
      if (i != j) w[i][j] += z[j];
    }
  }
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) w[i][j] = min(w[i][j], w[i][k] + w[k][j] - z[k]);
    }
  }
}
int solve(int n, vector<int> mark) {
  build(n);
  int k = (int)mark.size();
  assert(k < maxk);
  for (int s = 0; s < (1 << k); ++s) {
    for (int i = 0; i < n; ++i) dp[s][i] = inf;
  }
  for (int i = 0; i < n; ++i) dp[0][i] = 0;
  for (int s = 1; s < (1 << k); ++s) {
    if (__builtin_popcount(s) == 1) {
      int x = __builtin_ctz(s);
      for (int i = 0; i < n; ++i) dp[s][i] = w[mark[x]][i];
      continue;
    }
    for (int i = 0; i < n; ++i) {
      for (int sub = s & (s - 1); sub; sub = s & (sub - 1)) {
        dp[s][i] = min(dp[s][i], dp[sub][i] + dp[s ^ sub][i] - z[i]);
      }
    }
    for (int i = 0; i < n; ++i) {
      off[i] = inf;
      for (int j = 0; j < n; ++j) off[i] = min(off[i], dp[s][j] + w[j][i] - z[j]);
    }
    for (int i = 0; i < n; ++i) dp[s][i] = min(dp[s][i], off[i]);
  }
  int res = inf;
  for (int i = 0; i < n; ++i) res = min(res, dp[(1 << k) - 1][i]);
  return res;
}}
