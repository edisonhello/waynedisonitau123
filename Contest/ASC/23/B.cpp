#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
vector<int> g[maxn], r[maxn];
int dep[maxn], s[maxn];

void dfs(int x, int p) {
    dep[x] = (p == 0 ? 0 : dep[p] + 1);
    for (int u : g[x]) {
        if (u == p) continue;
        dfs(u, x);
    }
    for (int u : r[x]) {
        if (dep[u] > dep[x]) continue;
        ++s[x];
        --s[u];
    }
}

void dfs2(int x, int p) {
    for (int u : g[x]) {
        if (u == p) continue;
        dfs2(u, x);
        s[x] += s[u];
    }
}

int main() {
#ifndef LOCAL
    freopen("diversion.in", "r", stdin);
    freopen("diversion.out", "w", stdout);
#endif
    int n, m; scanf("%d %d", &n, &m);
    vector<pair<int, int>> ed;
    for (int i = 0; i < m; ++i) {
        int x, y, d; scanf("%d %d %d", &x, &y, &d);
        if (d == 1) {
            g[x].push_back(y);
            g[y].push_back(x);
        } else {
            r[x].push_back(y);
            r[y].push_back(x);
        }
    }
    dfs(1, 0);
    dfs2(1, 0);
    int ans = 0;
    for (int i = 2; i <= n; ++i) if (s[i] == 1) ++ans;
    printf("%d\n", ans);
    return 0;
}
