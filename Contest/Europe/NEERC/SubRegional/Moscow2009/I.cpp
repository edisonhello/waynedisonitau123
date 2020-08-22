#include <bits/stdc++.h>
using namespace std;

const int maxn = 1 << 23;

int res[maxn], aux[maxn], a[maxn], sz;

void db(int t, int p, int n, int k) {
  if (t > n) {
    if (n % p == 0) {
      for (int i = 1; i <= p; ++i) res[sz++] = aux[i];
    }
  } else {
    aux[t] = aux[t - p];
    db(t + 1, p, n, k);
    for (int i = aux[t - p] + 1; i < k; ++i) {
      aux[t] = i;
      db(t + 1, t, n, k);
    }
  }
}

int main() {
  freopen("infinite.in", "r", stdin);
  freopen("infinite.out", "w", stdout);

  int n; cin >> n;
  int k = 2;

  db(1, 1, n, k);

  for (int i = 0; i < sz; ++i) cout << res[i];
  for (int i = 0; i < n - 1; ++i) cout << res[i];
  cout << endl;
}
