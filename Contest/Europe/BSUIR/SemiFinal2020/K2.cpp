#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  int64_t res = accumulate(a.begin(), a.end(), 0LL);
  int64_t sum = res;
  int x = 0;
  if (k == 0) {
    cout << 0 << "\n";
    return 0;
  }
  for (int p = 0; p < m; ++p) {
    vector<int64_t> bit(p);
    int cnt = 0;
    int64_t cur = sum;
    int z = (1 << p);
    for (int i = 0; i < n; ++i) {
      if (a[i] >> p & 1) {
        continue; 
      }
      cur -= a[i] & ((1 << (p + 1)) - 1);
      cur += (1 << p);
      cnt++;
      for (int j = 0; j < p; ++j) {
        if (!(a[i] >> j & 1)) bit[j]++;
      }
    }
    vector<int> ord(p);
    iota(ord.begin(), ord.end(), 0);
    vector<int64_t> cost(p);
    for (int i = 0; i < p; ++i) cost[i] = 1LL * (1 << i) * (bit[i] - (cnt - bit[i]));
    for (int i = 0; i < p; ++i) cur += 1LL * (1 << i) * (cnt - bit[i]);
    sort(ord.begin(), ord.end(), [&](int i, int j) {
      return cost[i] > cost[j];
    });
    for (int i = 0; i < min((int)ord.size(), k - 1); ++i) {
      if (cost[ord[i]] <= 0) break;
      cur += cost[ord[i]];
      z ^= (1 << ord[i]);
    }
    if (cur > res) {
      res = cur;
      x = z;
    } else if (cur == res) {
      x = min(x, z);
    }
  }
  cout << x << "\n";
}
