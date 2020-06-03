#include <bits/stdc++.h>
using namespace std;

int lr[100005][2];

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  for (int i = 0; i < n; ++i) cin >> lr[i][0] >> lr[i][1];

  auto ok = [&] (int a) -> bool {
    for (int i = 0; i < n; ++i) {
      int l = lr[i][0];
      if (l + a - 1 > lr[i][1]) continue;
      if (i + a - 1 >= n) continue;
      if (lr[i + a - 1][0] > l) continue;
      if (l + a - 1 > lr[i + a - 1][1]) continue;
      return 1;
    }
    for (int i = 0; i < n; ++i) {
      int l = lr[i][0];
      if (l + a - 1 > lr[i][1]) continue;
      if (i - a + 1 < 0) continue;
      if (lr[i - a + 1][0] > l) continue;
      if (l + a - 1 > lr[i - a + 1][1]) continue;
      return 1;
    }
    return 0;
  };

  int L = 1, R = n;
  while (L < R) {
    int M = (L + R + 1) >> 1;
    if (ok(M)) L = M;
    else R = M - 1;
  }
  cout << L << endl;
}
