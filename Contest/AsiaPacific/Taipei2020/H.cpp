#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> g[100005];

int n;
int sz[100005];
int djs[100005];

int Find(int x) {
    return djs[x] == x ? x : djs[x] = Find(djs[x]); 
}

void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return;
    djs[x] = y;
    sz[y] += sz[x];
}

long long ans = 0;

void dfs(int now, int pa) {
    sz[now] = 1;
    for (auto p : g[now]) if (p.first != pa) {
        dfs(p.first, now);
        sz[now] += sz[p.first];
        ans += 1ll * p.second * sz[p.first] * (n - sz[p.first]);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int m; cin >> n >> m;
    vector<tuple<int, int, int>> edges;
    while (m--) {
        int u, v, w; cin >> u >> v >> w;
        edges.emplace_back(w, u, v);
    }

    sort(edges.begin(), edges.end(), greater<tuple<int, int, int>>());

    for (int i = 1; i <= n; ++i) djs[i] = i;

    int grp = n;
    int minw = INT_MAX;
    for (auto &[w, u, v] : edges) {
        if (Find(u) == Find(v)) continue;
        Union(u, v);
        --grp;
        if (grp == 1) {
            minw = w;
            break;
        }
    }

    reverse(edges.begin(), edges.end());
    for (int i = 1; i <= n; ++i) djs[i] = i;
    vector<tuple<int, int, int>> ee;
    for (auto &[w, u, v] : edges) {
        if (w < minw) continue;
        if (Find(u) == Find(v)) continue;
        Union(u, v);
        ee.emplace_back(w, u, v);
    }

    for (int i = 1; i <= n; ++i) djs[i] = i;
    for (int i = 1; i <= n; ++i) sz[i] = 1;
    reverse(ee.begin(), ee.end());

    for (auto [w, u, v] : ee) {
        u = Find(u);
        v = Find(v);
        assert(u != v);
        ans += 1ll * w * sz[u] * sz[v];
        Union(u, v);
    }

    cout << ans << '\n';
}
