#include <bits/stdc++.h>
using namespace std;

long long fpow(long long b, long long n, long long m) {
  long long a = 1;
  while (n) {
    if (n & 1) a = (__int128)a * b % m;
    b = (__int128)b * b % m;
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
      a = (__int128)a * a % n;
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
  auto f = [&](auto x, auto n, int p) { return ((__int128)x * x % n + p) % n; };
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

// int sg[1005];

vector<int> primes;
int np[1000006];

int main() {
  for (int i = 2; i <= 1000000; ++i) {
    if (np[i]) continue;
    primes.push_back(i);
    for (long long j = 1ll * i * i; j <= 1000000; j += i) {
      np[j] = 1;
    }
  }

  int n;
  cin >> n;
  vector<long long> a(n);
  for (int i = 0; i < n; ++i) cin >> a[i];

  vector<set<long long>> fac(n);
  set<long long> morep;

  for (int i = 0; i < n; ++i) {
    for (int p : primes) {
      if (a[i] % p == 0) {
        while (a[i] % p == 0) a[i] /= p;
        fac[i].insert(p);
      }
    }
    if (a[i] != 1) {
      if (IsPrime(a[i])) {
        fac[i].insert(a[i]);
        morep.insert(a[i]);
        a[i] = 1;
      } else {
        int x = sqrt(a[i]);
        for (int xx = x - 1; xx <= x + 1; ++xx) {
          if (1ll * xx * xx == a[i]) {
            a[i] = 1;
            fac[i].insert(xx);
            morep.insert(xx);
            break;
          }
        }
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (a[i] == 1 || a[j] == 1) continue;
      long long g = __gcd(a[i], a[j]);
      // if (g != a[i] || g != a[j]) 
      //   morep.insert(g);
      if (IsPrime(g)) morep.insert(g);
    }
  }

  // sort(morep.begin(), morep.end());
  // morep.resize(unique(morep.begin(), morep.end()) - morep.begin());

  for (int i = 0; i < n; ++i) {
    for (long long p : morep) {
      if (a[i] % p == 0) {
        while (a[i] % p == 0) a[i] /= p;
        fac[i].insert(p);
      }
    }

    if (a[i] != 1) {
      if (IsPrime(a[i])) {
        fac[i].insert(a[i]);
      }
      a[i] = 1;
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
      val ^= len;
    }
  }

  cout << (val ? "First" : "Second") << endl;
}
