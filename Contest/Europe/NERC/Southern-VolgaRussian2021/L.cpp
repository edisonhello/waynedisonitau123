#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  vector<int> t(N);
  for (int i = 0; i < N; ++i) {
    cin >> t[i];
  }

  auto Check = [&](int k) {
    int add = 0;
    for (int i = 0; i < N; ++i) {
      int cur = t[i] + add;
      if (cur <= k) {
        add = 0;
        continue;
      }
      if ((cur + 1) / 2 > k) {
        return false;
      }
      int x = 0;
      for (int d = 20; d >= 0; --d) {
        if (x + (1 << d) <= k) {
          if ((cur - (x + (1 << d)) + 1) / 2 <= k - (x + (1 << d))) {
            x += (1 << d);
          }
        }
      }
      add = cur - x;
    }
    return add == 0;
  };

  int ans = *max_element(t.begin(), t.end());
  for (int d = 20; d >= 0; --d) {
    if (ans >= (1 << d)) {
      if (Check(ans - (1 << d))) {
        ans -= (1 << d);
      }
    }
  }
  cout << ans << "\n";
}
