#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007;

long long pw(long long b, long long n, long long a = 1) {
    while (n) {
        if (n & 1) a = a * b % mod;
        b = b * b % mod; n >>= 1;
    }
    return a;
}

long long f(int x, long long n) {
    if (x == 1) return 1;
    if (x == 2) return (pw(2, n) - 2 + mod) % mod;
    if (x == 3) return ((pw(3, n) - 3ll * pw(2, n) + 3) % mod + mod) % mod;
    if (x == 4) return ((pw(4, n) - 4ll * pw(3, n) + 6ll * pw(2, n) - 4) % mod + mod) % mod;
    if (x == 5) return ((pw(5, n) - 5ll * pw(4, n) + 10ll * pw(3, n) - 10ll * pw(2, n) + 5) % mod + mod) % mod;
    assert(0);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        long long n; int m; cin >> n >> m;
        if (m == 2) {
            cout << 2 << '\n';
        } else if (m == 3) {
            cout << 6ll * f(2, n) % mod << '\n';
        } else if (m == 4) {
            cout << (24ll * f(3, n) + 12ll * f(2, n)) % mod << '\n';
        } else if (m == 5) {
            cout << (120ll * f(4, n) + 120ll * f(3, n)) % mod << '\n';
        } else if (m == 6) {
            cout << (720ll * f(5, n) + 1080ll * f(4, n) + 720ll * f(3, n)) % mod << '\n';
        }
    }
}

