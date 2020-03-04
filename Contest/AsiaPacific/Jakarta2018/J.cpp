#include <bits/stdc++.h>
using namespace std;

const int maxn = 20;
int dp[maxn][1 << maxn];
string s[maxn];
vector<pair<string, int>> z[maxn];

int main() {
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
        for (int j = 1; j < (1 << s[i].size()); ++j) {
            string t = "";
            for (int k = 0; k < s[i].size(); ++k) {
                if (j >> k & 1) t += s[i][k];
            }
            z[i].emplace_back(t, j);
        }
        sort(z[i].begin(), z[i].end());
    }
    for (int i = 0; i < maxn; ++i) for (int j = 0; j < (1 << maxn); ++j) dp[i][j] = -1e9;
    for (int i = 0; i < (1 << s[1].size()); ++i) dp[1][i] = __builtin_popcount(i);
    for (int i = 2; i <= n; ++i) {
        int pmax = -1e9;
        int p = 0;
        for (int j = 0; j < (int)z[i].size(); ++j) {
            while (p < (int)z[i - 1].size() && z[i][j].first > z[i - 1][p].first) {
                pmax = max(pmax, dp[i - 1][z[i - 1][p].second]);
                ++p;
            }
            dp[i][z[i][j].second] = pmax + __builtin_popcount(z[i][j].second);
        }
    }
    int ans = -1e9;
    for (int i = 1; i < (1 << s[n].size()); ++i) ans = max(ans, dp[n][i]);
    if (ans < 0) ans = -1;
    cout << ans << endl;
    return 0;
}
