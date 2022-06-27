#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, K;
  cin >> N >> K;
  vector<int64_t> A(N);
  int64_t mask = 0;
  constexpr int kP = 998244353;
  int ans = 0;
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
    int frees = 0;
    int one = 0;
    int fix = 0;
    for (int j = 0; j < K; ++j) {
      if (mask >> j & 1) {
        fix++;
      } else {
        if (A[i] >> j & 1) {
          one++;
        } else {
          frees++;
        }
      }
    }
    int ways = (((1LL << one) - 1) % kP) * ((1LL << frees) % kP) % kP;
    ans += 1LL * (i + 1) * ways % kP;
    ans %= kP;
    mask |= A[i];
  }
  cout << ans << "\n";
  return 0;
}
