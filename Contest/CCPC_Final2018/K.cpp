#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

template <typename T>
tuple<T, T, T> extgcd(T a, T b) {
    if (!b) return make_tuple(a, 1, 0);
    T d, x, y;
    tie(d, x, y) = extgcd(b, a % b);
    return make_tuple(d, y, x - (a / b) * y);
}

long long fmul(long long a, long long b, long long n) {
    b %= n, a %= n;
    long long res = 0;
    while (b > 0) {
        if (b & 1)
            (res += a) %= n;
        (a += a) %= n;
        b >>= 1;
    }
    return res;
}
long long fpow(long long c, long long d, long long n) {
    c %= n;
    long long res = 1;
    while (d > 0) {
        if (d & 1)
            (res *= c) %= n;
        (c *= c) %= n;
        d >>= 1;
    }
    return res;
}

long long inverse(long long x, long long p) {
    auto res = extgcd(x, p);
    return (get<1>(res) % p + p) % p;
}

int main() {
    int t; scanf("%d", &t);
    for (int tc = 1; tc <= t; ++tc) {
        printf("Case %d: ", tc);
        long long n, c; scanf("%lld%lld", &n, &c);
        int p, q;
        int k = sqrt(n);
        for (int i = k - (1 - k % 2); i >= 2; i -= 2) {
            if (n % i == 0) {
                p = i;
                q = n / i;
                break;
            }
        }


        long long m = (p - 1) * 1ll * (q - 1);
        long long e = (1 << 30) + 3;
        long long d = inverse(e, m);
        long long x = fpow(c, d, p);
        long long y = fpow(c, d, q);
        long long ans = fmul(fmul(x, q, n),  inverse(q, p), n) + fmul(fmul(y, p, n), inverse(p, q), n);
        // printf("%lld %lld %lld\n", x, y, ans);
        printf("%lld\n", ans % n);
    }
}
