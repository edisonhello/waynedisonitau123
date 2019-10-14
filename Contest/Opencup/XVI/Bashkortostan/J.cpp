#include <bits/stdc++.h>
using namespace std;

const int maxn = 100 + 5;
int a[maxn], b[maxn];
bitset<1000001> fr[maxn];

int main() {
    int n; scanf("%d", &n);
    int p; scanf("%d", &p);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    int q; scanf("%d", &q);
    for (int i = 1; i <= n; ++i) scanf("%d", &b[i]);

    vector<pair<int, int>> dp(p + 1, make_pair(1e9, -1e9));
    dp[0] = make_pair(0, 0);
    for (int i = 1; i <= n; ++i) {
        vector<pair<int, int>> cdp(dp.begin(), dp.end());
        for (int j = 0; j <= p; ++j) {
            int nxt = min(p, j + a[i]);
            cdp[nxt].first = min(cdp[nxt].first, dp[j].first + b[i]);
            cdp[nxt].second = max(cdp[nxt].second, dp[j].second + b[i]);
        }
        dp.swap(cdp);
    }
    int x = -1, y = -1;
    for (int i = 0; i < p; ++i) {
        if (dp[i].second >= q) {
            x = i;
            y = -1;
        }
    }
    if (dp[p].first < q) {
        x = -1;
        y = dp[p].first;
    }
    if (x == -1 && y == -1) {
        puts("YES");
        return 0;
    }
    puts("NO");
    if (x == -1) {
        for (int i = 1; i <= n; ++i) swap(a[i], b[i]);
        swap(x, y);
        swap(p, q);
    }
    {
        vector<int> dp(x + 1, -1e9);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            vector<int> cdp(x + 1, -1e9);
            for (int j = 0; j <= x; ++j) {
                cdp[j] = dp[j];
                fr[i][j] = 0;
                if (j >= a[i] && dp[j - a[i]] + b[i] > cdp[j]) {
                    cdp[j] = dp[j - a[i]] + b[i];
                    fr[i][j] = 1;
                }
            }
            dp.swap(cdp);
        }
    }
    int z = x;
    vector<int> ans;
    for (int i = n; i >= 1; --i) {
        ans.push_back((int)fr[i][z]);
        if (fr[i][z]) z -= a[i];
    }
    while (!ans.empty()) {
        printf("%d", ans.back());
        ans.pop_back();
    }
    return 0;
}
