#include <bits/stdc++.h>
using namespace std;

const int kMod = 1'000'000'000 + 7;
const int kN = 100'000 + 5;
int a[30][30], b[30][30], c[30][30];
int fc[kN], iv[kN], pw[kN], qw[kN], dp[kN];

int fpow(int a, int n) {
    int res = 1;
    while (n > 0) {
        if (n & 1) res = 1LL * res * a % kMod;
        a = 1LL * a * a % kMod;
        n >>= 1;
    }
    return res;
}

int Choose(int n, int k) {
    return 1LL * fc[n] * iv[n - k] % kMod * iv[k] % kMod;
}

int Odd(int n) {
    return dp[n];
    /* int ans = 0;
    for (int i = 1; i <= n; i += 2) {
        int add = 1LL * Choose(n, i) * pw[i] % kMod * qw[n - i] % kMod;
        (ans += add) %= kMod;
    } */
    // printf("Odd n = %d ans = %d\n", n, ans);
    // return ans;
}

int Even(int n) {
    return kMod + 1 - dp[n];
    /* int ans = 0;
    for (int i = 0; i <= n; i += 2) {
        int add = 1LL * Choose(n, i) * pw[i] % kMod * qw[n - i] % kMod;
        (ans += add) %= kMod;
    } */
    // printf("Even n = %d ans = %d\n", n, ans);
    // return ans;
}

int main() {
    fc[0] = iv[0] = 1;
    for (int i = 1; i < kN; ++i) {
        fc[i] = 1LL * fc[i - 1] * i % kMod;
        iv[i] = fpow(fc[i], kMod - 2);
    }
    int n, p, q; scanf("%d%d%d", &n, &p, &q);
    p = 1LL * p * fpow(q, kMod - 2) % kMod;
    q = (kMod + 1 - p) % kMod;
    pw[0] = qw[0] = 1;
    for (int i = 1; i < kN; ++i) {
        pw[i] = 1LL * pw[i - 1] * p % kMod;
        qw[i] = 1LL * qw[i - 1] * q % kMod;
    }
    dp[0] = 0;
    for (int i = 1; i < kN; ++i) {
        dp[i] = 1LL * p * (kMod + 1 - dp[i - 1]) % kMod + 1LL * q * dp[i - 1] % kMod;
        if (dp[i] >= kMod) dp[i] -= kMod;
    }
    for (int i = 0; i < n; ++i) {
        int x; scanf("%d", &x);
        for (int j = 0; j < 30; ++j) {
            for (int k = 0; k < 30; ++k) {
                if ((x >> j & 1) && (x >> k & 1)) ++a[j][k];
                if ((x >> j & 1) && !(x >> k & 1)) ++b[j][k];
                if (!(x >> j & 1) && (x >> k & 1)) ++c[j][k];
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < 30; ++i) {
        int v = 1LL * (1 << i) * (1 << i) % kMod;
        (ans += 1LL * v * Odd(a[i][i]) % kMod) %= kMod;
        for (int j = i + 1; j < 30; ++j) {
            int p = 2LL * Odd(a[i][j]) * Even(b[i][j]) % kMod * Even(c[i][j]) % kMod + 
                    2LL * Even(a[i][j]) * Odd(b[i][j]) % kMod * Odd(c[i][j]) % kMod;

            if (p >= kMod) p -= kMod;
            ans += 1LL * (1 << i) * (1 << j) % kMod * p % kMod;
            if (ans >= kMod) ans -= kMod;
        }
    }
    printf("%d\n", ans);
    return 0;
}
