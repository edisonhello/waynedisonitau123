#include <bits/stdc++.h>
using namespace std;

int mod = 1e9 + 7;

int fpow(int a, int n) {
    int r = 1;
    for (; n; n >>= 1) {
        if (n & 1) r = r * 1ll * a % mod;
        a = a * 1ll * a % mod;
    }
    return r;
}

int main() {
    int n, m, c; cin >> n >> m >> c;
    int x = fpow(c, n * n);
    int ans = 0;
    for (int k = 1; k <= m; ++k) {
        int g = __gcd(m, k);
        (ans += fpow(x, g)) %= mod;
    }
    ans = ans * 1ll * fpow(m, mod - 2) % mod;
    cout << ans << endl;
}
