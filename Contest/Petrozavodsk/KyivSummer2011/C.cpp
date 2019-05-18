#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
vector<int> g[maxn], sub[maxn];
int dp[maxn], ans[maxn];

void dfs(int x, int p) {
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i];
        if (u == p) continue;
        dfs(u, x);
        dp[x] = max(dp[x], dp[u] + 1);
    }
}

void dfs2(int x, int p, int f) {
    multiset<int> ms;
    if (p >= 0) {
        sub[x].push_back(f + 1);
        ms.insert(f + 1);
    }
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i];
        if (u == p) continue;
        sub[x].push_back(dp[u] + 1);
        ms.insert(dp[u] + 1);
    }
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i];
        if (u == p) continue;
        ms.erase(ms.find(dp[u] + 1));
        int z = !ms.empty() ? *ms.rbegin() : 0;
        dfs2(u, x, z);
        ms.insert(dp[u] + 1);
    }
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("amoeba.in", "r", stdin);
    freopen("amoeba.out", "w", stdout);
#endif
    int n, a, b; scanf("%d%d%d", &n, &a, &b);
    for (int i = 0; i < n - 1; ++i) {
        int x, y; scanf("%d%d", &x, &y);
        --x, --y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs(0, -1);
    dfs2(0, -1, -1);
    for (int i = 0; i < n; ++i) {
        sort(sub[i].begin(), sub[i].end());
        reverse(sub[i].begin(), sub[i].end());
        for (int j = 0; j < (int)sub[i].size(); ++j)
            ans[sub[i][j]] = max(ans[sub[i][j]], j + 1);
    }
    /* for (int i = 0; i < n; ++i) {
        printf("i = %d: \n", i + 1);
        for (int j = 0; j < (int)sub[i].size(); ++j)
            printf("%d ", sub[i][j]);
        puts("");
    } */
    for (int i = n - 1; i >= 0; --i)
        ans[i] = max(ans[i], ans[i + 1]);
    for (int i = a; i <= b; ++i)
        printf("%d\n", ans[i]);
    puts("");

}
