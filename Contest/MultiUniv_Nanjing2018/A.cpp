#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
const int mod = 998244353;
int fc[maxn], iv[maxn];

int fpow(int x, int n) {
    int res = 1;
    while (n > 0) {
        if (n & 1)
            res = res * 1ll * x % mod;
        x = x * 1ll * x % mod;
        n >>= 1;
    }
    return res;
}

int comb(int n, int k) {
    if (n < k || k < 0) return 0;
    return fc[n] * 1ll * iv[k] % mod * iv[n - k] % mod;
}

int main() {
    int t; scanf("%d", &t);
    fc[0] = iv[0] = 1;
    for (int i = 1; i < maxn; ++i) {
        fc[i] = fc[i - 1] * 1ll * i % mod;
        iv[i] = fpow(fc[i], mod - 2);
    }

    while (t--) {
        int n, m, k; scanf("%d%d%d", &n, &m, &k);
        int ans = 0;
        for (int i = 0, cf = 1; i <= min(k / n, m); ++i, cf = mod - cf) {
            ans += comb(m, i) * 1ll * cf % mod * comb(m + k - i * n - 1, m - 1) % mod;
            ans %= mod;
        }

        printf("%d\n", ans);
    }
}
