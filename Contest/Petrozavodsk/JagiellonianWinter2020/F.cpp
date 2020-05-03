#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

struct Frac {
    long long u, d;
    Frac() : u(0), d(1) {}
    Frac(long long _u, long long _d) : u(_u), d(_d) {
        long long g = __gcd(u, d);
        u /= g, d /= g;
    }
};

Frac operator+ (const Frac &a, const Frac &b) {
    return Frac(a.u * b.d + b.u * a.d, a.d * b.d);
}
Frac operator/ (const Frac &a, const Frac &b) {
    return Frac(a.u * b.d, a.d * b.u);
}

bool operator< (const Frac &a, const Frac &b) {
    return (__int128)a.u * b.d < (__int128)a.d * b.u;
}

long long cnt[20][256];

int CalcInv(vector<int> &v) {
    int n = v.size(); 
    int x = 0;
    for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j)
        x += (v[i] > v[j]);
    return x;
}

void solve() {
    int n, a, b, c, d; cin >> n >> a >> b >> c >> d;
    while (d--) {
        vector<int> v(n);
        for (int i = 0; i < n; ++i) cin >> v[i], --v[i];
        int ni = CalcInv(v);
        Frac cost(min(ni * a, b + (n * (n - 1) / 2 - ni) * a), 1);

        vector<pair<int, int>> costs;
        for (int i = 0; i < 256; ++i) if (cnt[n][i]) {
            costs.emplace_back(min(a * i, b + (n * (n - 1) / 2 - i) * a), i);
            // cerr << "costs inv c " << i << " cost " << costs.back().first << endl;
        }

        sort(costs.begin(), costs.end());

        long long sumcost = 0;
        long long tot = 1;
        for (int i = 2; i <= n; ++i) tot *= i;
        long long inside = 0;

        for (auto [t, c_inv] : costs) {
            inside += cnt[n][c_inv];
            sumcost += cnt[n][c_inv] * t;
            
            // Frac tmp = (Frac(c, 1) + Frac(sumcost, inside)) / Frac(inside, tot);
            Frac tmp(1ll * c * tot + sumcost, inside);
            if (tmp < cost) cost = tmp;

            // cerr << "bound t = " << t << " in c_inv " << c_inv << " tmp = " << tmp.u << "/" << tmp.d << endl;
        }

        cout << cost.u << "/" << cost.d << '\n';
    }
}

long long dp[1 << 16][256];
void init() {
    for (int n = 1; n <= 16; ++n) {
        memset(dp, 0, sizeof(dp));
        dp[(1 << n) - 1][0] = 1;
        for (int z = (1 << n) - 1; z > 0; --z) {
            for (int y = 0; y < 256; ++y) if (dp[z][y]) {
                for (int zz = z; zz; ) {
                    int i = __lg(zz & -zz);
                    zz ^= 1 << i;
                    int ni = __builtin_popcount(z & ((1 << i) - 1));
                    dp[z ^ (1 << i)][y + ni] += dp[z][y];
                }
            }
        }

        for (int y = 0; y < 256; ++y) cnt[n][y] = dp[0][y];
    }
}

int main() {
    init();

    ios_base::sync_with_stdio(0); cin.tie(0);
    int z; cin >> z; while (z--) solve();
}

