#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int64_t> A(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
  }
  int64_t x;
  cin >> x;
  sort(A.rbegin(), A.rend());
  int64_t ans = 0;
  for (int s = 0; s < (1 << (N - 1)); ++s) {
    int64_t y = x;
    for (int i = 0; i < N - 1; ++i) {
      if (s >> i & 1) {
        y %= A[i];
      }
    }
    y %= A[N - 1];
    ans = max(ans, y);
  }
  cout << ans << "\n";
}
