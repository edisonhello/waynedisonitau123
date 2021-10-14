#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  cin >> T;
  while (T--) {
    int A, B;
    cin >> A >> B;
    int ans = A - 1;
    vector<int> D;
    for (int t = 1; ; t = B / (B / (t + 1))) {
      D.push_back(t);
      if (t == B) break;
    }
    reverse(D.begin(), D.end());
    int pv = 1;
    for (int u : D) {
      int L = pv, R = B / u;
      for (int t = 0; t <= 10; ++t) {
        if (L + t <= A && L + t <= R) {
          if (B % (L + t) != 0) {
            ans = min(ans, A - B + u * (L + t));
          }
        }
      }
      pv = R + 1;
    }
    for (int v = 1; v * v <= B; ++v) {
      if (B % v == 0) {
        if (v <= A) {
          ans = min(ans, A - v);
        }
        if (B / v <= A) {
          ans = min(ans, A - B / v);
        }
      }
    }
    cout << ans << "\n";
  }
}
