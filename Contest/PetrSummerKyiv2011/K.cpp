#include <bits/stdc++.h>
using namespace std;

long long mul(long long b, long long n, long long mod, long long a = 0) {
    b %= mod;
    while (n) {
        if (n & 1) a = (a + b) % mod;
        b = (b + b) % mod; n >>= 1;
    } return a;
}

long long pw(long long b, long long n, long long mod, long long a = 1) {
    b %= mod;
    while (n) {
        if (n & 1) a = mul(a, b, mod);
        b = mul(b, b, mod); n >>= 1;
    } return a;
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("zeroes.in", "r", stdin);
    freopen("zeroes.out", "w", stdout);
#endif
    long long k, p; cin >> k >> p;
    if (p == 1) {
        cout << 0 << endl;
        exit(0);
    }
    long long ans = (pw(10, k - 1, p) * ((k - 1) % p) % p + k % p - (pw(10, k - 1, 9 * p) + 9 * p - 1) / 9) % p;
    ans = (ans % p + p) % p;
    cout << ans << endl;

}
