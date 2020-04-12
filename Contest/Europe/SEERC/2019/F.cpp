#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> dep(n);
    vector<int> fa(n);

    auto Dfs = [&](auto self, int x, int p) -> void {
        fa[x] = p;
        for (int u : g[x]) {
            if (u == p) continue;
            dep[u] = dep[x] + 1;
            self(self, u, x);
        }
    };

    Dfs(Dfs, 0, -1);
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j) { return dep[i] > dep[j]; });
    vector<int> uf(n), rep(n);
    iota(uf.begin(), uf.end(), 0);
    iota(rep.begin(), rep.end(), 0);

    function<int(int)> Find = [&](int x) {
        if (x == uf[x]) return x;
        return uf[x] = Find(uf[x]);
    };

    auto Merge = [&](int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y) return;
        if (dep[rep[x]] < dep[rep[y]]) swap(x, y);
        uf[x] = y;
    };

    vector<bool> mark(n);

    auto Mark = [&](int x) {
        mark[x] = true;
        for (int u : g[x]) {
            if (mark[u]) Merge(x, u);
        }
    };

    for (int i = 0; i < n; ++i) {
        int x = ord[i];
        if (mark[x]) continue;
        if (fa[x] == -1) {
            cout << "Alice\n";
            return 0;
        }
        if (!mark[fa[x]]) {
            Mark(fa[x]);
            Mark(x);
        } else {
            int f = rep[Find(fa[x])];
            if (fa[f] == -1) {
                cout << "Alice\n";
                return 0;
            }
            assert(!mark[fa[f]]);
            Mark(fa[f]);
            Mark(x);
        }
    }

    cout << "Bob\n";
    return 0;
}

