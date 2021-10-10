#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N, K, P;
  cin >> N >> K >> P;
  vector<int> A(N), C(N);
  for (int i = 0; i < N; ++i) cin >> A[i];
  for (int i = 0; i < N; ++i) cin >> C[i];

  constexpr int64_t kInf = 1'000'000'000'000'000'000;
  auto Check = [&](int64_t cost) {
    vector<vector<pair<int64_t, int>>> dp(N + 1, vector<pair<int64_t, int>>(N + 1, make_pair(-kInf, 0)));
    dp[0][0] = make_pair(0, 0);
    for (int i = 0; i < N; ++i) {
      for (int combo = 0; combo <= N; ++combo) {
        if (dp[i][combo].first == -kInf) continue;
        if (combo > 0) {
          dp[i + 1][0] = max(dp[i + 1][0], make_pair(dp[i][combo].first + P,
                                                   dp[i][combo].second));
        } else {
          dp[i + 1][0] =
              max(dp[i + 1][0], dp[i][0]);
        }
        if (combo + 1 <= N) {
          auto v = make_pair(dp[i][combo].first + (int64_t)1LL * C[combo] * A[i],
                             dp[i][combo].second + 1);
          v.first += cost;
          dp[i + 1][combo + 1] = max(dp[i + 1][combo + 1], v);
        }
      }
    }
    pair<int64_t, int> res = make_pair(-kInf, 0);
    for (int i = 0; i <= N; ++i) {
      auto v = dp[N][i];
      if (i > 0) v.first += P;
      res = max(res, v);
    }
    res.second = res.second;
    return res;
  };

  auto Get = [&](int K) -> int64_t {
    int64_t cost = -20'000'000'000;
    for (int bit = 40; bit >= 0; --bit) {
      auto v = Check(cost + (1LL << bit));
      if (v.second == K) {
        return v.first - (cost + (1LL << bit)) * K;
      }
      if (v.second < K) cost += (1LL << bit);
    }
    auto v = Check(cost);
    cerr << "cost = " << cost << " v first " << v.first << endl;
    cerr << "K = " << K << " v second " << v.second << endl;
    return v.first - cost * K;
  };

  int l = 0, r = K;
  while (r - l > 5) {
    int ml = l + (l + r) / 3;
    int mr = r - (l + r) / 3;
    if (Get(ml) > Get(mr)) l = ml;
    else r = mr;
  }

  int64_t res = -kInf;
  for (int i = l; i <= r; ++i) res = max(res, Get(i));
  cout << res << "\n";

  return 0;
}

