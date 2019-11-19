#include <bits/stdc++.h>
using namespace std;

const int maxn = 10005;

set<pair<int, int>> ans;
map<pair<int, int>, pair<int, int>> btg;
vector<int> g[maxn], cg[maxn], mem[maxn];
int nn, bel[maxn], pa[20][maxn], dep[maxn];
int requ[maxn], reqd[maxn], dfn[maxn], low[maxn], tk;
stack<int> stk;

void Dfs(int x, int p) {
    dfn[x] = low[x] = tk++;
    stk.push(x);
    for (int u : g[x]) {
        if (u == p) continue;
        if (dfn[u] != -1) {
            low[x] = min(low[x], dfn[u]);
        } else {
            Dfs(u, x);
            low[x] = min(low[x], low[u]);
        }
    }
    if (low[x] == dfn[x]) {
        nn += 1;
        while (true) {
            int z = stk.top();
            stk.pop();
            bel[z] = nn;
            if (z == x) break;
        }
    }
}

void dfsb(int now, int p) {
    pa[0][now] = p;
    for (int i = 1; i < 20; ++i) pa[i][now] = pa[i - 1][pa[i - 1][now]];
    for (int i : cg[now]) if (i != p) {
        dep[i] = dep[now] + 1;
        dfsb(i, now);
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 19; i >= 0; --i) if ((dep[u] - dep[v]) & (1 << i)) u = pa[i][u];
    if (u == v) return u;
    for (int i = 19; i >= 0; --i) if (pa[i][u] != pa[i][v]) {
        u = pa[i][u];
        v = pa[i][v];
    }
    return pa[0][u];
}

void dfsbb(int now, int pa) {
    for (int i : cg[now]) if (i != pa) {
        dfsbb(i, now);
        requ[now] = max(requ[now], requ[i] - 1);
        reqd[now] = max(reqd[now], reqd[i] - 1);
    }
    if (requ[now] && reqd[now]) {
        cout << "No" << endl;
        exit(0);
    }
    if (requ[now]) {
        // printf("requ[%d] = %d\n", now, requ[now]);
        // printf("bedge = %d -> %d, edge = %d -> %d\n", now, pa, btg[make_pair(now, pa)].first, btg[make_pair(now, pa)].second);
        ans.insert(btg[make_pair(now, pa)]);
    }
    else if (pa) {
        // printf("reqd[%d] = %d\n", now, reqd[now]);
        // printf("bedge = %d -> %d, edge = %d -> %d\n", pa, now, btg[make_pair(pa, now)].first, btg[make_pair(pa, now)].second);
        ans.insert(btg[make_pair(pa, now)]);
    }
}

bitset<maxn> ibvis;
void dfsib(int now) {
    ibvis[now] = 1;
    for (int i : g[now]) if (bel[i] == bel[now] && ans.count(make_pair(now, i)) == 0 && ans.count(make_pair(i, now)) == 0) {
        ans.insert(make_pair(now, i));
        if (!ibvis[i]) dfsib(i);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    while (m--) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    memset(dfn, -1, sizeof(dfn));
    Dfs(1, 0);
    // puts("BCC done");
    // for (int i = 1; i <= n; ++i) printf("%d bel %d\n", i, bel[i]);

    for (int i = 1; i <= n; ++i) {
        mem[bel[i]].push_back(i);
        for (int j : g[i]) if (bel[i] != bel[j]) {
            cg[bel[i]].push_back(bel[j]);
            btg[make_pair(bel[i], bel[j])] = make_pair(i, j);
            btg[make_pair(bel[j], bel[i])] = make_pair(j, i);
        }
    }

    dfsb(1, 0);
    // puts("dfsb");
    int k; cin >> k; while (k--) {
        int u, v; cin >> u >> v;
        u = bel[u], v = bel[v];
        if (u == v) continue;
        int l = lca(u, v);
        if (l != u) requ[u] = max(requ[u], dep[u] - dep[l]);
        if (l != v) reqd[v] = max(reqd[v], dep[v] - dep[l]);
    }

    // puts("input done");

    dfsbb(1, 0);

    // puts("dfsbb done");
    for (int i = 1; i <= nn; ++i) dfsib(mem[i][0]);

    cout << "Yes" << endl;
    for (auto &p : ans) cout << p.first << ' ' << p.second << '\n';
}
