#include <bits/stdc++.h>
#define int int64_t
using namespace std;

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while (T--) {
    int H, N;
    cin >> H >> N;
    vector<int> x(N), y(N);
    for (int i = 0; i < N; ++i) {
      cin >> x[i] >> y[i];
    }
    int M;
    cin >> M;
    x.resize(N + M);
    y.resize(N + M);
    for (int i = N; i < N + M; ++i) {
      cin >> x[i] >> y[i];
    }
    map<int, int> up;
    up[0] = 0;

    vector<int> event(N + M);
    iota(event.begin(), event.end(), 0);
    sort(event.begin(), event.end(), [&](int i, int j) { return x[i] < x[j]; });

    int H2 = 2 * H;
    for (int i : event) {
      int xp = x[i] % H2;
      // cout << "i = " << i << endl;
      if (i >= N) {
        if (up.find((y[i] - xp + H2) % H2) != up.end()) {
          int d = (y[i] - xp + H2) % H2;
          int e = (xp + d) % H2;
          if (e <= H) {
            up[(y[i] - xp + H2) % H2]++;
          }
        }
        if (up.find((H2 - y[i] - xp + H2) % H2) != up.end()) {
          int d = (H2 - y[i] - xp + H2) % H2;
          int e = (xp + d) % H2;
          if (e >= H) {
            up[(H2 - y[i] - xp + H2) % H2]++;
          }
        }
      } else {
        if (up.find((y[i] - xp + H2) % H2) != up.end()) {
          int d = (y[i] - xp + H2) % H2;
          int e = (xp + d) % H2;
          if (e <= H) {
            up[(y[i] - xp + H2 + H2 - 2 * y[i]) % H2] =
              max(up[(y[i] - xp + H2 + H2 - 2 * y[i]) % H2], up[(y[i] - xp + H2) % H2]);
          }
        }
        if (up.find((H2 - y[i] - xp + H2) % H2) != up.end()) {
          int d = (H2 - y[i] - xp + H2) % H2;
          int e = (xp + d) % H2;
          if (e >= H) {
            up[(H2 - y[i] - xp + 2 * y[i] + H2) % H2] = 
              max(up[(H2 - y[i] - xp + 2 * y[i] + H2) % H2],  up[(H2 - y[i] - xp + H2) % H2]);
          }
        }
      }
      // cout << "up" << endl;
      // for (auto [a, b] : up) {
      //   cout << a << ": " << b << endl;
      // }
    }

    int ans = 0;
    for (auto [a, b] : up) {
      ans = max(ans, b);
    }
    cout << ans << "\n";
  }
  return 0;
}

