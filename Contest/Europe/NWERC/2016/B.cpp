#include <bits/stdc++.h>
using namespace std;

set<int> G[100005], iG[100005], cG[100005];
vector<int> tp;
bitset<100005> vis;
int cc;
int bel[100005];
vector<int> mem[100005];

void dfs1(int now) {
    vis[now] = 1;
    for (int i : G[now]) if (!vis[i]) dfs1(i);
    tp.push_back(now);
}

void dfs2(int now, int cc) {
    vis[now] = 1;
    bel[now] = cc;
    mem[cc].push_back(now);
    // cerr << now << " bel = " << cc << endl;
    for (int i : iG[now]) if (!vis[i]) dfs2(i, cc);
}

int go(int now, int used) {
    // cerr << "go " << now << ", bel = " << bel[now] << ", used = " << used << endl;
    static map<pair<int, int>, int> rec;
    if (rec.count(make_pair(now, used))) return rec[make_pair(now, used)];
    if (used) {
        int mx = 0;
        for (int i : G[now]) if (bel[i] != bel[now]) mx = max(mx, go(i, 0) + 1);
        return rec[make_pair(now, used)] = mx;
    } else {
        if (mem[bel[now]].size() == 1u) return go(now, 1);
        for (int i = 1; i < (int)mem[bel[now]].size(); ++i) 
            if (mem[bel[now]][i] == now) 
                swap(mem[bel[now]][i], mem[bel[now]][0]);
        sort(mem[bel[now]].begin() + 1, mem[bel[now]].end());
        int mx = go(mem[bel[now]][0], 1);
        do {
            for (int z = 1; z < (int)mem[bel[now]].size(); ++z) {
                if (G[mem[bel[now]][z - 1]].count(mem[bel[now]][z]) == 0) break;
                mx = max(mx, z + go(mem[bel[now]][z], 1));
            }
        } while (next_permutation(mem[bel[now]].begin() + 1, mem[bel[now]].end()));
        return rec[make_pair(now, used)] = mx;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        G[u].insert(v);
        iG[v].insert(u);
    }
    for (int i = 1; i <= n; ++i) if (!vis[i]) dfs1(i);
    vis.reset();
    for (int i = n - 1; i >= 0; --i) if (!vis[tp[i]]) dfs2(tp[i], ++cc);
    for (int i = 1; i <= n; ++i) for (int j : G[i]) if (bel[i] != bel[j]) {
        cG[bel[i]].insert(bel[j]);
    }
    // cerr << "fin scc" << endl;
    vis.reset();
    int mx = 0;
    for (int i = 1; i <= n; ++i) mx = max(mx, go(i, 0));
    cout << mx + 1 << endl;
}
