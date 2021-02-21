#include <bits/stdc++.h>
using namespace std;

#define int long long

const int mod = 998244353;
const int inv6 = 166374059;

int getpt(int a, int b) {
    return (1ll * a * a + 1ll * b * b) % mod;
}

int walk_10(int a, int b, int c, int d) {
    int off = getpt(c, d);
    if (a != c) {
        swap(a, b);
        swap(c, d);
    }

    assert(a == c);

    if (b > d) swap(b, d);
    c = d;

    long long v1 = 1ll * a * a % mod * (c - b + 1) % mod;
    long long v2 = 1ll * (c) * (c + 1) % mod * (2 * c + 1) % mod * inv6 % mod;
    long long v3 = 1ll * (b - 1) * (b) % mod * (2 * b - 1) % mod * inv6 % mod;
    return ((v1 + v2 - v3 - off) % mod + mod) % mod;
}

int f(int a, int b) {
    if (b < a) swap(a, b);
    long long v1 = 1ll * b * (b + 1) % mod * (2 * b + 1) % mod * inv6 % mod;
    long long v2 = 1ll * (a - 1) * a % mod * (2 * a - 1) % mod * inv6 % mod;
    return ((4ll * (v1 - v2 + mod) % mod - 1ll * a * a - 1ll * b * b) % mod + mod) % mod;
}

int getsum(int a, int b, int c, int d) {
    if (c < a) {
        swap(a, c);
        swap(b, d);
    }

    if (b >= d) {
        return (0ll + walk_10(a, b, a, d) + walk_10(d, a, d, c) + getpt(c, d)) % mod;
    }

    if (d <= c) swap(a, b), swap(c, d);

    if (d >= b && b >= c) {
        return (0ll + walk_10(c, d, c, b) + walk_10(b, c, b, a) + getpt(a, b)) % mod;
    }

    int x = max(a, b);
    return (0ll + walk_10(c, d, c, c) + walk_10(a, b, x, x) + f(c, x)) % mod;
}

int solve(int a, int b, int c, int d) {
    int sum = getsum(a, b, c, d);

    sum += 1ll * c * c % mod * d % mod * d % mod;
    if (sum >= mod) sum -= mod;
    sum -= 1ll * a * a % mod * b % mod * b % mod;
    if (sum < 0) sum += mod;
    sum -= 1ll * c * c % mod;
    if (sum < 0) sum += mod;
    sum -= 1ll * d * d % mod;
    if (sum < 0) sum += mod;

    return sum;
}

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int q; cin >> q; while (q--) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        cout << solve(a, b, c, d) << '\n';
    }
}

