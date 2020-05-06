#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        p[i]--;
    }
    constexpr int kMod = 1'000'000'000 + 7;

    vector<vector<int>> dp(n, vector<int>(n + 1));
    for (int i = 0; i < n; ++i) {
        dp[i][1] = 1;
    }

    vector<int> fenw(n + 1);

    auto Update = [&](int p, int v) {
        for (int i = p + 1; i <= n; i += i & -i) {
            fenw[i] += v;
            fenw[i] >= kMod ? fenw[i] -= kMod : 0;
        }
    };

    auto Query = [&](int p) {
        int res = 0;
        for (int i = p + 1; i > 0; i -= i & -i) {
            res += fenw[i];
            res >= kMod ? res -= kMod : 0;
        }
        return res;
    };

    vector<int> pos(n);
    for (int i = 0; i < n; ++i) pos[p[i]] = i;

    for (int k = 2; k <= n; ++k) {
        fill(fenw.begin(), fenw.end(), 0);
        for (int i = 0; i < n; ++i) {
            dp[i][k] = Query(pos[i]);
            Update(pos[i], dp[i][k - 1]);
        }
    }
    int res = 0;
    vector<int> pw(n + 1, 1);
    vector<vector<int>> cnk(n + 1, vector<int>(n + 1));

    for (int i = 0; i <= n; ++i) {
        cnk[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            cnk[i][j] = (cnk[i - 1][j] + cnk[i - 1][j - 1]) % kMod;
        }
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            pw[i] = 1LL * pw[i] * i % kMod;
        }
    }

    auto Solve = [&](int k) {
        int res = 0;
        for (int i = 0; i <= k; ++i) {
            int add = i % 2 == 0 ? pw[k - i] : kMod - pw[k - i];
            add = 1LL * add * cnk[k][i] % kMod;
            (res += add) >= kMod ? res -= kMod : 0;
        }
        return res;
    };

    for (int k = 1; k <= n; ++k) {
        int ways = 0;
        for (int i = 0; i < n; ++i) {
            ways += dp[i][k];
            ways >= kMod ? ways -= kMod : 0;
        }
        res += 1LL * ways * Solve(k) % kMod;
        res >= kMod ? res -= kMod : 0;
    }
    cout << res << "\n";
}

