

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
vector<pair<int, int>> g[maxn];
vector<pair<int, int>> ed[maxn];
int fa[maxn], tin[maxn], low[maxn], tk;
bool v[maxn], brg[maxn];

int find(int x) {
    if (x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    fa[find(x)] = find(y);
}

void dfs(int x, int p) {
    tin[x] = low[x] = tk++;
    for (const auto &e : g[x]) {
        int u = e.first, i = e.second;
        if (i == p) continue;
        if (tin[u] >= 0) {
            low[x] = min(low[x], tin[u]);
            continue;
        }
        dfs(u, i);
        low[x] = min(low[x], low[u]);
    }
    if (low[x] == tin[x]) {
        if (~p) brg[p] = true;
    }
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i < maxn; ++i) fa[i] = i;
    for (int i = 0; i < m; ++i) {
        int x, y, d; scanf("%d%d%d", &x, &y, &d);
        --x, --y;
        ed[d].emplace_back(x, y);
    }
    int ans = 0;
    long long sum = 0;
    for (int i = 0; i < maxn; ++i) {
        int p = 0;
        for (int j = 0; j < (int)ed[i].size(); ++j) {
            int x = find(ed[i][j].first), y = find(ed[i][j].second);
            if (x == y) continue;
            g[x].emplace_back(y, p);
            g[y].emplace_back(x, p);
            ++p;
        }
        for (int j = 0; j < n; ++j) tin[j] = -1;
        for (int j = 0; j < p; ++j) brg[j] = false;
        tk = 0;
        for (int j = 0; j < n; ++j) {
            if (tin[j] >= 0) continue;
            dfs(j, -1);
        }
        for (int j = 0; j < p; ++j) {
            if (brg[j]) ++ans, sum += i;
        }
        for (int j = 0; j < n; ++j) g[j].clear();
        for (int j = 0; j < (int)ed[i].size(); ++j) {
            int x = ed[i][j].first, y = ed[i][j].second;
            merge(x, y);
        }
    }
    printf("%d %lld\n", ans, sum);
    return 0;
}
