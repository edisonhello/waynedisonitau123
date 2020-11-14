
#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

vector<pair<int, int>> rotate(const vector<pair<int, int>> &v) {
    int n = v.size();
    auto vv = v;
    for (auto i : v) vv.push_back(i);
    int i = 0, j = 1;
    while (i < n && j < n) {
        int k = 0;
        while (k < n && vv[i + k] == vv[j + k]) ++ k;
        if (vv[i + k] <= vv[j + k]) j += k + 1;
        else i += k + 1;
        if (i == j) ++j;
    }
    int pos = (i < n ? i : j);
    vector<pair<int, int>> r;
    for (int i = pos, j = 0; j < n; ++i, ++j) {
        r.push_back(vv[i]);
    }
    return r;
}

vector<int> g[200005];
int dp[200005][2];
int n, m;

void dfs(int now, int pa) {
    dp[now][0] = 0;
    dp[now][1] = 1;
    for (int i : g[now]) if (i != pa && i >= n) {
        dfs(i, now);
        dp[now][0] += dp[i][1];
        dp[now][1] += min(dp[i][0], dp[i][1]);
    }
}

int dp2[200005][2];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n + m; ++i) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 0; i < n; ++i) {
        dfs(i, -1);
        // cerr << "dp[" << i << "] 0 1 = " << dp[i][0] << ' ' << dp[i][1] << endl;
    }

    int mn = INT_MAX;

    memset(dp2, 0x3f, sizeof(dp2));
    dp2[0][1] = dp[0][1];

    for (int i = 1; i < n; ++i) {
        dp2[i][0] = dp2[i - 1][1] + dp[i][0];
        dp2[i][1] = min(dp2[i - 1][0], dp2[i - 1][1]) + dp[i][1];
    }

    mn = min(dp2[n - 1][0], dp2[n - 1][1]);

    memset(dp2, 0x3f, sizeof(dp2));
    dp2[0][0] = 0 + dp[0][0];

    for (int i = 1; i < n; ++i) {
        dp2[i][0] = dp2[i - 1][1] + dp[i][0];
        dp2[i][1] = min(dp2[i - 1][0], dp2[i - 1][1]) + dp[i][1];
    }

    mn = min(mn, dp2[n - 1][1]);

    cout << mn << endl;

}
