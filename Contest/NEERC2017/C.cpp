#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
int x[maxn], y[maxn];
bool v[maxn], used[maxn];
vector<pair<int, int>> g[maxn], r[maxn];

void dfs(int x, vector<pair<int, int>> g[maxn]) {
    v[x] = true;
    for (const auto &e : g[x]) {
        if (v[e.first]) continue;
        used[e.second] = true;
        dfs(e.first, g);
    }
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n, m; scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++i) {
            g[i].clear();
            r[i].clear();
        }
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &x[i], &y[i]);
            --x[i], --y[i];
            g[x[i]].emplace_back(y[i], i);
            r[y[i]].emplace_back(x[i], i);
        }
        for (int i = 0; i < n; ++i) v[i] = false;
        for (int i = 0; i < m; ++i) used[i] = false;
        dfs(0, g);
        for (int i = 0; i < n; ++i) v[i] = false;
        dfs(0, r);
        vector<int> ans;
        for (int i = 0; i < m; ++i) {
            if (!used[i]) ans.push_back(i);
        }
        for (int i = 0; i < m - n - n; ++i) printf("%d %d\n", x[ans[i]] + 1, y[ans[i]] + 1);
    }
    return 0;
}
