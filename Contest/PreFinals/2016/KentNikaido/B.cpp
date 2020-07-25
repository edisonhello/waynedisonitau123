#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
int fac[2000006], ifac[2000006];

int pw(int b, int n) {
  int a = 1;
  while (n) {
    if (n & 1) a = 1ll * a * b % mod;
    b = 1ll * b * b % mod; n >>= 1;
  }
  return a;
}

int main() {
  fac[0] = 1;
  for (int i = 1; i <= 2000000; ++i) fac[i] = fac[i - 1] * 1ll * i % mod;
  ifac[2000000] = pw(fac[2000000], mod - 2);
  for (int i = 1999999; i >= 0; --i) ifac[i] = ifac[i + 1] *
}
