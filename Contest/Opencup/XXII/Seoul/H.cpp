#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  vector<int> h(N);
  for (int i = 0; i < N; ++i) {
    cin >> h[i];
  }
  int g = 0;
  int p = -1;
  int ans = 1;
  constexpr int kP = 1'000'000'000 + 7;
  for (int i = 0; i < N; ++i) {
    if (h[i] > g) {
      g = h[i];
      if (p != -1) {
        ans = 1LL * ans * (i - p + 1) % kP;
      }
      p = i;
    }
  }
  cout << ans << "\n";
  return 0;
}
