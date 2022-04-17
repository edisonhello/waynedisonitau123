#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;

  vector<int> a(N);
  vector<int> cnt(1000000 + 1);
  for (int i = 0; i < N; ++i) {
    cin >> a[i];
    cnt[a[i]] = 1;
  }
  int ans = 0;
  for (int i = 0; i < N; ++i) {
    for (int t = 1; t * t <= a[i]; ++t) {
      if (a[i] % t == 0) {
        int p = -1;
        if (a[i] / t >= t && (a[i] / t - t) % 2 == 0 && cnt[(a[i] / t - t) / 2]) {
          p = (a[i] / t - t) / 2;
          ans++;
        }
        if (a[i] != t * t) {
          if (t >= a[i] / t && (t - a[i] / t) % 2 == 0 && cnt[(t - a[i] / t) / 2]) {
            if ((t - a[i] / t) / 2 != p) {
              ans++;
            }
          }
        }
      }
    }
  }
  cout << ans << "\n";
  return 0;
}
