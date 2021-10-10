#include <bits/stdc++.h>
using namespace std;

long long fmul(long long b, long long n, long long m) {
  long long a = 0;
  while (n) {
    if (n & 1) (a += b) %= m;
    (b += b) %= m;
    n >>= 1;
  }
  return a;
}

long long fpow(long long b, long long n, long long m) {
  long long a = 1;
  while (n) {
    if (n & 1) a = fmul(a, b, m);
    b = fmul(b, b, m);
    n >>= 1;
  }
  return a;
}

map<long long, int> cnt;

vector<long long> chk = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
bool IsPrime(long long n) {
  auto Check = [&](long long a, long long u, long long n, int t) {
    a = fpow(a, u, n);
    if (a == 0 || a == 1 || a == n - 1) return true;
    for (int i = 0; i < t; ++i) {
      a = fmul(a, a, n);
      if (a == 1) return false;
      if (a == n - 1) return true;
    }
    return false;
  };
  if (n < 2) return false;
  if (n % 2 == 0) return n == 2;
  long long u = n - 1;
  int t = 0;
  for (; !(u & 1); u >>= 1, ++t)
    ;
  for (long long i : chk) {
    if (!Check(i, u, n, t)) return false;
  }
  return true;
}

void Rho(long long n) {
  if (n == 1) return;
  if (IsPrime(n)) return ++cnt[n], void();
  if (n % 2 == 0) return Rho(n / 2), ++cnt[2], void();
  long long x = 2, y = 2, d = 1, p = 1;
  auto f = [&](auto x, auto n, int p) { return (fmul(x, x, n) + p) % n; };
  while (true) {
    if (d != n && d != 1) {
      Rho(n / d);
      Rho(d);
      return;
    }
    if (d == n) ++p;
    x = f(x, n, p);
    y = f(f(y, n, p), n, p);
    d = __gcd(abs(x - y), n);
  }
}

int sg[1005];

int main() {
  sg[0] = 0;
  sg[1] = 1;
  set<int> st;
  for (int len = 2; len <= 1000; ++len) {
    st.clear();
    for (int del = 1; del <= len; ++del) {
      for (int lef = 0; lef <= len - del; ++lef) {
        int ri = len - del - lef;
        st.insert(sg[lef] ^ sg[ri]);
        // if (sg[lef] != 0 && sg[ri] != 0)
        //   sg[len] = 0;
        // else {
        //   int ano = sg[lef] ^ sg[ri];
        //   if (ano == 0)
        //     sg[len] = 1;
        //   else if (ano == 1)
        //     sg[len] = 2;
        //   else
        //     sg[len] = 1;
        // }
      }
    }
    for (int i = 0; ; ++i) {
      if (!st.count(i)) {
        sg[len] = i;
        // cerr << "sg " << len << " = " << i << endl;
        break;
      }
    }
  }

  int n;
  cin >> n;
  vector<long long> a(n);
  for (int i = 0; i < n; ++i) cin >> a[i];

  vector<set<long long>> fac(n);
  for (int i = 0; i < n; ++i) {
    cnt.clear();
    Rho(a[i]);
    for (auto [p, c] : cnt) {
      fac[i].insert(p);
    }
  }

  int val = 0;
  for (int i = 0; i < n; ++i) {
    while (fac[i].size()) {
      long long x = *fac[i].begin();
      int j;
      for (j = i; j < n; ++j) {
        if (!fac[j].count(x)) break;
        fac[j].erase(x);
      }

      int len = j - i;
      val ^= sg[len];
    }
  }

  cout << (val ? "First" : "Second") << endl;
}

