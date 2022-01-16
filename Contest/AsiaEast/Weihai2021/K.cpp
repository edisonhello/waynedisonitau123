#include <bits/stdc++.h>
using namespace std;

int pw(int b, int n, int mod) {
  int a = 1;
  while (n) {
    if (n & 1) a = 1ll * a * b % mod;
    b = 1ll * b * b % mod;
    n >>= 1;
  }
  return a;
}

int inv(int x, int mod) {
  return pw(x, mod - 2, mod);
}

void solve(int n) {
  vector<int> oc(n);

  for (int i = 1; i <= n - 1; ++i) {
    int ii = inv(i, n);

    if (ii < i) oc[i] = oc[ii];
    else oc[i] = pw(i, (n - 1) / 2, n) == 1;
  }

  for (int i = 1; i <= n - 1; ++i) {
    cout << oc[i] << ' ';
  }
  cout << endl;
}

int main() {
  int n;
  cin >> n;
  solve(n);
}

