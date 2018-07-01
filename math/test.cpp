#include <bits/stdc++.h>
using namespace std;

// n < 4759123141     chk = [2, 7, 61]
// n < 1122004669633  chk = [2, 13, 23, 1662803]
// n < 2^64           chk = [2, 325, 9375, 28178, 450775, 9780504, 1795265022]
//
vector<long long> chk = { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 };

long long fmul(long long a, long long n, long long mod) {
    long long ret = 0;
    for (; n; n >>= 1) {
        if (n & 1) (ret += a) %= mod;
        (a += a) %= mod;
    }
    return ret;
}

long long fpow(long long a, long long n, long long mod) {
    long long ret = 1LL;
    for (; n; n >>= 1) {
        if (n & 1) ret = fmul(ret, a, mod);
        a = fmul(a, a, mod);
    }
    return ret;
}
bool check(long long a, long long u, long long n, int t) {
    a = fpow(a, u, n);
    if (a == 0) return true;
    if (a == 1 || a == n - 1) return true;
    for (int i = 0; i < t; ++i) {
        a = fmul(a, a, n);
        if (a == 1) return false;
        if (a == n - 1) return true;
    }
    return false;
}
bool is_prime(long long n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    long long u = n - 1; int t = 0;
    for (; u & 1; u >>= 1, ++t);
    for (long long i : chk) {
        if (!check(i, u, n, t)) return false;
    }
    return true;
}

int main() {
    int t; cin >> t; while (t--) {
        long long x; cin >> x;
        if (is_prime(x)) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}
