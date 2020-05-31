#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> c(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> c[i][j];
            c[i][j]--;
        }
    }
    constexpr int kMod = 1'000'000'000 + 7;
    vector<vector<int>> comb(n + 1, vector<int>(n + 1));
    for (int i = 0; i <= n; ++i) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % kMod;
        }
    }
    vector<bool> vis(n);
    vector<int> cnt(300);
    int res = 0;
    for (int it = 0; it < n; ++it) {
        vector<int> add(300);
        for (int j = 0, pv = 0; j <= it; ++j) {
            int pd = 1;
            for (int i = 0; i < 300; ++i) {
                (add[i] += comb[cnt[i]][j]) %= kMod;
                pd = 1LL * pd * add[i] % kMod;
            }
            (pd += kMod - pv) %= kMod;
            res += 1LL * pd * (j + 1) % kMod;
            res %= kMod;
            (pv += pd) %= kMod;
        }
        int x = -1, color = -1;
        for (int i = 0; i < n; ++i) {
            if (vis[i]) continue;
            int z = -1;
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                if (vis[j]) continue;
                if (z == -1) {
                    z = c[i][j];
                } else {
                    if (z != c[i][j]) z = -2;
                }
            }
            if (z == -2) continue;
            x = i;
            color = z;
            break;
        }
        assert(x != -1);
        vis[x] = true;
        if (color != -1) cnt[color]++;
    }

    cout << res << "\n";
}

