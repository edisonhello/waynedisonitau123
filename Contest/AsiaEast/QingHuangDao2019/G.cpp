#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;

  vector<int> cnt(N + 1);
  vector<uint64_t> perm;

  auto Hash = [&](const vector<int> &v) -> uint64_t {
    uint64_t hv = 0;
    for (int i = 0; i < v.size(); ++i) hv |= (static_cast<uint64_t>(v[i]) << (4 * i));
    return hv;
  };

  auto DfsState = [&](auto dfs, int x, int s, uint64_t hv = 0) -> void {
    if (x < 0) {
      if (s == N) perm.push_back(hv);
      return;
    }
    for (int i = 0; i + s <= N; ++i) {
      dfs(dfs, x - 1, hv | (static_cast<uint64_t>(i) << (x * 4)));
    }
  };

  DfsState(DfsState, N, 0);

  // unordered_map<uint64_t, int> T;
  // for (int i = 0; i < perm.size(); ++i) T[perm[i]] = i;

  vector<string> grid(N);
  for (int i = 0; i < N; ++i) cin >> grid[i];
  vector<vector<int>> w(N, vector<int>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) cin >> w[i][j];
  }

  auto Get = [&](uint64_t v) {
    return lower_bound(perm.begin(), perm.end(), v) - perm.begin();
  };

  constexpr int kInf = 2'000'000'000;
  const int K = perm.size();

  vector<int> dp(K, kInf);

  auto GetH = [&](uint64_t H, int p) {
    return H >> (p * 4) & 15;
  };

  auto IncH = [&](uint64_t &H, int p) {
    p <<= 2;
    int t = H >> p & 15;
    H &= ~(15ULL << p);
    H |= static_cast<uint64_t>(t + 1) << p;
  };

  auto DecH = [&](uint64_t &H, int p) {
    p <<= 2;
    int t = H >> p & 15;
    H &= ~(15ULL << p);
    H |= static_cast<uint64_t>(t - 1) << p;
  };

  dp[0] = 0;
  pair<int, int> black[20], white[20];
  for (int s = 1; s < K; ++s) {
    uint64_t H = perm[s];
    int quota = 0;
    int p = -1;
    bool f = false;
    int pb = 0, pw = 0;
    for (int i = N - 1, j = 0; i >= 0; --i) {
      while (quota == 0) {
        assert(j <= N);
        quota += GetH(H, j++);
      }
      quota--;
      int h = j - 1;
      if (h > 0 && h > p) {
        uint64_t t = H;
        DecH(t, h);
        IncH(t, h - 1);
        int g = Get(t);
        dp[s] = min(dp[s], dp[g] + w[N - h][i]);
        if (grid[N - h][i] == 'B') black[pb++] = make_pair(i, h);
        if (grid[N - h][i] == 'W') white[pw++] = make_pair(i, h);
      }
      p = h;
    }
    for (int i = 0; i < pb; ++i) {
      int hb = black[i].second;
      int ib = black[i].first;
      for (int j = 0; j < pw; ++j) {
        int hw = white[j].second;
        int iw = white[j].first;
        uint64_t t = H;
        DecH(t, hb);
        IncH(t, hb - 1);
        DecH(t, hw);
        IncH(t, hw - 1);
        int g = Get(t);
        dp[s] = min(dp[s], dp[g] + abs(w[N - hb][ib] - w[N - hw][iw]));
      }
    }
  }

  cout << dp.back() << "\n";
  return 0;
}
