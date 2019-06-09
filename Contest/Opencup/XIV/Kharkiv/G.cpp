#include <bits/stdc++.h>
using namespace std;

const int maxn = 100;
long long a[maxn];

long long fpow(long long a, long long n, long long p) {
    long long res = 1;
    while (n > 0) {
        if (n & 1) (res *= a) %= p;
        (a *= a) %= p;
        n >>= 1;
    }
    return res;
}

long long fmul(long long a, long long b, long long p) {
    long long res = 0;
    while (b > 0) {
        if (b & 1) (res += a) %= p;
        (a += a) %= p;
        b >>= 1;
    }
    return res;
}

long long inv(long long a, long long p) {
    return fpow(a, p - 2, p);
}

int main() {
    int p, n; cin >> p >> n;
    for (int i = n; i >= 0; --i) {
        cin >> a[i];
    }
    long long p2 = p * 1ll * p;
    for (int i = 0; i <= n; ++i) {
        a[i] += p2;
        a[i] %= p2;
    }
    long long ans = 1e18;
    for (long long b = 0; b < p; ++b) {
        long long base = 1;
        long long sum = 0;
        for (int i = 0; i <= n; ++i) {
            sum += (long long)((__int128)(a[i]) * base % p2);
            sum %= p2;
            base = base * b % p2;
        }

        if (sum % p == 0) {
            if (sum == 0) {
                ans = min(ans, b);
                continue;
            }
            long long base2 = 1;
            long long sum2 = 0;
            for (int i = 1; i <= n; ++i) {
                sum2 += a[i] % p * i % p * base2 % p;
                sum2 %= p;
                base2 = base2 * b % p;
            }
            if (sum2 == 0) continue;
            long long r = sum / p;
            long long a = (p - r) * inv(sum2, p) % p;
            ans = min(ans, a * p + b);
        }
    }

    if (ans >= p2) ans = -1;
    cout << ans << endl;
    return 0;
}
