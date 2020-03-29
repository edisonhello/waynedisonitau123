#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    int sum = 0;
    vector<int> cnt(31);
    vector<vector<int>> wh(31);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
        cnt[a[i]]++;
        wh[a[i]].push_back(i);
    }
    constexpr int kN = 4000 + 30 + 1;
    int up = (sum + 2) / 3 + 30;
    vector<vector<bitset<kN>>> dp(31, vector<bitset<kN>>(up + 1));
    dp[0][0].set(0);
    for (int i = 1; i <= 30; ++i) {
        for (int j = 0; j <= up; ++j) {
            for (int k = 0; j - k * i >= 0 && k <= cnt[i]; ++k) {
                int p = cnt[i] - k;
                bitset<kN> bs = dp[i - 1][j - k * i];
                for (int v = 0; (1 << v) <= p; ++v) {
                    bs |= bs << ((1 << v) * i);
                    p -= (1 << v);
                }
                if (p > 0) bs |= bs << (p * i);
                dp[i][j] |= bs;
            }
        }
    }
    int ans = sum + 1;
    int x = -1, y = -1;
    for (int i = 0; i <= up; ++i) {
        for (int j = 0; j <= up; ++j) {
            if (dp[30][i][j]) {
                int a = max(max(i, j), sum - i - j); 
                int b = min(min(i, j), sum - i - j); 
                if (a - b < ans) {
                    ans = a - b;
                    x = i;
                    y = j;
                }
            }
        }
    }
    cout << ans << "\n";
    vector<vector<int>> res(3, vector<int>(31));
    for (int i = 30; i > 0; --i) {
        bool ok = false;
        for (int k = 0; x - k * i >= 0 && k <= cnt[i]; ++k) {
            int p = cnt[i] - k;
            // bitset<kN> bs = dp[i - 1][x - k * i];
            vector<bitset<kN>> bs = {dp[i - 1][x - k * i]};
            vector<int> r = {0};
            for (int v = 0; (1 << v) <= p; ++v) {
                bs.push_back(bs.back() | (bs.back() << ((1 << v) * i)));
                // bs |= bs << ((1 << v) * i);
                r.push_back((1 << v));
                p -= (1 << v);
            }
            if (p > 0) {
                bs.push_back(bs.back() | bs.back() << (p * i));
                r.push_back(p);
            }
            if (bs.back()[y]) {
                int cnt = 0;
                for (int z = bs.size() - 1; z > 0; --z) {
                    if (y >= r[z] * i && bs[z - 1][y - r[z] * i]) {
                        cnt += r[z];
                        y -= r[z] * i;
                    }
                }
                res[0][i] = k;
                res[1][i] = cnt;
                x -= k * i;
                ok = true;
                break;
            }
        }
        assert(ok);
    }
    for (int i = 1; i <= 30; ++i) {
        res[2][i] = cnt[i] - res[0][i] - res[1][i];
    }
    for (int i = 0; i < 3; ++i) {
        vector<int> p;
        for (int j = 1; j <= 30; ++j) {
            while (res[i][j]--) {
                p.push_back(wh[j].back());
                wh[j].pop_back();
            }
        }
        sort(p.begin(), p.end());
        cout << p.size();
        for (int u : p) cout << " " << u + 1;
        cout << "\n";
    }
}

