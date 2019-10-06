#include <bits/stdc++.h>
using namespace std;

const int maxn = 2000 + 5;
vector<pair<int, int>> g[maxn];
int s[maxn], to[maxn], dep[maxn], cc[maxn];
vector<long long> vec;

void dfs(int x, int p) {
    dep[x] = 0;
    to[x] = -1;

    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i].first, w = g[x][i].second;
        if (u == p) continue;
        dfs(u, x);
        cc[u] = dep[u] + w;
        dep[x] = max(dep[x], cc[u]);
        if (to[x] == -1 || cc[u]> cc[to[x]]) to[x] = u;
    }
}

void dfs2(int x, int p, int d, int z) {
    if (to[x] == -1) vec.emplace_back(1LL * d * z);
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i].first, w = g[x][i].second;
        if (u == p) continue;
        if (u == to[x]) dfs2(u, x, d + w, z);
        else dfs2(u, x, w, z);
    }
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        --u, --v;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    for (int i = 0; i < n; ++i) scanf("%d", &s[i]);

    for (int i = 0; i < n; ++i) {
        dfs(i, -1);
        dfs2(i, -1, 0, s[i]);
    }

    sort(vec.begin(), vec.end(), greater<long long>());
    // for (int j : vec) printf("%d ", j); puts("");
    long long ans = 0;
    for (int i = 0; i < min(m, (int)vec.size()); ++i) ans += vec[i];
    printf("%lld\n", ans);
    return 0;
}
