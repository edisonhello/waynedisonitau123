#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

int bel[10004];
bitset<10004> cango[10004], vis;
vector<int> tp, G[10004], iG[10004], cG[10004], icG[10004], mem[10004];

void dfs1(int now) {
    vis[now] = 1;
    for (int i : icG[now]) {
        if (!vis[i]) dfs1(i);
        cango[now] |= cango[i];
    }
}

void dfs2(int now) {
    vis[now] = 1;
    for (int i : cG[now]) if (!vis[i]) {
        dfs2(i);
    }
}

void dfs11(int now) {
    vis[now] = 1;
    for (int i : G[now]) if (!vis[i]) dfs11(i);
    tp.push_back(now);
}

void dfs12(int now, int cc) {
    vis[now] = 1;
    bel[now] = cc;
    mem[cc].push_back(now);
    for (int i : iG[now]) if (!vis[i]) dfs12(i, cc);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    while (m--) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
        iG[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) if (!vis[i]) dfs11(i);
    reverse(tp.begin(), tp.end()); vis.reset();
    int cc = 0;
    for (int i : tp) if (!vis[i]) dfs12(i, ++cc);
    vis.reset();
    for (int i = 1; i <= n; ++i) for (int j : G[i]) if (bel[i] != bel[j]) {
        cG[bel[i]].push_back(bel[j]);
        icG[bel[j]].push_back(bel[i]);
    }

    for (int i = 1; i <= cc; ++i) cango[i][i] = 1;
    for (int i = 1; i <= cc; ++i) if (!vis[i]) dfs1(i);
    int ans = 0;
    for (int i = 1; i <= cc; ++i) {
        vis.reset();
        int tmp = 0;
        for (int j = 1; j <= cc; ++j) {
            if (cango[i][j] && !vis[j]) dfs2(j);
        }
        for (int j = 1; j <= cc; ++j) {
            if (!vis[j]) tmp += mem[j].size();
        }
        ans += tmp * mem[i].size();
    }
    cout << n * n - ans << endl;
}
