#include <bits/stdc++.h>
using namespace std;

const int kN = 2e5 + 5;
int x[kN], y[kN], uf[kN], deg[kN], gx[kN], gy[kN], dfn[kN], low[kN], tk;
bool used[kN], bg[kN];
vector<int> g[kN];

int Find(int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
}

void Merge(int x, int y) {
    uf[Find(x)] = Find(y);
}

void Dfs(int x, int p, int f) {
    dfn[x] = low[x] = tk++;
    for (int e : g[x]) {
        int u = gx[e] == x ? gy[e] : gx[e];
        if (u == p) continue;
        if (dfn[u] != -1) {
            low[x] = min(low[x], dfn[u]);
            continue;
        }
        Dfs(u, x, e);
        low[x] = min(low[x], low[u]);
    }
    if (low[x] == dfn[x] && f != -1) bg[f] = true;
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        vector<int> ds;
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &x[i], &y[i]);
            ds.push_back(x[i]);
            ds.push_back(y[i]);
        }

        sort(ds.begin(), ds.end());
        ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
        int m = ds.size();
        for (int i = 0; i < m; ++i) {
            uf[i] = i;
            deg[i] = 0;
            g[i].clear();
            dfn[i] = -1;
        }

        for (int i = 0; i < n; ++i) {
            int u = lower_bound(ds.begin(), ds.end(), x[i]) - ds.begin(); 
            int v = lower_bound(ds.begin(), ds.end(), y[i]) - ds.begin(); 
            Merge(u, v);
            gx[i] = u;
            gy[i] = v;
            ++deg[u];
            ++deg[v];
            g[u].push_back(i);
            g[v].push_back(i);
        }
        int ans = 0;
        vector<int> root;
        for (int i = 0; i < m; ++i) {
            if (Find(i) == i) root.push_back(i); 
        }
        if (root.size() == 1) {
            puts("0");
            continue;
        }
        for (int i = 0; i < m; ++i) used[i] = false;
        for (int i = 0; i < n; ++i) bg[i] = false;
        printf("%d\n", (int)root.size() - 1);
        int p = ds[root[0]];
        for (int i = 0; i < m; ++i) {
            if (Find(i) == root[0]) continue;
            if (used[Find(i)]) continue;
            if (deg[i] == 1) {
                used[Find(i)] = true;
                printf("%d %d %d\n", g[i][0] + 1, ds[i], p);
            }
        }
        tk = 0;
        for (int i = 1; i < root.size(); ++i) {
            if (!used[root[i]]) {
                Dfs(root[i], -1, -1);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (Find(gx[i]) == root[0]) continue;
            if (used[Find(gx[i])]) continue;
            if (!bg[i]) {
                printf("%d %d %d\n", i + 1, ds[gx[i]], p);
                used[Find(gx[i])] = true;
            }
        }
        for (int i = 1; i < root.size(); ++i) assert(used[root[i]]);
    }
    return 0;
}
