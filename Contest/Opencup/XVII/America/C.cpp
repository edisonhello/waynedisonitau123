#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> x(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }
    constexpr int kMod = 1'000'000'000 + 7;

    vector<vector<int>> dp1(n, vector<int>(n, -1));
    vector<vector<int>> dp2(n, vector<int>(n, -1));
    vector<vector<bool>> ok(n, vector<bool>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ok[i][j] = __gcd(x[i], x[j]) > 1;
        }
    }

    for (int i = 0; i < n; ++i) {
        dp1[i][(i + 1) % n] = 1;
        dp2[i][(i + 1) % n] = 1;
    }

    auto Between = [&](int l, int r, int x) {
        if (l < r) return x >= l && x <= r;
        return x >= l || x <= r;
    };

    for (int v = 2; v < n; ++v) {
        for (int i = 0; i < n; ++i) {
            int j = (i + v) % n;
            dp1[i][j] = 0;
            dp2[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                if (i == k || j == k) continue;
                if (!Between(i, j, k)) continue;
                if (ok[i][k]) {
                    dp1[i][j] += 1LL * dp1[i][k] * dp1[k][j] % kMod;
                    (dp1[i][j] >= kMod) ? dp1[i][j] -= kMod : 0;
                }
                if (ok[j][k]) {
                    dp2[i][j] += 1LL * dp2[i][k] * dp1[k][j] % kMod;
                    (dp2[i][j] >= kMod) ? dp2[i][j] -= kMod : 0;
                }
            }
            (dp1[i][j] += dp2[i][j]) >= kMod ? dp1[i][j] -= kMod : 0;
        }
    }

    int res = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            if (!ok[i][j]) continue;
            // int g = 1LL * Dfs1(Dfs1, Dfs2, i, j) * Dfs1(Dfs1, Dfs2, j, i) % kMod;
            int g = 1LL * dp1[i][j] * dp1[j][i] % kMod;
            (res += g) >= kMod ? res -= kMod : 0;
        }
    }

    auto fpow = [&](int a, int n) {
        int res = 1;
        while (n > 0) {
            if (n & 1) res = 1LL * res * a % kMod;
            a = 1LL * a * a % kMod;
            n >>= 1;
        }
        return res;
    };

    res = 1LL * res * fpow(2 * n - 2, kMod - 2) % kMod;
    cout << res << "\n";
}

