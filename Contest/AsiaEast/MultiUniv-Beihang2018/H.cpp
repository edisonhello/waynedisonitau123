#include <bits/stdc++.h>
using namespace std;

void Solve() {
    int n;
    cin >> n; 
    string s;
    cin >> s;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = s[i] - '0';
    }
    vector<int> dp(10);
    vector<int> lis1(n);
    vector<int> lis2(n);
    vector<vector<int>> ch(n, vector<int>(10));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= a[i]; ++j) lis1[i] = max(lis1[i], dp[j] + 1);
        dp[a[i]] = max(dp[a[i]], lis1[i]);
        for (int j = 0; j < 10; ++j) ch[i][j] = dp[j];
        for (int j = 1; j < 10; ++j) ch[i][j] = max(ch[i][j], ch[i][j - 1]);
    }
    fill(dp.begin(), dp.end(), 0);
    for (int i = n - 1; i >= 0; --i) {
        for (int j = a[i]; j < 10; ++j) lis2[i] = max(lis2[i], dp[j] + 1);
        dp[a[i]] = max(dp[a[i]], lis2[i]);
    }
    int res = 0;
    int l = -1, r = -1;
    for (int k = 0; k < 10; ++k) {
        int g = 0;
        vector<vector<int>> dp(10, vector<int>(10, -1));
        vector<vector<int>> fr(10, vector<int>(10, -1));
        for (int i = n - 1; i >= 0; --i) {
            int v = g + 1;
            for (int d = 0; d < 10; ++d) {
                int r = -1, z = -1;
                for (int p = d; p <= a[i]; ++p) {
                    if (dp[p][d] != -1 && dp[p][d] + 1 > r) {
                        r = dp[p][d] + 1;
                        z = fr[p][d];
                    }
                }
                if (r > dp[a[i]][d]) {
                    dp[a[i]][d] = r;
                    fr[a[i]][d] = z;
                }
            }
            if (v > dp[a[i]][a[i]]) {
                dp[a[i]][a[i]] = v;
                fr[a[i]][a[i]] = i;
            }
            if (a[i] <= k) {
                for (int d = 0; d < 10; ++d) {
                    if (fr[a[i]][d] == -1) continue;
                    int v = dp[a[i]][d] + (i > 0 ? ch[i - 1][d] : 0);
                    if (v > res) {
                        res = v;
                        l = i;
                        r = fr[a[i]][d];
                    }
                }
            }
            if (a[i] >= k) g = max(g, lis2[i]);
        }
    }
    cout << res << " ";
    cout << l + 1 << " " << r + 1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) Solve();
}

