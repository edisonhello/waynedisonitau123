#include <bits/stdc++.h>
using namespace std;

string Solve() {
  int N;
  int64_t K;
  cin >> N >> K;

  if (N == 1) {
    if (K == 1) return "0";
    if (K == 2) return "1";
    return "NOT FOUND!";
  }

  array<int, 2> fr = {((N + 1) / 2 + 1) / 2, (N / 2 + 1) / 2};
  array<int, 2> cnt = {(N + 1) / 2, N / 2};
  vector<int> opp(N);
  vector<vector<int>> id(2);
  for (int i = 0; i < N; ++i) id[i % 2].push_back(i);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0, k = id[i].size() - 1; j < id[i].size(); ++j, k--) {
      opp[id[i][j]] = id[i][k];
    }
  }

  constexpr int64_t kInf = 4'000'000'000'000'000'000;

  auto Add = [&](int64_t a, int64_t b) {
    return min(a + b, kInf);
  };

  auto Mul = [&](int64_t a, int64_t b) {
    if (a > kInf / b) return kInf;
    return min(a * b, kInf); 
  };

  vector<int64_t> pw(2 * N + 1, 1);
  for (int i = 1; i <= 2 * N; ++i) {
    pw[i] = Add(pw[i - 1], pw[i - 1]);
  }

  K--;
  string ans(N, ' ');
  array<bool, 2> ok = {true, true};
  for (int i = 0; i < N; ++i) {
    assert(cnt[i % 2] > 0);
    // cout << "K = " << K << endl;
    // cout << "ans = " << ans << endl;
    if (fr[i % 2] > 0) {
      int A = fr[i % 2] - 1, B = fr[(i + 1) % 2];
      int C = cnt[i % 2] - 1, D = cnt[(i + 1) % 2];
      int64_t ways = pw[A + D] + pw[B + C] - pw[A + B];
      ways = min(ways, kInf);
      if (ways <= K) {
        ans[i] = '1';
        K -= ways;
      } else {
        ans[i] = '0';
      }
      fr[i % 2]--;
      cnt[i % 2]--;
    } else {
      // cout << "ha" << endl;
      assert(ans[opp[i]] != ' ');
      if (!ok[(i + 1) % 2]) {
        ans[i] = ans[opp[i]];
      } else {
        if (!ok[i % 2]) {
          int A = fr[(i + 1) % 2];
          int B = cnt[i % 2] - 1;
          int64_t ways = pw[A + B];
          if (ways <= K) {
            ans[i] = '1';
            K -= ways;
          } else {
            ans[i] = '0';
          }
        } else {
          if (ans[opp[i]] == '0') {
            if (ok[(i + 1) % 2]) {
              int A = cnt[(i + 1) % 2];
              int B = cnt[i % 2] - 1;
              int C = fr[(i + 1) % 2];
              // cout << "A = " << A << " B = " << B << endl;
              int64_t ways = pw[A] + pw[B + C] - pw[C];
              ways = min(ways, kInf);
              if (ways <= K) {
                K -= ways;
                ans[i] = '1';
                ok[i % 2] = false;
              } else {
                ans[i] = '0';
              }
            } else {
              int A = fr[(i + 1) % 2];
              int B = cnt[i % 2] - 1;
              if (pw[A + B] <= K) {
                K -= pw[A + B];
                ans[i] = '1';
                ok[i % 2] = false;
              } else {
                ans[i] = '0';
              }
            }
          } else {
            if (ok[(i + 1) % 2]) {
              int A = cnt[i % 2] - 1;
              int B = fr[(i + 1) % 2];
              if (pw[A + B] <= K) {
                K -= pw[A + B];
                ans[i] = '1';
              } else {
                ans[i] = '0';
                ok[i % 2] = false;
              }
            } else {
              ans[i] = '1';
            }
          }
        }
      }
      cnt[i % 2]--;
    }
  }
  if (K > 0) return "NOT FOUND!";
  return ans;
}

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; ++i) {
    cout << "Case #" << i + 1 << ": ";
    cout << Solve() << "\n";
  }
}
