#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
vector<int> g[maxn];
int sz[maxn], dep[maxn], x[maxn], y[maxn], w[maxn];

void dfs(int x, int p) {
    dep[x] = ~p ? dep[p] + 1 : 0;
    sz[x] = 1;
    for (const int &u : g[x]) {
        if (u == p) continue;
        dfs(u, x);
        sz[x] += sz[u];
    }
}

int main() {
    int n, k, h, c; scanf("%d%d%d%d", &n, &k, &h, &c);
    for (int i = 0; i < n - 1; ++i) {
        scanf("%d%d%d", &x[i], &y[i], &w[i]);
        --x[i], --y[i];
        g[x[i]].push_back(y[i]);
        g[y[i]].push_back(x[i]);

    }
    dfs(0, -1);
    vector<pair<long long, int>> edge;
    for (int i = 0; i < n - 1; ++i) {
        if (dep[x[i]] < dep[y[i]]) swap(x[i], y[i]);
        long long path = sz[x[i]] * 1ll * (n - sz[x[i]]);
        long long length = path * w[i];
        edge.emplace_back(length, i);
    }
    sort(edge.begin(), edge.end());
    if (h <= c) reverse(edge.begin(), edge.end());
    for (int i = 0; i < k; ++i) printf("%d ", edge[i].second + 1);
    puts("");
    return 0;
}
