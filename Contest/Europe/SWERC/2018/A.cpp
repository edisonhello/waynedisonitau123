#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k;
  cin >> n >> k;
  vector<int> state(n + 1);
  int cnt = 0, res = 0;
  for (int i = 0; i < k; ++i) {
    int x;
    cin >> x;
    for (int j = x; j <= n; j += x) {
      cnt -= state[j];
      state[j] ^= 1;
      cnt += state[j];
    }
    res = max(res, cnt);
  }
  cout << res << "\n";
}
