#include <bits/stdc++.h>
using namespace std;
 
const int mod = 1000000007;
 
int a[(1 << 18) + 5];
int _fac[1000006], _ifac[1000006];
 
int pw(int b, int n, int m, int a = 1) {
    while (n) {
        if (n & 1) a = 1ll * a * b % m;
        b = 1ll * b * b % m; n >>= 1;
    } return a;
}
 
int inv(int x) {
    return pw(x, mod - 2, mod);
}
 
int fac(int x) {
    if (x < 0) return 0;
    return _fac[x];
}
int ifac(int x) {
    if (x < 0) return 0;
    return _ifac[x];
}
 
int f[20][(1 << 18) + 5];
 
int main() {
    _fac[0] = 1;
    for (int i = 1; i <= 1000000; ++i) _fac[i] = 1ll * _fac[i - 1] * i % mod;
    _ifac[1000000] = inv(_fac[1000000]);
    for (int i = 1000000 - 1; i >= 0; --i) _ifac[i] = 1ll * _ifac[i + 1] * (i + 1) % mod;
 
    ios_base::sync_with_stdio(0); cin.tie(0);
    int k; cin >> k;
    int n = 1 << k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
 
    for (int z = 0; z <= k; ++z) {
        for (int t = 1; t <= n; ++t) {
            f[z][t] = (f[z][t - 1] + 1ll * a[t] * fac(n - t) % mod * ifac(n - t - ((1 << z) - 1))) % mod;
            // cerr << "f[" << z << "][" << t << "] = " << f[z][t] << endl;
        }
    }
 
    int sum = 0;
    for (int i = 1; i <= n - 1; ++i) {
        int add = 0;
        for (int j = 0; j <= k; ++j) {
            add = (add + (1ll << j) * (f[j][n] - f[j][i] + mod) % mod * fac(n - i - (1 << j)) % mod * ifac(n - i - (1 << (j + 1)) + 1) % mod * fac(n - (1 << (j + 1))) % mod) % mod;
        }
        // cerr << "i = " << i << ", add = " << add << endl;
        sum = (sum + 1ll * add * a[i]) % mod;
    }
 
    sum = (sum * 1ll * ifac(n - 1)) % mod;
    cout << sum << endl;
}
