#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007;

long long pw(long long b, long long n, long long m, long long a = 1) {
    while (n) {
        if (n & 1) a = a * b % m;
        b = b * b % m; n >>= 1;
    }
    return a;
}

long long inv(long long x) {
    return pw(x, mod - 2, mod);
}

long long go(long long n) {
    long long a = -n * n % mod * (n + 1) % mod * (n + 1) % mod * inv(4) % mod;
    long long b = (n + 4) * n % mod * (n + 1) % mod * (2 * n % mod + 1) % mod * inv(6) % mod;
    long long c = -(3 * n % mod + 5) * n % mod * (n + 1) % mod * inv(2) % mod;
    long long d = (2 * n + 2) * n % mod;
    return ((a + b + c + d) % mod + mod) % mod;
}

int main() {
    int t; scanf("%d", &t); for (int T = 1; T <= t; ++T) {
        long long n, m; scanf("%lld%lld", &n, &m);
        n %= mod; m %= mod;
        printf("Case %d: ", T);
        printf("%lld\n", go(n) * go(m) % mod * inv(4) % mod);
    }
}
