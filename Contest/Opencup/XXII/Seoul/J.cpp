#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  int64_t K;
  cin >> N >> K;
  vector<vector<int>> A(N, vector<int>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> A[i][j];
    }
  }

  constexpr int64_t kInf = 1'000'000'000'000'000;
  auto Get = [&](const vector<int>& vec) {
    int64_t s = 0, ms = 0, mss = -kInf;
    for (int u : vec) {
      s += u;
      mss = max(mss, s - ms);
      ms = min(ms, s);
    }
    int64_t suff = -kInf;
    s = 0;
    for (int i = vec.size() - 1; i >= 0; --i) {
      s += vec[i];
      suff = max(suff, s);
    }
    return make_pair(mss, suff);
  };

  // cerr << "solve tx = " << tx << " ty = " << ty << endl;
  vector<vector<pair<int64_t, int64_t>>> top(N), bot(N);
  // cerr << "top:" << endl;
  for (int s = 0; s < (1 << (N - 1)); ++s) {
    vector<int> vec(N);
    vec[0] = A[0][0];
    int x = 0, y = 0;
    for (int i = 0; i < N - 1; ++i) {
      if (s >> i & 1) {
        x++;
      } else {
        y++;
      }
      vec[i + 1] = A[x][y];
    }
    top[x].push_back(Get(vec));
  }
  // cerr << "bot:" << endl;
  for (int s = 0; s < (1 << (N - 1)); ++s) {
    vector<int> vec(N);
    vec[0] = A[N - 1][N - 1];
    int x = N - 1, y = N - 1;
    for (int i = 0; i < N - 1; ++i) {
      if (s >> i & 1) {
        x--;
      } else {
        y--;
      }
      vec[i + 1] = A[x][y];
    }
    vec.pop_back();
    bot[x].push_back(Get(vec));
  }

  auto Solve = [&](int tx) {
    int64_t ans = 0;
    {
      // top = bot = K
      vector<int64_t> top_k, bot_k;
      for (auto p : top[tx]) {
        if (p.first == K) {
          top_k.push_back(p.second);
        }
      }
      for (auto p : bot[tx]) {
        if (p.first == K) {
          bot_k.push_back(p.second);
        }
      }
      sort(top_k.begin(), top_k.end());
      sort(bot_k.begin(), bot_k.end());
      int i = top_k.size() - 1;
      for (int64_t b : bot_k) {
        while (i >= 0 && b + top_k[i] > K) {
          i--;
        }
        ans += i + 1;
      }
    }
    {
      // top = K
      vector<int64_t> top_k, bot_k;
      for (auto p : top[tx]) {
        if (p.first == K) {
          top_k.push_back(p.second);
        }
      }
      for (auto p : bot[tx]) {
        if (p.first < K) {
          bot_k.push_back(p.second);
        }
      }
      sort(top_k.begin(), top_k.end());
      sort(bot_k.begin(), bot_k.end());
      int i = top_k.size() - 1;
      for (int64_t b : bot_k) {
        while (i >= 0 && b + top_k[i] > K) {
          i--;
        }
        ans += i + 1;
      }
    }
    {
      // bot = K
      vector<int64_t> top_k, bot_k;
      for (auto p : top[tx]) {
        if (p.first < K) {
          top_k.push_back(p.second);
        }
      }
      for (auto p : bot[tx]) {
        if (p.first == K) {
          bot_k.push_back(p.second);
        }
      }
      sort(top_k.begin(), top_k.end());
      sort(bot_k.begin(), bot_k.end());
      int i = top_k.size() - 1;
      for (int64_t b : bot_k) {
        while (i >= 0 && b + top_k[i] > K) {
          i--;
        }
        ans += i + 1;
      }
    }
    {
      // top < K, bot < K
      vector<int64_t> top_k, bot_k;
      for (auto p : top[tx]) {
        if (p.first < K) {
          top_k.push_back(p.second);
        }
      }
      for (auto p : bot[tx]) {
        if (p.first < K) {
          bot_k.push_back(p.second);
        }
      }
      sort(top_k.begin(), top_k.end());
      for (int64_t b : bot_k) {
        int64_t t = K - b;
        ans += upper_bound(top_k.begin(), top_k.end(), t) -
               lower_bound(top_k.begin(), top_k.end(), t);
      }
    }
    // cerr << "res = " << ans << endl;
    return ans;
  };

  int64_t ans = 0;
  for (int x = 0; x < N; ++x) {
    for (int y = 0; y < N; ++y) {
      if (x + y == N - 1) {
        ans += Solve(x);
      }
    }
  }
  cout << ans << "\n";
  return 0;
}
