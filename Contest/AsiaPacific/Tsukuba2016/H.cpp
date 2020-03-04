#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
vector<int> g[maxn], r[maxn];
vector<pair<int, int>> dg[maxn];
int x[maxn], y[maxn], w[maxn], uf[maxn], dep[maxn];
int fa[maxn][20], dp[maxn], dt[maxn];
int gdp[maxn], scc[maxn], fdp[maxn];
bool ig[maxn], v[maxn];

void infinite() {
    puts("Infinite");
    exit(0);
}

int find(int x) {
    if (x == uf[x]) return x;
    return uf[x] = find(uf[x]);
}

void merge(int x, int y) {
    uf[find(x)] = find(y);
}

vector<int> check_cycle(int n) {
    memset(v, false, sizeof(v));
    memset(scc, -1, sizeof(scc));

    vector<int> tz;

    function<void(int)> dfs = [&](int x) {
        v[x] = true;
        for (int u : g[x]) {
            if (!v[u]) dfs(u);
        }
        tz.push_back(x);
    };

    function<void(int, int)> rdfs = [&](int x, int z) {
        scc[x] = z;
        for (int u : r[x]) {
            if (scc[u] == -1) rdfs(u, z);
        }
    };

    for (int i = 0; i < n; ++i) {
        if (!v[i]) dfs(i);
    }

    int sz = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (scc[tz[i]] == -1) rdfs(tz[i], sz++);
    }
    if (sz != n) infinite();
    return tz;
}

void dfs(int x, int p) {
    gdp[x] = dp[x];
    for (int u : g[x]) {
        if (u == p) continue;
        dfs(u, x);
        gdp[x] = max(gdp[x], gdp[u] + 1);
    }
}

void dfs2(int x, int p, int f) {
    fdp[x] = max(f + 1, gdp[x]);
    multiset<int> ms;
    ms.insert(f + 1);
    ms.insert(dp[x]);
    for (int u : g[x]) {
        if (u == p) continue;
        ms.insert(gdp[u] + 1);
    }
    for (int u : g[x]) {
        if (u == p) continue;
        ms.erase(ms.find(gdp[u] + 1));
        dfs2(u, x, *ms.rbegin());
        ms.insert(gdp[u] + 1);
    }
}

void solve(int r) { 
    dfs(r, -1);
    dfs2(r, -1, -1);
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    set<pair<int, int>> directed, undirected;
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &x[i], &y[i], &w[i]);
        --x[i], --y[i];
        if (w[i] == 1) {
            if (directed.count(make_pair(x[i], y[i]))) ig[i] = true;
            if (directed.count(make_pair(y[i], x[i]))) infinite();
            directed.insert(make_pair(x[i], y[i]));
        } else {
            if (undirected.count(minmax(x[i], y[i]))) infinite();
            undirected.insert(minmax(x[i], y[i]));
        }
    }

    for (int i = 0; i < n; ++i) uf[i] = i;
    for (int i = 0; i < m; ++i) {
        if (w[i] == 2) {
            if (find(x[i]) == find(y[i])) infinite();
            merge(x[i], y[i]);
            g[x[i]].push_back(y[i]);
            g[y[i]].push_back(x[i]);
        }
    }

    int ans = 0;

    for (int i = 0; i < n; ++i) g[i].clear();
    for (int i = 0; i < m; ++i) {
        if (w[i] == 1 && !ig[i]) {
            if (find(x[i]) == find(y[i])) infinite();
            dg[find(x[i])].emplace_back(x[i], y[i]);
            g[find(x[i])].push_back(find(y[i]));	
            r[find(y[i])].push_back(find(x[i]));	
        }
    }

    vector<int> tp = check_cycle(n);
    for (int i = 0; i < n; ++i) g[i].clear();
    for (int i = 0; i < m; ++i) if (w[i] == 2) {
        g[x[i]].push_back(y[i]);
        g[y[i]].push_back(x[i]);
    }
    for (int i = 0; i < n; ++i) {
        int x = tp[i];
        if (find(x) != x) continue;
        for (auto e : dg[x]) {
            int u = e.second;
            dp[e.first] = max(dp[e.first], fdp[u] + 1);
        }
        solve(x);
    }
    for (int i = 0; i < n; ++i) ans = max(ans, fdp[i]);
    printf("%d\n", ans);
    return 0;
}
