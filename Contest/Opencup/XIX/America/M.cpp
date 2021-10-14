#include <bits/stdc++.h>
using namespace std;

int main() {
  int M, N;
  cin >> M >> N;
  vector<int> p(1 << M);
  for (int i = 0; i < (1 << M); ++i) {
    cin >> p[i];
    p[i]--;
  }

  bool failed = false;
  vector<bool> used(N);

  auto DivideConquer = [&](auto self, int l, int r) -> int {
    if (r - l == 1) {
      return 0;
    }
    int m = (l + r) >> 1;
    bool eq = true;
    for (int i = l; i < m; ++i) {
      eq &= (p[i] == p[i + (r - m)]);
    }
    if (eq) {
      return 1 + self(self, l, m);
    } else {
      for (int i = l; i < m; ++i) used[p[i]] = true;
      for (int i = m; i < r; ++i) {
        if (used[p[i]]) {
          failed = true;
        }
      }
      for (int i = l; i < m; ++i) used[p[i]] = false;
      if (!failed) {
        return self(self, l, m) + self(self, m, r);
      } else {
        return 0;
      }
    }
  };

  int ans = DivideConquer(DivideConquer, 0, (1 << M));
  if (failed) {
    cout << 0 << "\n";
  } else {
    int res = 1;
    for (int i = 0; i < ans; ++i) {
      res = (res + res) % (1'000'000'000 + 7);
    }
    cout << res << "\n";
  }
}
