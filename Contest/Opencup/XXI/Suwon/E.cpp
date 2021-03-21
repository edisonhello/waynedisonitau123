#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

int pw(int b, int n) {
    int a = 1;
    while (n) {
        if (n & 1) a = 1ll * a * b % mod;
        b = 1ll * b * b % mod; n >>= 1;
    }
    return a;
}

int inv(int x) {
    return pw(x, mod - 2);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, q; cin >> n >> q;
    vector<int> a(n + 1), c(n + 1);
    for (int i = 1; i < n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> c[i];
    vector<int> prea(n + 1, 0);
    for (int i = 1; i <= n; ++i) prea[i] = prea[i - 1] + a[i];
    vector<int> f(n + 1, 0);
    for (int i = 1; i <= n; ++i) f[i] = 1ll * a[i] * inv(prea[i]) % mod;

    vector<int> pp(n + 1, 0);
    for (int i = 1; i <= n; ++i) pp[i] = 1ll * f[i] * c[i] % mod;
    vector<int> prepp(n + 1, 0);
    for (int i = 1; i <= n; ++i) (prepp[i] = prepp[i - 1] + pp[i]) >= mod ? prepp[i] -= mod : 0;

    vector<int> term1(n + 1, 0);
    term1[2] = 1ll * (1 - f[2] + mod) * (1 + mod - pw(1 + mod - f[1], 2)) % mod * c[1] % mod;
    for (int i = 3; i <= n; ++i) {
        int prev = term1[i - 1];

        int part2 = 1ll * prev * inv(1 + mod - f[i - 1]) % mod;
        int newpart2 = 1ll * part2 * (1 + mod - pw(f[i - 1], 2)) % mod;

        term1[i] = 1ll * newpart2 * (1 + mod - f[i]) % mod;
        term1[i] += 1ll * (1 + mod - f[i]) * (1 + mod - pw(1 + mod - f[i - 1], 2)) % mod * c[i - 1] % mod;
        if (term1[i] >= mod) term1[i] -= mod;
    }

    while (q--) {
        int u, v; cin >> u >> v;
        if (u == v) {
            cout << 0 << '\n';
            continue;
        }
        if (u > v) swap(u, v);

        int ans = c[u] + c[v];
        if (ans >= mod) ans -= mod;

        ans += 2ll * (prepp[v - 1] + mod - prepp[u]) % mod;
        if (ans >= mod) ans -= mod;

        ans += 2ll * term1[u] % mod;
        if (ans >= mod) ans -= mod;

        cout << ans << '\n';
    }
}

