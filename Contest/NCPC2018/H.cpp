#include <bits/stdc++.h>
using namespace std;

int len(unsigned long long x) {
    int res = 0;
    while (x) res++, x /= 10;
    return res;
}

const int mod = 1009;

int fpow(int x, unsigned long long n) {
    n %= (mod - 1);
    int r = 1;
    while (n) {
        if (n & 1) r = r * 1ll * x % mod;
        x = x * 1ll * x % mod;
        n >>= 1;
    }
    return r;
}

unsigned long long tpow(unsigned long long x, int n) {
    unsigned long long r = 1;
    while (n--) r *= x;
    return r;
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        unsigned long long n; scanf("%llu", &n);
        int l = len(n);
        int k = 0, ans = 0;
        for (int i = l - 1; i >= 0; --i) {
            unsigned long long a = tpow(10, i);
            unsigned long long b = -1;
            if (a * 1.0 * 10 - 1 < n) b = a * 10 - 1;
            else b = n;
            unsigned long long x = b - a + 1;
            int t = i + 1;
            int a10 = fpow(10, k + x % (mod - 1) * t % (mod - 1)) % mod * (a % mod) % mod;
            int an10 = fpow(10, k % (mod - 1)) * (b % mod) % mod;
            int p = fpow(10, k + t) * (fpow(10, (x - 1) % (mod - 1) * t % (mod - 1)) - 1 + mod) % mod;
            int q = (fpow(10, t) - 1 + mod) % mod;
            p = p * fpow(q, mod - 2) % mod;
            int d = (fpow(10, t) - 1 + mod) % mod;
            int sum = (a10 - an10 + p + mod) * fpow(d, mod - 2) % mod;
            ans = (ans + sum) % mod;
            k += t * (x % (mod - 1));
            k %= (mod - 1);
        }
        if (n % 2 == 1 && ans % 2 == 1 || n % 2 == 0 && ans % 2 == 0) {}
        else (ans += 1009) %= 2018;
        printf("%d\n", ans);
    }
}
