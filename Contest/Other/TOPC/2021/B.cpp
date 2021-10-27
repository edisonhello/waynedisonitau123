#include <bits/stdc++.h>
using namespace std;

int main() {
  constexpr int kC = 1'000'000;
  vector<int> sum(kC + 1);
  for (int i = 1; i <= kC; ++i) {
    for (int j = i + i; j <= kC; j += i) {
      sum[j] += i;
    }
  }
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    if (sum[n] > n) cout << "abundant\n";
    else if (sum[n] == n) cout << "perfect\n";
    else cout << "deficient\n";
  }
}
