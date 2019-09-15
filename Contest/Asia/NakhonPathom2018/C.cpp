#include <bits/stdc++.h>
using namespace std;

const int maxn = 5000 + 5;
int h[maxn], dp[maxn];
vector<int> g[maxn];

int dfs(int x) {
    if (dp[x] != -1) return dp[x];
    dp[x] = 0;
    for (int u : g[x]) dp[x] = max(dp[x], dfs(u) + 1);
    return dp[x];
}

int main() {
    int n, w; scanf("%d%d", &n, &w);
    for (int i = 0; i < n; ++i) scanf("%d", &h[i]);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (h[i] < h[j] && abs(i - j) <= w) g[i].push_back(j);
        }
    }
    int ans = 0;
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < n; ++i) ans = max(ans, dfs(i));
    printf("%d\n", ans);
}
