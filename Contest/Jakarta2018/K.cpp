#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5;

set<pair<int, int>> edg;
vector<int> g[maxn];
bitset<maxn> vis;

vector<tuple<int, int, int>> ans;

pair<int,int> edge(int u, int v) {
    return u < v ? make_pair(u, v) : make_pair(v, u);
}

void dfs(int now, int pa) {
    // printf("now = %d, pa = %d\n", now, pa);
    vis[now] = true;
    int la = -1;
    for (int i: g[now]) {
        if (i == pa) continue;
        if (!vis[i]) dfs(i, now);
        if (la == -1) {
            if (edg.find(edge(now, i)) == edg.end()) continue;
            la = i;
            continue;
        } else {
            if (edg.find(edge(now, i)) == edg.end()) continue;
            ans.emplace_back(la, now, i);
            edg.erase(edge(la, now));
            edg.erase(edge(now, i));
            la = -1;
        }
    }
    if (la != -1 && pa) {
        ans.emplace_back(la, now, pa);
        edg.erase(edge(la, now));
        edg.erase(edge(now, pa));
    }
}

int main() {
    // ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    while (m--) {
        int u, v; cin >> u >> v;
        if (v < u) swap(u, v);
        edg.insert(edge(u, v));
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) {
        if (vis[i]) continue;
        dfs(i, 0);
    }
    cout << ans.size() << '\n';
    for (auto t: ans) {
        cout << get<0>(t) << ' ' << get<1>(t) << ' ' << get<2>(t) << '\n';
    }
}
