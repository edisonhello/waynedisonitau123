#include <bits/stdc++.h>
using namespace std;

const int maxn = 300 + 5;
int d[maxn][maxn], w[maxn][maxn], uf[maxn], fa[maxn][10], dep[maxn];
bool v[maxn], ed[maxn][maxn];
int ds[maxn];
vector<int> g[maxn];

int Find(int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
}

void Dfs(int x, int p) {
    fa[x][0] = p;
    dep[x] = ~p ? dep[p] + 1 : 0;
    for (int i = 1; (1 << i) <= dep[x]; ++i)
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    for (int u : g[x]) {
        if (u == p) continue;
        Dfs(u, x);
    }
}

int LCA(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    for (int i = 0; i < 10; ++i) {
        if ((dep[v] - dep[u]) >> i & 1)
            v = fa[v][i];
    }
    if (u == v) return u;
    for (int i = 9; i >= 0; --i) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        scanf("%d", &d[i][j]);
        if (d[i][j] == -1) d[i][j] = 1e9;
        w[i][j] = d[i][j];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) g[j].clear();
        for (int j = 0; j < n; ++j) memset(fa[j], -1, sizeof(fa[j]));
        memset(ed, false, sizeof(ed));
        for (int j = 0; j < n; ++j) ds[j] = 1e9;
        ds[i] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.emplace(0, i);
        memset(v, false, sizeof(v));
        while (!pq.empty()) {
            int x = pq.top().second; pq.pop();
            if (v[x]) continue;
            v[x] = true;
            for (int j = 0; j < n; ++j) {
                if (ds[j] > ds[x] + d[x][j]) {
                    ds[j] = ds[x] + d[x][j];
                    fa[j][0] = x;
                    pq.emplace(ds[j], j);
                }
            }
        }
        for (int j = 0; j < n; ++j) {
            if (fa[j][0] >= 0) {
                g[fa[j][0]].push_back(j);
                ed[fa[j][0]][j] = ed[j][fa[j][0]] = true;
            }
        }
        Dfs(i, -1);
        int ans = 1e9;
        for (int j = 0; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                if (v[j] && v[k] && LCA(j, k) == i && !ed[j][k]) {
                    ans = min(ans, ds[j] + ds[k] + d[j][k]);
                }
            }
        }
        if (ans > 5e8) ans = -1;
        printf("%d\n", ans);
    }
}
