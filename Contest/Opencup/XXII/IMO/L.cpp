#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 2000000 + 1;
constexpr int kC = 5;
int dp[kN][kC * 2 + 1][kC * 2 + 1];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    string s, t;
    cin >> s >> t;
    constexpr int kP = 998244353;
    dp[0][kC][kC] = 1;
    int N = s.size();
    s = "." + s;
    t = "." + t;

    auto Get = [&](int i, int j, int k) -> int {
      int dj = j - i;
      int dk = k - i / 2;
      if (dj < -kC || dj > kC || dk < -kC || dk > kC) {
        return 0;
      } else {
        return dp[i][dj][dk];
      }
    };

    for (int i = 1; i <= N; ++i) {
      for (int dj = -kC; dj <= kC; ++dj) {
        for (int dk = -kC; dk <= kC; ++dk) {
          int j = i + dj;
          int k = i / 2 + dk;
          if (j > N || j < 0 || k < 0) {
            continue;
          }
          for (char c = 'A'; c <= 'C'; ++c) {
            if (s[i] == '?' || s[i] == c || t[j] == '?' || t[j] == c) {
              int s_mask = 0;
              for (int pi = i - 1; pi >= max(0, i - kC); --pi) {
                int t_mask = 0;
                for (int pj = j - 1; pj >= max(0, j - kC); --pj) {
                  dp[i][dj][dk] += Get(pi, pj, k - 1);
                  dp[i][dj][dk] %= kP;
                }
                if (s[pi] != '?') {
                  s_mask |= (1 << (s[pi] - 'A'));
                }
              }
            }
          }
        }
      }
    }
  }
}
