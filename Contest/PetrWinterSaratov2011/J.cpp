#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
vector<pair<int, int>> g[maxn];
vector<pair<int, int>> child[maxn];
int k[maxn], t[maxn], pos[maxn];
long long s[maxn], z[maxn], dp[maxn];

void dfs(int x, int p) {
    z[x] = k[x];
    s[x] = t[x];
    long long sum = 0;
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i].first, d = g[x][i].second;
        if (u == p) continue;
        dfs(u, x);
        z[x] += z[u];
        s[x] += s[u] + d + d; 
        sum += dp[u] + d * z[u];
        child[x].emplace_back(u, d);
    }
    sort(child[x].begin(), child[x].end(), [&](pair<int, int> i, pair<int, int> j) {
        long long vi = z[i.first] * (s[j.first] + 2 * j.second);
        long long vj = z[j.first] * (s[i.first] + 2 * i.second);
        return vi > vj;
    });
    long long delay = 0, pk = 0;
    for (int i = 0; i < (int)child[x].size(); ++i) 
        pk += z[child[x][i].first];
    long long pt = 0;
    for (int i = 0; i < (int)child[x].size(); ++i) {
        sum += pt * z[child[x][i].first];
        pt += s[child[x][i].first] + 2 * child[x][i].second;
    }
    // printf("sum = %lld\n", sum);
    dp[x] = 1e18;
    // printf("pk = %lld\n", pk);
    // printf("s = %lld\n", s[x]);
    for (int i = 0; i <= (int)child[x].size(); ++i) {
        long long v = (delay + t[x]) * k[x] + t[x] * pk;
        // printf("pk + k[x] = %lld\n", pk + k[x]);
        // printf("v = %lld\n", v);
        if (v < dp[x]) {
            dp[x] = v;
            pos[x] = i;
        }
        if (i < (int)child[x].size()) {
            delay += s[child[x][i].first] + 2 * child[x][i].second;
            pk -= z[child[x][i].first];
        }
    }
    dp[x] += sum;
    // printf("dp[%d] = %lld\n", x, dp[x]);
}

void dfs2(int x) {
    for (int i = 0; i < pos[x]; ++i) {
        printf("M %d\n", child[x][i].first + 1);
        dfs2(child[x][i].first);
        printf("M %d\n", x + 1);
    }
    printf("P %d\n", x + 1);
    for (int i = pos[x]; i < (int)child[x].size(); ++i) {
        printf("M %d\n", child[x][i].first + 1);
        dfs2(child[x][i].first);
        printf("M %d\n", x + 1);
    }
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("beetles.in", "r", stdin);
    freopen("beetles.out", "w", stdout);
#endif
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &t[i]);
    for (int i = 0; i < n; ++i) scanf("%d", &k[i]);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, d; scanf("%d%d%d", &u, &v, &d);
        --u, --v;
        g[u].emplace_back(v, d);
        g[v].emplace_back(u, d);
    }
    dfs(0, -1);
    printf("%lld\n", dp[0]);
    dfs2(0);
}
