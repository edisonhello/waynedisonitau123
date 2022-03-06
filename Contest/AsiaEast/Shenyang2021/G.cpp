#pragma GCC optimize("O3", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 1000 + 5;
int16_t dp[1 << 20][20];
int16_t to[1 << 20][20];
int16_t len[1 << 20][20];
int16_t last[1 << 20];
int16_t cut[1 << 20][20];
int16_t prv[20];
int16_t cnt[20][kN + 1];
int16_t pos[20][kN + 1];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  string s;
  cin >> s;

  // cout << *min_element(s.begin(), s.end()) << "\n";
  // cout << *max_element(s.begin(), s.end()) << "\n";
  // if (*min_element(s.begin(), s.end()) == *max_element(s.begin(), s.end())) {
  //   cout << string('a', N) << "\n";
  //   return 0;
  // }

  memset(cut, -1, sizeof(cut));
  memset(pos, -1, sizeof(pos));
  memset(prv, -1, sizeof(prv));

  for (int i = 0; i < N; ++i) {
    if (prv[s[i] - 'a'] != -1) {
      for (int j = prv[s[i] - 'a'] + 1; j <= i; ++j) {
        pos[s[i] - 'a'][j] = prv[s[i] - 'a'];
      }
    }
    prv[s[i] - 'a'] = i;
    cnt[s[i] - 'a'][i]++;
  }
  // cerr << "here" << endl;
  for (int i = 0; i < 20; ++i) {
    for (int j = 0; j < N; ++j) {
      cnt[i][j + 1] += cnt[i][j];
    }
  }
  for (int i = 0; i < 20; ++i) {
    if (prv[i] != -1) {
      for (int j = prv[i] + 1; j <= N; ++j) {
        pos[i][j] = prv[i];
      }
    }
  }

  last[0] = N;
  for (int s = 1; s < (1 << 20); ++s) {
    for (int c = 0; c < 20; ++c) {
      if (s >> c & 1) {
        if (pos[c][last[s ^ (1 << c)]] != -1) {
          last[s] = max(last[s], pos[c][last[s ^ (1 << c)]]);
        }
      }
    }
  }
  for (int s = 0; s < (1 << 20); ++s) {
    for (int c = 0; c < 20; ++c) {
      if (s >> c & 1) {
        continue;
      }
      if (pos[c][last[s]] != -1) {
        cut[s][c] = pos[c][last[s]];
      }
    }
  }
  // cerr << "here" << endl;

  function<bool(int, int, int, int)> Compare = [&](int s1, int c1, int s2,
                                                   int c2) {
    while (true) {
      if (dp[s1][c1] == -1 && dp[s2][c2] == -1) {
        return false;
      }
      if (dp[s1][c1] != dp[s2][c2]) {
        return dp[s1][c1] > dp[s2][c2];
      }
      int x1 = to[s1][c1], x2 = to[s2][c2];
      s1 ^= (1 << x1);
      c1 = x1;
      s2 ^= (1 << x2);
      c2 = x2;
    }
  };

  memset(dp, -1, sizeof(dp));
  memset(to, -1, sizeof(to));

  for (int s = 0; s < (1 << 20); ++s) {
    for (int c = 0; c < 20; ++c) {
      if (s >> c & 1) {
        continue;
      }
      if (cut[s][c] == -1) {
        continue;
      }

      for (int d = 0; d < 20; ++d) {
        if (s >> d & 1) {
          int p = cnt[d][last[s ^ (1 << d)]] - cnt[d][cut[s][c]];
          if (len[s ^ (1 << d)][d] + 1 > len[s][c]) {
            len[s][c] = len[s ^ (1 << d)][d] + 1;
            dp[s][c] = p;
            to[s][c] = d;
          } else if (len[s ^ (1 << d)][d] + 1 == len[s][c] && p > dp[s][c]) {
            dp[s][c] = p;
            to[s][c] = d;
          } else if (len[s ^ (1 << d)][d] + 1 == len[s][c] && p == dp[s][c]) {
            if (Compare(s ^ (1 << d), d, s ^ (1 << to[s][c]), to[s][c])) {
              to[s][c] = d;
            }
          }
        }
      }
    }
  }
  int all = 0;
  for (char c : s) {
    all |= (1 << (c - 'a'));
  }
  int fs = -1, best = -1, ll = 0;
  for (int i = 0; i < 20; ++i) {
    int p = cnt[i][last[all ^ (1 << i)]];
    if (len[all ^ (1 << i)][i] > ll) {
      ll = len[all ^ (1 << i)][i];
      fs = p;
      best = i;
    } else if (len[all ^ (1 << i)][i] == ll && p > fs) {
      fs = p;
      best = i;
    } else if (len[all ^ (1 << i)][i] == ll && p == fs) {
      if (Compare(all ^ (1 << i), i, all ^ (1 << best), best)) {
        best = i;
      }
    }
  }
  vector<int> ans = {fs};
  int mask = all ^ (1 << best), cur = best;
  while (mask > 0 && dp[mask][cur] > 0) {
    ans.push_back(dp[mask][cur]);
    int tc = to[mask][cur];
    mask = mask ^ (1 << to[mask][cur]);
    cur = tc;
  }
  char c = 'a' + ans.size() - 1;
  for (int u : ans) {
    for (int i = 0; i < u; ++i) cout << c;
    c--;
  }
  cout << "\n";
}
