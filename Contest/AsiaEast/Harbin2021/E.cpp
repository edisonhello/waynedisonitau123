#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    int N;
    cin >> N;
    vector<int> a(N);
    int x = 0;
    for (int i = 0; i < N; ++i) {
      cin >> a[i];
      x = max(x, a[i]);
    }
    if (x == 0) {
      cout << "1\n";
      continue;
    }
    int g = 0;
    for (int i = 0; i + 1 < N; ++i) {
      int diff = abs(2 * a[i] - a[i + 1]);
      g = __gcd(g, diff);
    }
    if (g == 0 || g <= x) {
      cout << "-1\n";
    } else {
      cout << g << "\n";
    }
  }
}

